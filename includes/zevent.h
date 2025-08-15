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
    EventType type = EventType::None ;
	HWND hwnd = nullptr ;

    union {
        struct { 
			int keyCode ; 
		} key ;

        struct { 
            int x, y ; 
            MouseButton button ;
        } mouse ;

        struct { 
            int w, h ;
        } resize ;
    } ;

	Event() noexcept : type(EventType::None), hwnd(nullptr) {}

	bool isFromWindow(HWND src) const noexcept ;

    PT getMousePosition() const noexcept ;

    void setMousePosition(PT pos) noexcept ;

    SZ getResizeSize() const noexcept ;

    void setResizeSize(SZ newSize) noexcept ;

    bool isMouseEvent() const noexcept ;

    bool isKeyEvent() const noexcept ;

    bool isMouseButton(MouseButton button) const noexcept ;

    bool isKey(int keyCode) const noexcept ;
} ;

Event translateWinEvent(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) noexcept ;

PT getEventPosition(const Event& event) noexcept ;

SZ getEventSize(const Event& event) noexcept ;

Event createMouseEvent(EventType type, PT position, MouseButton button) noexcept ;

Event createResizeEvent(SZ size) noexcept ;

Event createKeyEvent(EventType type, int keyCode) noexcept ;

#undef USE_Z_ALIAS