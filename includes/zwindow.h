#pragma once

#include <queue>
#include <unordered_map>
#include <string>
#include <deque> 

#define WIN32_LEAN_AND_MEAN
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>

#include <zunit.h>
#include "zevent.h"

namespace error_handler {

	struct register_class_failed { 
		cstr what() const noexcept { 
			return "Failed to register window class" ; 
		} 
	} ;

	struct create_window_failed { 
		cstr what() const noexcept { 
			return "Failed to create window" ; 
		} 
	} ;

}

template <typename Derived> 
class Window {
private :
	using HWNDM = std::unordered_map<HWND, Window*> ;

	// non-static member
	HWND m_hwnd = nullptr ;
	HINSTANCE m_hInstance = nullptr ;
	Quad m_bound ;
	cstr m_title ;
	bool m_shouldclose = false ;
	std::queue<Event, std::deque<Event>> m_events ;
	std::string m_windowID = getWindowID() ;

	// static member
	static inline HWNDM hwndmap ;
	static inline uchar nwindow = 0 ;
	static inline std::string window_id = "zwindow_" ;

	static inline std::string getWindowID() noexcept {
		return (window_id += std::to_string(nwindow++)) ;
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
        wc.lpszClassName = m_windowID.c_str() ;
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
            m_windowID.c_str(), // Class name
            m_title, // Window title
            WS_OVERLAPPEDWINDOW, // Window style
            m_bound.X, // X position
            m_bound.Y, // Y position
            m_bound.Width, // Width
            m_bound.Height, // Height
            nullptr, // Parent window
            nullptr, // Menu
            m_hInstance, // Instance handle
            this // Additional data
        ) ;

		if (!m_hwnd)
			throw error_handler::create_window_failed() ;

		hwndmap[m_hwnd] = this ;
		nwindow++ ;

		#ifdef ZWINDOW_DEBUG
		#if defined(EVENT_RECEIVE) || defined (DEBUG_ALL)

		printf("Window [%s] created. Total count: %d\n", m_title, nwindow) ;

		#endif
		#endif
	}

	void destroy() noexcept {

		#ifdef ZWINDOW_DEBUG
		#if defined(EVENT_RECEIVE) || defined (DEBUG_ALL)

		printf("Destroying window [%s]\n", m_title) ;
		
		#endif
		#endif

        if (m_hwnd) {
            DestroyWindow(m_hwnd) ;
            m_hwnd = nullptr ;
        }

        if (m_hInstance) 
            UnregisterClass(m_windowID.c_str(), m_hInstance) ;
    }

	LRESULT HandleMsg(HWND hwnd, unsigned long long msg, WPARAM wp, LPARAM lp) noexcept {

		#ifdef ZWINDOW_DEBUG
		#if defined(EVENT_RECEIVE) || defined (DEBUG_ALL)
		
		printf("Window [%s] received message: 0x%X\n", m_title, msg) ;
		
		#endif
		#endif

		Event event = translateWinEvent(hwnd, msg, wp, lp) ;
        if (event.type != EventType::None) {
            m_events.push(event) ;

		#ifdef ZWINDOW_DEBUG
		#if defined(EVENT_RECEIVE) || defined (DEBUG_ALL)

		printf("Event type %d pushed to window [%s]\n", (int)event.type, m_title) ;
		
		#endif
		#endif

		}

        switch (msg) {
            case WM_CLOSE :

				#ifdef ZWINDOW_DEBUG
				#if defined(EVENT_RECEIVE) || defined (DEBUG_ALL)

				printf("WM_CLOSE received by window [%s]\n", m_title) ;

				#endif
				#endif

				destroy() ;
                m_shouldclose = true ;
                return 0 ;

            case WM_DESTROY : {

				#ifdef ZWINDOW_DEBUG
				#if defined(EVENT_RECEIVE) || defined (DEBUG_ALL)

				printf("WM_DESTROY received by window [%s]\n", m_title) ;

				#endif
				#endif

                auto it = hwndmap.find(hwnd) ;
				if (it != hwndmap.end()) 
                    hwndmap.erase(it) ;

				if (nwindow > 0) 
					nwindow-- ;

				#ifdef ZWINDOW_DEBUG
				#if defined(EVENT_RECEIVE) || defined (DEBUG_ALL)

				printf("Remaining window count: %d\n", (int)nwindow) ;

				#endif
				#endif

                if (nwindow <= 0) {

					#ifdef ZWINDOW_DEBUG
					#if defined(EVENT_RECEIVE) || defined (DEBUG_ALL)

					printf("Last window destroyed, calling PostQuitMessage\n") ;

					#endif
					#endif

                    PostQuitMessage(0) ;
				}

                return 0 ;
			}
			
            case WM_SIZE :

				#ifdef ZWINDOW_DEBUG
				#if defined(EVENT_RECEIVE) || defined (DEBUG_ALL)

				printf("WM_SIZE received by window [%s]\n", m_title) ;

				#endif
				#endif
				
                m_bound.setSize(LOWORD(lp), HIWORD(lp)) ;
                break ;

            case WM_MOVE :

				#ifdef ZWINDOW_DEBUG
				#if defined(EVENT_RECEIVE) || defined (DEBUG_ALL)

				printf("WM_MOVE received by window [%s]\n", m_title) ;

				#endif
				#endif

                m_bound.setPos(LOWORD(lp), HIWORD(lp)) ;
                break ;

            case WM_PAINT : {

				#ifdef ZWINDOW_DEBUG
				#if defined(EVENT_RECEIVE) || defined (DEBUG_ALL)

				printf("WM_PAINT received by window [%s]\n", m_title) ;

				#endif
				#endif

                PAINTSTRUCT ps ;
                HDC hdc = BeginPaint(hwnd, &ps) ;
                if constexpr (requires (HDC hdc) { std::declval<Derived>().OnPaint(hdc) ; }) {

					#ifdef ZWINDOW_DEBUG
					#if defined(EVENT_RECEIVE) || defined (DEBUG_ALL)

					printf("Derived Has Method OnPaint in WM_PAINT [%s]\n", m_title) ;

					#endif
					#endif

					static_cast<Derived*>(this)->OnPaint(hdc) ;
				}
                EndPaint(hwnd, &ps) ;

                return 0 ;
            }
        }

        return DefWindowProc(hwnd, msg, wp, lp) ;
	}

	static LRESULT CALLBACK initEventHandler(HWND hwnd, unsigned msg, WPARAM wp, LPARAM lp) noexcept {
		Window* w = nullptr ;

		if (msg == WM_NCCREATE) {

			CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lp) ;
			w = reinterpret_cast<Window*>(cs->lpCreateParams) ;

			SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(w)) ;

			hwndmap[hwnd] = w ;

		} else 
			w = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA)) ;

		if (w)
			return w->HandleMsg(hwnd, msg, wp, lp) ;

		return DefWindowProc(hwnd, msg, wp, lp) ;
	}

