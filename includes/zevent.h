#pragma once

#include <windowsx.h>
#include "zunit.h"

#define USE_Z_ALIAS

enum class EventType : uchar {
    None,
    Quit,
    KeyDown,
    KeyUp,
    MouseMove,
    MouseDown,
    MouseUp,
    Resize,
	Close
} ;

enum class MouseButton : uchar {
    Left,
    Right,
    Middle,
    Unknown
} ;

struct Event {
	char dummy ;
    EventType type = EventType::None ;
	HWND hwnd = nullptr ;

    union {
        struct { 
			int keyCode ; 
		} key ;

        struct { 
            Pos pos ; 
            MouseButton button ;

            const Pos& position() const noexcept { 
				return pos ; 
			}

            void setPosition(const Pos& pos) noexcept { 
				this->pos = pos ;
			}
        } mouse ;

        struct { 
            Size size_ ;

            const Size& size() const noexcept { 
				return size_ ; 
			}

            void setSize(const Size& newSize) noexcept { 
				size_ = newSize ;
			}

        } resize ;
    } ;

	Event() noexcept : dummy(0) {}

	bool isFromWindow(HWND src) const noexcept {
		return hwnd == src ;
	}

    Pos getMousePosition() const noexcept {
        return (type == EventType::MouseMove || type == EventType::MouseDown || type == EventType::MouseUp) ? mouse.position() : Pos{} ;
    }

    void setMousePosition(Pos pos) noexcept {
        if (type == EventType::MouseMove || type == EventType::MouseDown || type == EventType::MouseUp) 
            mouse.setPosition(pos);
    }

    Size getResizeSize() const noexcept {
        return (type == EventType::Resize) ? resize.size() : Size{} ;
    }

    void setResizeSize(Point<uint> newSize) noexcept {
        if (type == EventType::Resize) 
            resize.setSize(newSize) ;
    }

    bool isMouseEvent() const noexcept {
        return type == EventType::MouseMove || type == EventType::MouseDown || type == EventType::MouseUp ;
    }

    bool isKeyEvent() const noexcept {
        return type == EventType::KeyDown || type == EventType::KeyUp ;
    }

    bool isMouseButton(MouseButton button) const noexcept {
        return isMouseEvent() && mouse.button == button ;
    }

    bool isKey(int keyCode) const noexcept {
        return isKeyEvent() && key.keyCode == keyCode ;
    }
} ;

inline Event translateWinEvent(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) noexcept {
    Event ev ;
	ev.hwnd = hwnd ;

    switch (msg) {
        case WM_QUIT :
			ev.type = EventType::Quit ;
        case WM_CLOSE :
			ev.type = EventType::Close ;
			break ;
        case WM_DESTROY :
            ev.type = EventType::Quit ;
            break ;

        case WM_KEYDOWN :
            ev.type = EventType::KeyDown ;
            ev.key.keyCode = (int)wp ;
            break ;

        case WM_KEYUP :
            ev.type = EventType::KeyUp ;
            ev.key.keyCode = (int)wp ;
            break ;

        case WM_MOUSEMOVE :
            ev.type = EventType::MouseMove ;
            ev.mouse.pos.x = GET_X_LPARAM(lp) ;
            ev.mouse.pos.y = GET_Y_LPARAM(lp) ;
            ev.mouse.button = MouseButton::Unknown ;
            break ;

        case WM_LBUTTONDOWN :
            ev.type = EventType::MouseDown ;
            ev.mouse.pos.x = GET_X_LPARAM(lp) ;
            ev.mouse.pos.y = GET_Y_LPARAM(lp) ;
            ev.mouse.button = MouseButton::Left ;
            break ;

        case WM_RBUTTONDOWN :
            ev.type = EventType::MouseDown ;
            ev.mouse.pos.x = GET_X_LPARAM(lp) ;
            ev.mouse.pos.y = GET_Y_LPARAM(lp) ;
            ev.mouse.button = MouseButton::Right ;
            break ;

        case WM_LBUTTONUP :
            ev.type = EventType::MouseUp ;
            ev.mouse.pos.x = GET_X_LPARAM(lp) ;
            ev.mouse.pos.y = GET_Y_LPARAM(lp) ;
            ev.mouse.button = MouseButton::Left ;
            break ;

        case WM_RBUTTONUP :
            ev.type = EventType::MouseUp ;
            ev.mouse.pos.x = GET_X_LPARAM(lp) ;
            ev.mouse.pos.y = GET_Y_LPARAM(lp) ;
            ev.mouse.button = MouseButton::Right ;
            break ;

        case WM_SIZE :
            ev.type = EventType::Resize ;
            ev.resize.size_.x = LOWORD(lp) ;
            ev.resize.size_.y = HIWORD(lp) ;
            break ;

        default:
            ev.type = EventType::None ;
            break ;
    }

    return ev ;
}

inline Pos getEventPosition(const Event& event) noexcept {
    return event.getMousePosition() ;
}

inline Size getEventSize(const Event& event) noexcept {
    return event.getResizeSize() ;
}

inline Event createMouseEvent(EventType type, Point<uint> position, MouseButton button) noexcept {
    Event event ;
    event.type = type ;
    event.mouse.pos.x = position.x ;
    event.mouse.pos.y = position.y ;
    event.mouse.button = button ;
    return event ;
}

inline Event createResizeEvent(Point<uint> size) noexcept {
    Event event ;
    event.type = EventType::Resize ;
    event.resize.size_.x = size.x ;
    event.resize.size_.y = size.y ;
    return event ;
}

inline Event createKeyEvent(EventType type, int keyCode) noexcept {
    Event event ;
    event.type = type ;
    event.key.keyCode = keyCode ;
    return event ;
}

#undef USE_Z_ALIAS