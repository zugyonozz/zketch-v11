#pragma once

#include "zdef.h"
#include "zunit.h"
#include <windowsx.h>

enum class EventType : unsigned char {
    None,
    Quit,
    KeyDown,
    KeyUp,
    MouseMove,
    MouseDown,
    MouseUp,
    Resize
} ;

enum class MouseButton : unsigned char {
    Left,
    Right,
    Middle,
    Unknown
} ;

struct Event {
    EventType type = EventType::None ;

    union {
        struct { 
			int keyCode ; 
		} key ;

        struct { 
            int x, y ; 
            MouseButton button ;

            Point<uint> position() const noexcept { 
				return Point<uint>{x, y} ; 
			}

            void setPosition(Point<uint> pos) noexcept { 
				x = pos.x ; 
				y = pos.y ; 
			}
        } mouse ;

        struct { 
            int width, height ;

            Point<uint> size() const noexcept { 
				return Point<uint>{width, height} ; 
			}

            void setSize(Point<uint> newSize) noexcept { 
				width = newSize.x ; 
				height = newSize.y ; 
			}

        } resize ;
    } ;

    Point<uint> getMousePosition() const noexcept {
        return (type == EventType::MouseMove || type == EventType::MouseDown || type == EventType::MouseUp) ? mouse.position() : Point<uint>{0, 0} ;
    }

    void setMousePosition(Point<uint> pos) noexcept {
        if (type == EventType::MouseMove || type == EventType::MouseDown || type == EventType::MouseUp) 
            mouse.setPosition(pos);
    }

    Point<uint> getResizeSize() const noexcept {
        return (type == EventType::Resize) ? resize.size() : Point<uint>{0} ;
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
};

inline Event translateWinEvent(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    Event ev ;

    switch (msg) {
        case WM_QUIT :
        case WM_CLOSE :
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
            ev.mouse.x = GET_X_LPARAM(lp) ;
            ev.mouse.y = GET_Y_LPARAM(lp) ;
            ev.mouse.button = MouseButton::Unknown ;
            break ;

        case WM_LBUTTONDOWN :
            ev.type = EventType::MouseDown ;
            ev.mouse.x = GET_X_LPARAM(lp) ;
            ev.mouse.y = GET_Y_LPARAM(lp) ;
            ev.mouse.button = MouseButton::Left ;
            break ;

        case WM_RBUTTONDOWN :
            ev.type = EventType::MouseDown ;
            ev.mouse.x = GET_X_LPARAM(lp) ;
            ev.mouse.y = GET_Y_LPARAM(lp) ;
            ev.mouse.button = MouseButton::Right ;
            break ;

        case WM_LBUTTONUP :
            ev.type = EventType::MouseUp ;
            ev.mouse.x = GET_X_LPARAM(lp) ;
            ev.mouse.y = GET_Y_LPARAM(lp) ;
            ev.mouse.button = MouseButton::Left ;
            break ;

        case WM_RBUTTONUP :
            ev.type = EventType::MouseUp ;
            ev.mouse.x = GET_X_LPARAM(lp) ;
            ev.mouse.y = GET_Y_LPARAM(lp) ;
            ev.mouse.button = MouseButton::Right ;
            break ;

        case WM_SIZE :
            ev.type = EventType::Resize ;
            ev.resize.width = LOWORD(lp) ;
            ev.resize.height = HIWORD(lp) ;
            break ;

        default:
            ev.type = EventType::None ;
            break ;
    }

    return ev ;
}

inline Point<uint> getEventPosition(const Event& event) {
    return event.getMousePosition();
}

inline Point<uint> getEventSize(const Event& event) {
    return event.getResizeSize();
}

inline Event createMouseEvent(EventType type, Point<uint> position, MouseButton button) {
    Event event;
    event.type = type;
    event.mouse.x = position.x;
    event.mouse.y = position.y;
    event.mouse.button = button;
    return event;
}

inline Event createResizeEvent(Point<uint> size) {
    Event event;
    event.type = EventType::Resize;
    event.resize.width = size.x;
    event.resize.height = size.y;
    return event;
}

inline Event createKeyEvent(EventType type, int keyCode) {
    Event event;
    event.type = type;
    event.key.keyCode = keyCode;
    return event;
}