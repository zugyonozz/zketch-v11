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
            Pos pos ; 
            MouseButton button ;
        } mouse ;

        struct { 
            Size size_ ;
        } resize ;
    } ;

	Event() noexcept : type(EventType::None), hwnd(nullptr) {}

	bool isFromWindow(HWND src) const noexcept ;

    Pos getMousePosition() const noexcept ;

    void setMousePosition(Pos pos) noexcept ;

    Size getResizeSize() const noexcept ;

    void setResizeSize(Pos newSize) noexcept ;

    bool isMouseEvent() const noexcept ;

    bool isKeyEvent() const noexcept ;

    bool isMouseButton(MouseButton button) const noexcept ;

    bool isKey(int keyCode) const noexcept ;
} ;

inline Event translateWinEvent(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) noexcept ;

inline Pos getEventPosition(const Event& event) noexcept ;

inline Size getEventSize(const Event& event) noexcept ;

inline Event createMouseEvent(EventType type, Pos position, MouseButton button) noexcept ;

inline Event createResizeEvent(Pos size) noexcept ;

inline Event createKeyEvent(EventType type, int keyCode) noexcept ;

#include "zeventimpl.h"

#undef USE_Z_ALIAS