protected :
	Window(const Window&) = delete ;
	Window& operator=(const Window&) = delete ;

	Window(cstr title, unsigned long long width, unsigned long long height, unsigned long long pos_x = 0U, unsigned long long pos_y = 0U) noexcept : m_bound(pos_x, pos_y, width, height), m_title(title), m_hInstance(GetModuleHandle(nullptr)) {
		registerWindowClass() ;
        createWindow() ;
        SetWindowLongPtr(m_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this)) ;
	}

	Window(cstr title, const SZ& size) noexcept : m_bound(PT{}, size), m_title(title), m_hInstance(GetModuleHandle(nullptr)) {
		registerWindowClass() ;
        createWindow() ;
        SetWindowLongPtr(m_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this)) ;
	}

	Window(cstr title, const PT& pos, const SZ& size) noexcept : m_bound(pos, size), m_title(title), m_hInstance(GetModuleHandle(nullptr)) {
		registerWindowClass() ;
        createWindow() ;
        SetWindowLongPtr(m_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this)) ;
	}

	Window(cstr title, const RECT& bound) noexcept : m_bound(bound), m_title(title), m_hInstance(GetModuleHandle(nullptr)) {
		registerWindowClass() ;
        createWindow() ;
        SetWindowLongPtr(m_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this)) ;
	}

	Window(cstr title, const Quad& bound) noexcept : m_bound(bound), m_title(title), m_hInstance(GetModuleHandle(nullptr)) {
		registerWindowClass() ;
        createWindow() ;
        SetWindowLongPtr(m_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this)) ;
	}

	Window(Window&& o) noexcept : m_hwnd(o.m_hwnd), m_hInstance(o.m_hInstance), m_bound(o.m_bound), m_title(std::move(o.m_title)) {
		o.m_hwnd = nullptr ;
		o.m_hInstance = nullptr ;
		if (m_hwnd) 
			SetWindowLongPtr(m_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this)) ;
	}

	Window& operator=(Window&& o) noexcept {
		if (this != &o) {

			m_hwnd = o.m_hwnd ;
			m_hInstance = o.m_hInstance ;
			m_bound = o.m_bound ;
			m_title = std::move(o.m_title) ;

			o.m_hwnd = nullptr ;
			o.m_hInstance = nullptr ;

			if (m_hwnd) 
				SetWindowLongPtr(m_hwnd, GWLP_USERDATA, reinterpret_cast<long long>(this)) ;
		}

		return *this ;
	}

	~Window() noexcept { destroy() ; }

	HWND getHandle() noexcept { 
		return m_hwnd ; 
	}

