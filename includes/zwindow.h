#pragma once

#include <unordered_map>
#include <queue>
#include "zevent.h"

using QE = std::queue<Event> ;

namespace error_handler {
	struct register_class_failed { cstr what() const noexcept { return "Failed to register window class" ; } } ;
	struct create_window_failed { cstr what() const noexcept { return "Failed to create window" ; } } ;
}

class Window {
private :

	using HM = std::unordered_map<HWND, Window*> ;

	HWND m_hwnd = nullptr ;
	HINSTANCE m_hInstance = nullptr ;
	Rect m_bound ;
	cstr m_title ;
	bool m_shouldclose = false ;
	static inline QE m_events ;
	str WID = getWID() ;
	static inline HM hm ;

	static str getWID() {
		static uchar baseWID = 0 ;
		return std::to_string(baseWID++) ;
	}

	bool registerWindowClass() {
		WNDCLASSEX wc = {} ;
		wc.cbSize = sizeof(WNDCLASSEX) ;
		wc.style = CS_HREDRAW | CS_VREDRAW ;
		wc.lpfnWndProc = initEventHandler ;
		wc.cbClsExtra = 0 ;
        wc.cbWndExtra = 0 ;
        wc.hInstance = m_hInstance ;
        wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION) ;
        wc.hCursor = LoadCursor(nullptr, IDC_ARROW) ;
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1) ;
        wc.lpszMenuName = nullptr ;
        wc.lpszClassName = WID.c_str() ;
        wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION) ;
		if (!RegisterClassEx(&wc)) {
            if (GetLastError() != ERROR_CLASS_ALREADY_EXISTS) {
                throw error_handler::register_class_failed() ;
			} else
			 	return false ;
		}
		return true;
	}

	void createWindow() {
		m_hwnd = CreateWindowEx(
            0, // Extended style
            WID.c_str(), // Class name
            m_title, // Window title
            WS_OVERLAPPEDWINDOW, // Window style
            m_bound.x, // X position
            m_bound.y, // Y position
            m_bound.w, // Width
            m_bound.h, // Height
            nullptr, // Parent window
            nullptr, // Menu
            m_hInstance, // Instance handle
            this // Additional data
        ) ;

		if (!m_hwnd)
			throw error_handler::create_window_failed() ;

		hm[m_hwnd] = this ;
	}

	void destroy() {
        if (m_hwnd) {
            DestroyWindow(m_hwnd) ;
            m_hwnd = nullptr ;
        }
        if (m_hInstance) 
            UnregisterClass(WID.c_str(), m_hInstance) ;
    }

	LRESULT HandleMsg(HWND hwnd, uint msg, WPARAM wp, LPARAM lp) noexcept {
		Event event = translateWinEvent(hwnd, msg, wp, lp);
        if (event.type != EventType::None) 
            m_events.push(event) ;

        switch (msg) {
            case WM_CLOSE:
                m_shouldclose = true;
                return 0;

            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;

            case WM_SIZE:
                m_bound.setSize(LOWORD(lp), HIWORD(lp)) ;
                break;

            case WM_MOVE:
                m_bound.setPos(LOWORD(lp), HIWORD(lp)) ;
                break;

            case WM_PAINT: {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hwnd, &ps);
                RECT rect ;
                GetClientRect(hwnd, &rect) ;
                FillRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH)) ;
                EndPaint(hwnd, &ps) ;
                return 0 ;
            }
        }

        return DefWindowProc(hwnd, msg, wp, lp) ;
	}

	static LRESULT CALLBACK initEventHandler(HWND hwnd, uint msg, WPARAM wp, LPARAM lp) noexcept {
		Window* w = nullptr ;
		if (msg == WM_NCCREATE) {
			CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lp) ;
			w = reinterpret_cast<Window*>(cs->lpCreateParams) ;
			SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(w)) ;
			hm[hwnd] = w ;
		} else 
			w = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA)) ;
		if (w)
			return w->HandleMsg(hwnd, msg, wp, lp) ;

		return DefWindowProc(hwnd, msg, wp, lp) ;
	}

