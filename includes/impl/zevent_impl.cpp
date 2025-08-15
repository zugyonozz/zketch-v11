#include "../zevent.h"

bool Event::isFromWindow(HWND src) const noexcept {
	return hwnd == src ;
}

PT Event::getMousePosition() const noexcept {
	return (type == EventType::MouseMove || type == EventType::MouseDown || type == EventType::MouseUp) ? PT{mouse.x, mouse.y} : PT{} ;
}

void Event::setMousePosition(PT pos) noexcept {
	if (type == EventType::MouseMove || type == EventType::MouseDown || type == EventType::MouseUp) {
		mouse.x = pos.X ;
		mouse.y = pos.Y ;
	}
}

SZ Event::getResizeSize() const noexcept {
	return (type == EventType::Resize) ? SZ{resize.w, resize.h} : SZ{} ;
}

void Event::setResizeSize(SZ newSize) noexcept {
	if (type == EventType::Resize) {
		resize.w = newSize.Width ;
		resize.h = newSize.Height ;
	}
}

bool Event::isMouseEvent() const noexcept {
	return type == EventType::MouseMove || type == EventType::MouseDown || type == EventType::MouseUp ;
}

bool Event::isKeyEvent() const noexcept {
	return type == EventType::KeyDown || type == EventType::KeyUp ;
}

bool Event::isMouseButton(MouseButton button) const noexcept {
	return isMouseEvent() && mouse.button == button ;
}

bool Event::isKey(int keyCode) const noexcept {
	return isKeyEvent() && key.keyCode == keyCode ;
}

Event translateWinEvent(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) noexcept {
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

PT getEventPosition(const Event& ev) noexcept {
    return ev.getMousePosition() ;
}

SZ getEventSize(const Event& ev) noexcept {
    return ev.getResizeSize() ;
}

Event createMouseEvent(EventType type, PT position, MouseButton button) noexcept {
    Event ev ;
    ev.type = type ;
    ev.mouse.x = position.X ;
    ev.mouse.y = position.Y ;
    ev.mouse.button = button ;
    return ev ;
}

Event createResizeEvent(SZ size) noexcept {
    Event ev ;
    ev.type = EventType::Resize ;
    ev.resize.w = size.Width ;
    ev.resize.h = size.Height ;
    return ev ;
}

Event createKeyEvent(EventType type, int keyCode) noexcept {
    Event ev ;
    ev.type = type ;
    ev.key.keyCode = keyCode ;
    return ev ;
}