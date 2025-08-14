#pragma once

bool Event::isFromWindow(HWND src) const noexcept {
	return hwnd == src ;
}

Pos Event::getMousePosition() const noexcept {
	return (type == EventType::MouseMove || type == EventType::MouseDown || type == EventType::MouseUp) ? mouse.pos : Pos{} ;
}

void Event::setMousePosition(Pos pos) noexcept {
	if (type == EventType::MouseMove || type == EventType::MouseDown || type == EventType::MouseUp) 
		mouse.pos = pos ;
}

Size Event::getResizeSize() const noexcept {
	return (type == EventType::Resize) ? resize.size_ : Size{} ;
}

void Event::setResizeSize(Pos newSize) noexcept {
	if (type == EventType::Resize) 
		resize.size_ = newSize ;
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

inline Event createMouseEvent(EventType type, Pos position, MouseButton button) noexcept {
    Event event ;
    event.type = type ;
    event.mouse.pos.x = position.x ;
    event.mouse.pos.y = position.y ;
    event.mouse.button = button ;
    return event ;
}

inline Event createResizeEvent(Pos size) noexcept {
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