public :
	Window(const Window&) = delete ;
	Window& operator=(const Window&) = delete ;

	Window(cstr title, uint width, uint height, uint pos_x = 0U, uint pos_y = 0U) noexcept : m_bound(pos_x, pos_y, width, height), m_title(title), m_hInstance(GetModuleHandle(nullptr)) {
		registerWindowClass();
        createWindow();
        SetWindowLongPtr(m_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	}

	Window(cstr title, const Size& size) noexcept : m_bound(Pos{}, size), m_title(title), m_hInstance(GetModuleHandle(nullptr)) {
		registerWindowClass();
        createWindow();
        SetWindowLongPtr(m_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	}

	Window(cstr title, const Size& size, const Pos& pos) noexcept : m_bound(pos, size), m_title(title), m_hInstance(GetModuleHandle(nullptr)) {
		registerWindowClass();
        createWindow();
        SetWindowLongPtr(m_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	}

	Window(cstr title, const RECT& bound) noexcept : m_bound(bound), m_title(title), m_hInstance(GetModuleHandle(nullptr)) {
		registerWindowClass();
        createWindow();
        SetWindowLongPtr(m_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	}

	Window(cstr title, const Rect& bound) noexcept : m_bound(bound), m_title(title), m_hInstance(GetModuleHandle(nullptr)) {
		registerWindowClass();
        createWindow();
        SetWindowLongPtr(m_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	}

	Window(Window&& o) noexcept : m_hwnd(o.m_hwnd), m_hInstance(o.m_hInstance), m_bound(o.m_bound), m_title(std::move(o.m_title)) {
		o.m_hwnd = nullptr ;
		o.m_hInstance = nullptr ;
		if (m_hwnd) SetWindowLongPtr(m_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this)) ;
	}

	Window& operator=(Window&& o) noexcept {
		if (this != &o) {
			m_hwnd = o.m_hwnd ;
			m_hInstance = o.m_hInstance ;
			m_bound = o.m_bound ;
			m_title = std::move(o.m_title) ;
			o.m_hwnd = nullptr ;
			o.m_hInstance = nullptr ;
			if (m_hwnd) SetWindowLongPtr(m_hwnd, GWLP_USERDATA, reinterpret_cast<sllong>(this)) ;
		}
		return *this ;
	}

	~Window() noexcept { destroy() ; }

	void show() { ShowWindow(m_hwnd, WinFg::SHOW) ; UpdateWindow(m_hwnd) ; }
	void hide() { ShowWindow(m_hwnd, WinFg::HIDE) ; }
    void minimize() { ShowWindow(m_hwnd, WinFg::MINIMIZE) ; }
    void maximize() { ShowWindow(m_hwnd, WinFg::MAXIMIZE) ; }
    void restore() { ShowWindow(m_hwnd, WinFg::RESTORE) ; }
	HWND getHandle() const noexcept { return m_hwnd ; }
	uint width() const noexcept { return m_bound.w ; }
	uint height() const noexcept { return m_bound.h ; }
	const auto Size() const noexcept { return m_bound.getSize() ; }
	const auto Position() const noexcept { return m_bound.getPos() ; }
	const auto& Bound() const noexcept { return m_bound ; } ;
	cstr title() const noexcept { return m_title ; }
    void setTitle(const char* title) noexcept { m_title = title ; SetWindowText(m_hwnd, title) ; }
    template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>> void setSize(T w, T h) noexcept { SetWindowPos(m_hwnd, nullptr, 0, 0, (m_bound.w = w) , (m_bound.h = h), SWP_NOMOVE | SWP_NOZORDER) ; }
    template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>> void setPosition(T x, T y) noexcept { SetWindowPos(m_hwnd, nullptr, (m_bound.x = x), (m_bound.y = y), 0 , 0, SWP_NOSIZE | SWP_NOZORDER) ; }
	void setSize(const ::Size& size) noexcept { SetWindowPos(m_hwnd, nullptr, 0, 0, (m_bound.w = size.x) , (m_bound.h = size.y), SWP_NOMOVE | SWP_NOZORDER) ; }
    void setPosition(const Pos& pos) noexcept { SetWindowPos(m_hwnd, nullptr, (m_bound.x = pos.x), (m_bound.y = pos.y), 0 , 0, SWP_NOSIZE | SWP_NOZORDER) ; }
	void setBound(const Rect& bound) noexcept {SetWindowPos(m_hwnd, nullptr, (m_bound.x = bound.x), (m_bound.y = bound.y), (m_bound.w = bound.w) , (m_bound.h = bound.h), SWP_NOZORDER) ; }
	bool shouldClose() const noexcept { return m_shouldclose ; }
	void close() noexcept { m_shouldclose = true ; }
	bool isValid() const noexcept { return m_hwnd && IsWindow(m_hwnd) ; }
	void getClientSize(uint& w, uint& h) const noexcept { RECT r ; GetClientRect(m_hwnd, &r) ; w = r.right - r.left ; h = r.bottom - r.top ; }
	Point<uint> getClientSize() const noexcept { return getClientBound().getSize() ; }
	Rect getClientBound() const noexcept { RECT r1 ; GetClientRect(m_hwnd, &r1) ; return Rect{Point<uint>{}, Point<uint>{r1.right - r1.left, r1.bottom - r1.top}} ; }

	static bool pollEvent(Event& e) {
        if (!m_events.empty()) {
            e = m_events.front();
            m_events.pop();
            return true;
        }
        return false;
    }

    void processMessage() noexcept {
        MSG msg;
        while (PeekMessage(&msg, m_hwnd, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
	
	void centerOnScreen() {
        Point<uint> screensize = {GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)} ;
        Point<uint> wsize = getClientSize() ;
        setPosition((screensize - wsize) / 2) ;
    }

	bool containsPoint(Point<uint> pt) const {
        Rect b = getClientBound();
        return pt.x >= b.x && pt.x < b.x + b.w && pt.y >=b.y && pt.y < b.y + b.h;
    }

	Point<uint> screenToClient(Point<uint> pos) const {
        POINT pt = static_cast<POINT>(pos) ;
        ScreenToClient(m_hwnd, &pt) ;
        return Point<uint>(pt.x, pt.y) ;
    }

    Point<uint> clientToScreen(Point<uint> pos) const {
        POINT pt = static_cast<POINT>(pos) ;
        ClientToScreen(m_hwnd, &pt) ;
        return Point<uint>(pt.x, pt.y) ;
    }
} ;