public :

	void show() noexcept { 
		ShowWindow(m_hwnd, WinFg::SHOW) ; 
		UpdateWindow(m_hwnd) ; 
	}

	void hide() noexcept { 
		ShowWindow(m_hwnd, WinFg::HIDE) ; 
	}

    void minimize() { 
		ShowWindow(m_hwnd, WinFg::MINIMIZE) ; 
	}

    void maximize() { 
		ShowWindow(m_hwnd, WinFg::MAXIMIZE) ; 
	}

    void restore() { 
		ShowWindow(m_hwnd, WinFg::RESTORE) ; 
	}

	HWND getHandle() const noexcept { 
		return m_hwnd ; 
	}

	unsigned long long width() const noexcept { 
		return m_bound.Width ; 
	}

	unsigned long long height() const noexcept { 
		return m_bound.Height ; 
	}

	SZ Size() const noexcept { 
		return m_bound.getSize() ; 
	}

	PT Position() const noexcept { 
		return m_bound.getPos() ; 
	}

	const Quad& Bound() const noexcept { 
		return m_bound ; 
	} ;

	cstr title() const noexcept { 
		return m_title ; 
	}

    void setTitle(const char* title) noexcept { 
		m_title = title ; 
		SetWindowText(m_hwnd, title) ; 
	}

    template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>> 
	void setSize(T w, T h) noexcept { 
		SetWindowPos(m_hwnd, nullptr, 0, 0, (m_bound.Width = w) , (m_bound.Height = h), SWP_NOMOVE | SWP_NOZORDER) ; 
	}

    template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>> 
	void setPosition(T x, T y) noexcept { 
		SetWindowPos(m_hwnd, nullptr, (m_bound.X = x), (m_bound.X = y), 0 , 0, SWP_NOSIZE | SWP_NOZORDER) ; 
	}

	void setSize(const SZ& size) noexcept { 
		SetWindowPos(m_hwnd, nullptr, 0, 0, (m_bound.Width = size.Width) , (m_bound.Height = size.Height), SWP_NOMOVE | SWP_NOZORDER) ; 
	}

    void setPosition(const PT& pos) noexcept { 
		SetWindowPos(m_hwnd, nullptr, (m_bound.X = pos.X), (m_bound.Y = pos.Y), 0 , 0, SWP_NOSIZE | SWP_NOZORDER) ; 
	}

	void setBound(const Quad& bound) noexcept { 
		SetWindowPos(m_hwnd, nullptr, (m_bound.X = bound.X), (m_bound.Y = bound.Y), (m_bound.Width = bound.Width) , (m_bound.Height = bound.Height), SWP_NOZORDER) ; 
	}

	bool shouldClose() const noexcept { 
		return m_shouldclose ; 
	}

	void close() noexcept { 
		m_shouldclose = true ; 
	}

	bool isValid() const noexcept { 
		return m_hwnd && IsWindow(m_hwnd) ; 
	}

	void getClientSize(int& w, int& h) const noexcept { 
		RECT r ; 
		GetClientRect(m_hwnd, &r) ; 
		w = r.right - r.left ; 
		h = r.bottom - r.top ; 
	}

	SZ getClientSize() const noexcept { 
		return getClientBound().getSize() ; 
	}

	Quad getClientBound() const noexcept { 
		RECT r1 ; 
		GetClientRect(m_hwnd, &r1) ; 
		return Quad{PT{}, SZ{r1.right - r1.left, r1.bottom - r1.top}} ; 
	}

	bool hasEvents() const { 
		return !m_events.empty() ; 
	}

	void clearEvents() noexcept { 
		while (!m_events.empty()) 
			m_events.pop() ; 
	}

	static int getWindowCount() noexcept { 
		return nwindow ; 
	}

    static void quitApplication() noexcept { 
		PostQuitMessage(0) ; 
	}


	bool pollEvent(Event& e) noexcept {
        if (!m_events.empty()) {

            e = m_events.front();
            m_events.pop();

            return true;
        }

        return false;
    }

	static bool pollEventFromWindow(HWND hwnd, Event& e) noexcept {
        auto it = hwndmap.find(hwnd);

        if (it != hwndmap.end()) 
            return it->second->pollEvent(e);

        return false;
    }

	static void processMessages() noexcept {
        MSG msg;

        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
	
	void centerOnScreen() noexcept {
        PT screensize = {GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)} ;
		PT wsize = static_cast<PT>(getClientSize()) ;

        setPosition((screensize - wsize) / 2) ;
    }

	bool containsPoint(const PT& pt) const noexcept {
        Quad b = getClientBound();
        return pt.X >= b.X && pt.X < b.X + b.Width && pt.Y >= b.Y && pt.Y < b.Y + b.Height ;
    }

	PT screenToClient(const PT& pos) const noexcept {
        POINT pt = static_cast<POINT>(pos) ;
        ScreenToClient(m_hwnd, &pt) ;

        return PT(pt.x, pt.y) ;
    }

    PT clientToScreen(const PT& pos) const {
        POINT pt = static_cast<POINT>(pos) ;

        ClientToScreen(m_hwnd, &pt) ;
        return PT(pt.x, pt.y) ;
    }

	#ifdef ZWINDOW_DEBUG

	unsigned long long getEventCount() const {
        return m_events.size() ;
    }

	#endif

} ;