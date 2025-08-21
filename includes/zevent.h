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

		bool isFromWindow(HWND src) const noexcept {
			return hwnd == src ;
		}

		Point getMousePosition() const noexcept {
			return (type == EventType::MouseMove || type == EventType::MouseDown || type == EventType::MouseUp) ? Point{static_cast<float>(mouse.x), static_cast<float>(mouse.y)} : Point{} ;
		}

		void setMousePosition(Point pos) noexcept {
			if (type == EventType::MouseMove || type == EventType::MouseDown || type == EventType::MouseUp) {
				mouse.x = static_cast<int>(pos.x) ;
				mouse.y = static_cast<int>(pos.y) ;
			}
		}

		Point getResizeSize() const noexcept {
			return (type == EventType::Resize) ? Point{static_cast<float>(resize.w), static_cast<float>(resize.h)} : Point{} ;
		}

		void setResizeSize(Point newSize) noexcept {
			if (type == EventType::Resize) {
				resize.w = static_cast<int>(newSize.x) ;
				resize.h = static_cast<int>(newSize.y) ;
			}
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

	Event translateWinEvent(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) noexcept {
		Event ev ;
		ev.hwnd = hwnd ;

		switch (msg) {
			case WM_QUIT :
				ev.type = EventType::Quit ;
				break ;
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
				ev.resize.w = LOWORD(lp) ;
				ev.resize.h = HIWORD(lp) ;
				break ;

			default:
				ev.type = EventType::None ;
				break ;
		}

		return ev ;
	}

	Point getEventPosition(const Event& ev) noexcept {
		return ev.getMousePosition() ;
	}

	Point getEventSize(const Event& ev) noexcept {
		return ev.getResizeSize() ;
	}

	Event createMouseEvent(EventType type, Point position, MouseButton button) noexcept {
		Event ev ;
		ev.type = type ;
		ev.mouse.x = static_cast<int>(position.x) ;
		ev.mouse.y = static_cast<int>(position.y) ;
		ev.mouse.button = button ;
		return ev ;
	}

	Event createResizeEvent(Point size) noexcept {
		Event ev ;
		ev.type = EventType::Resize ;
		ev.resize.w = static_cast<int>(size.x) ;
		ev.resize.h = static_cast<int>(size.y) ;
		return ev ;
	}

	Event createKeyEvent(EventType type, int keyCode) noexcept {
		Event ev ;
		ev.type = type ;
		ev.key.keyCode = keyCode ;
		return ev ;
	}

}