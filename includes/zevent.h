#pragma once

// platform header

#include <windowsx.h>

// zketch header

#include "zunit.h"

namespace zketch {

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

		Point getMousePosition() const noexcept ;

		void setMousePosition(Point pos) noexcept ;

		Point getResizeSize() const noexcept ;

		void setResizeSize(Point newSize) noexcept ;

		bool isMouseEvent() const noexcept ;

		bool isKeyEvent() const noexcept ;

		bool isMouseButton(MouseButton button) const noexcept ;

		bool isKey(int keyCode) const noexcept ;
	} ;

	Event translateWinEvent(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) noexcept ;

	Point getEventPosition(const Event& event) noexcept ;

	Point getEventSize(const Event& event) noexcept ;

	Event createMouseEvent(EventType type, Point position, MouseButton button) noexcept ;

	Event createResizeEvent(Point size) noexcept ;

	Event createKeyEvent(EventType type, int keyCode) noexcept ;

}