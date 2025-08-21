#pragma once

// standard header

#include <queue>
#include <atomic>

// zketch header

#include "zevent.h"

#ifndef WIN32_LEAN_AND_MEAN
	#define WIN32_LEAN_AND_MEAN
#endif

#ifndef NOMINMAX
	#define NOMINMAX
#endif

#ifndef USE_ZKETCH_ALIAS
	#define USE_ZKETCH_ALIAS
#endif

namespace zketch {

	namespace error_handler {

		struct register_class_failed {
			cstr what() const noexcept ;
		} ;

		struct create_window_failed {
			cstr what() const noexcept ;
		} ;

	}

	// Forward declarations
	template<typename Derived>
	class Window ;

	// Utility for generating unique IDs
	class IdGenerator {
	private:
		static inline std::atomic<int> counter_{0} ;
		
	public:
		static std::string generate(cstr prefix) noexcept {
			return std::string(prefix) + std::to_string(counter_.fetch_add(1, std::memory_order_relaxed)) ;
		}
	} ;

	// Main Window class
	template<typename Derived>
	class Window {
	private:
		// Core window data
		HWND hwnd_ = nullptr ;
		HINSTANCE instance_ = nullptr ;
		Quad bounds_ ;
		std::string title_ ;
		std::string class_id_ ;
		
		// State management
		std::atomic<bool> should_close_{false} ;
		
		// Event system - using deque for better performance
		std::queue<Event, std::deque<Event>> events_ ;
		
		// Static registry - FIXED: Sekarang per-template instantiation
		static inline fast_map<HWND, Window*> hwnd_map_ ;
		static inline std::atomic<uint8_t> window_count_{0} ;

		// Window class registration - FIXED: Return type bool
		bool register_window_class() noexcept {
			WNDCLASSEX wc{} ;
			wc.cbSize = sizeof(WNDCLASSEX) ;
			wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC ;
			wc.lpfnWndProc = window_procedure ;
			wc.hInstance = instance_ ;
			wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION) ;
			wc.hCursor = LoadCursor(nullptr, IDC_ARROW) ;
			wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1) ;
			wc.lpszClassName = class_id_.c_str() ;
			wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION) ;

			ATOM result = RegisterClassExA(&wc) ;
			return result != 0 || GetLastError() == ERROR_CLASS_ALREADY_EXISTS ;
		}

		// Window creation - FIXED: Error handling
		void create_window() {
			hwnd_ = CreateWindowExA(
				0,
				class_id_.c_str(),
				title_.c_str(),
				WS_OVERLAPPEDWINDOW,
				static_cast<int>(bounds_.x), 
				static_cast<int>(bounds_.y),
				static_cast<int>(bounds_.w), 
				static_cast<int>(bounds_.h),
				nullptr, nullptr,
				instance_,
				this
			) ;

			if (!hwnd_) 
				throw error_handler::create_window_failed() ;
		}

		// Cleanup - FIXED: Proper cleanup sequence
		void destroy() noexcept {
			if (hwnd_) {
				// Remove from map first
				auto it = hwnd_map_.find(hwnd_) ;
				if (it != hwnd_map_.end()) {
					hwnd_map_.erase(it) ;
					window_count_.fetch_sub(1, std::memory_order_relaxed) ;
				}
				
				DestroyWindow(hwnd_) ;
				hwnd_ = nullptr ;
			}
		}

		// FIXED: Message handling dengan proper event queueing
		LRESULT handle_message(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) noexcept {
			switch (msg) {
				case WM_CREATE : {
					if constexpr (requires() { static_cast<Derived*>(this)->OnCreate(); }) 
						static_cast<Derived*>(this)->OnCreate() ;
    				return 0 ;
				}
				case WM_PAINT : {
					PAINTSTRUCT ps ;
					HDC hdc = BeginPaint(hwnd, &ps) ;
					if constexpr (requires(HDC hdc) { static_cast<Derived*>(this)->OnPaint(hdc) ; }) 
						static_cast<Derived*>(this)->OnPaint(hdc) ;
					EndPaint(hwnd, &ps) ;
					return 0 ;
				}
				case WM_SIZE : {
					Point newSize = {static_cast<float>(LOWORD(lp)), static_cast<float>(HIWORD(lp))} ;
					bounds_.setSize(newSize) ;
					if constexpr (requires(const Point& s) { static_cast<Derived*>(this)->OnResize(s); }) 
                        static_cast<Derived*>(this)->OnResize(newSize) ;
					
					// Queue resize event
					Event event ;
                    event.type = EventType::Resize ;
                    event.hwnd = hwnd ;
                    event.resize.w = LOWORD(lp) ;
                    event.resize.h = HIWORD(lp) ;
                    events_.emplace(std::move(event)) ;
					return 0 ;
				}
				case WM_CLOSE : {
					// Set flag and queue close event
					should_close_.store(true, std::memory_order_relaxed) ;
                    Event event ;
                    event.type = EventType::Close ;
                    event.hwnd = hwnd ;
                    events_.emplace(std::move(event)) ;
                    return 0 ; // Don't call DefWindowProc for WM_CLOSE
                }
                case WM_DESTROY: {
                	// Queue quit event
                	Event event ;
                    event.type = EventType::Quit ;
                    event.hwnd = hwnd ;
                    events_.emplace(std::move(event)) ;
                    return 0 ;
                }
				case WM_NCDESTROY: {
                    // Final cleanup
                    auto it = hwnd_map_.find(hwnd_) ;
                    if (it != hwnd_map_.end()) {
                    	hwnd_map_.erase(it) ;
                    	if (window_count_.fetch_sub(1, std::memory_order_relaxed) == 1) 
                    		PostQuitMessage(0) ;
                    }
                    hwnd_ = nullptr ;
                    return 0 ;
                }
				case WM_MOVE : {
					bounds_.setPos(static_cast<float>(LOWORD(lp)), static_cast<float>(HIWORD(lp))) ;
					break ;
				}
				// Handle other messages that need event queueing
				case WM_KEYDOWN:
				case WM_KEYUP:
				case WM_MOUSEMOVE:
				case WM_LBUTTONDOWN:
				case WM_LBUTTONUP:
				case WM_RBUTTONDOWN:
				case WM_RBUTTONUP: {
					Event event = translateWinEvent(hwnd, msg, wp, lp) ;
					if (event.type != EventType::None) 
						events_.emplace(std::move(event)) ;
					break ;
				}
				default:
					break ;
			}

			return DefWindowProcA(hwnd, msg, wp, lp) ;
		}

		// FIXED: Static window procedure dengan proper message routing
		static LRESULT CALLBACK window_procedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) noexcept {
			Window* window = nullptr ;
			
			if (msg == WM_NCCREATE) {
				auto cs = reinterpret_cast<CREATESTRUCTA*>(lp) ;
				window = static_cast<Window*>(cs->lpCreateParams) ;
				SetWindowLongPtrA(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window)) ;
				window->hwnd_ = hwnd ;
				hwnd_map_[hwnd] = window ;
				window_count_.fetch_add(1, std::memory_order_relaxed) ;
			} else {
				window = reinterpret_cast<Window*>(GetWindowLongPtrA(hwnd, GWLP_USERDATA)) ;
			}

			if (window) {
				return window->handle_message(hwnd, msg, wp, lp) ;
			}

			return DefWindowProcA(hwnd, msg, wp, lp) ;
		}

	protected:
		// Protected constructors for CRTP
		explicit Window(cstr title, const Point& size, const Point& pos = {0, 0}) 
			: instance_(GetModuleHandleA(nullptr))
			, bounds_(pos, size)
			, title_(title)
			, class_id_(IdGenerator::generate("zketchWindow")) {
			
			try {
				if (!register_window_class()) {
					throw error_handler::register_class_failed() ;
				}
				create_window() ;
				SetWindowLongPtrA(hwnd_, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this)) ;
			} catch (...) {
				// Constructor failed, cleanup
				if (hwnd_) {
					DestroyWindow(hwnd_) ;
					hwnd_ = nullptr ;
				}
				throw ;
			}
		}

		explicit Window(cstr title, const Quad& bounds) noexcept
			: bounds_(bounds)
			, title_(title)
			, class_id_(IdGenerator::generate("zketchWindow"))
			, instance_(GetModuleHandleA(nullptr)) {
			
			try {
				if (!register_window_class()) {
					throw error_handler::register_class_failed() ;
				}
				create_window() ;
				SetWindowLongPtrA(hwnd_, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this)) ;
			} catch (...) {
				if (hwnd_) {
					DestroyWindow(hwnd_) ;
					hwnd_ = nullptr ;
				}
				throw ;
			}
		}

		// FIXED: Move semantics
		Window(Window&& other) noexcept
			: hwnd_(std::exchange(other.hwnd_, nullptr))
			, instance_(std::exchange(other.instance_, nullptr))
			, bounds_(other.bounds_)
			, title_(std::move(other.title_))
			, class_id_(std::move(other.class_id_))
			, should_close_(other.should_close_.load())
			, events_(std::move(other.events_)) {
			
			if (hwnd_) {
				SetWindowLongPtrA(hwnd_, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this)) ;
				hwnd_map_[hwnd_] = this ;
			}
		}

		Window& operator=(Window&& other) noexcept {
			if (this != &other) {
				destroy() ;
				
				hwnd_ = std::exchange(other.hwnd_, nullptr) ;
				instance_ = std::exchange(other.instance_, nullptr) ;
				bounds_ = other.bounds_ ;
				title_ = std::move(other.title_) ;
				class_id_ = std::move(other.class_id_) ;
				should_close_.store(other.should_close_.load()) ;
				events_ = std::move(other.events_) ;
				
				if (hwnd_) {
					SetWindowLongPtrA(hwnd_, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this)) ;
					hwnd_map_[hwnd_] = this ;
				}
			}
			return *this ;
		}

		~Window() noexcept {
			destroy() ;
		}

	public:
		// Disable copy operations
		Window(const Window&) = delete ;
		Window& operator=(const Window&) = delete ;

		// FIXED: Close method
		void close() noexcept {
			should_close_.store(true, std::memory_order_relaxed) ;
            if constexpr (requires() { static_cast<Derived*>(this)->OnClose(); }) 
                static_cast<Derived*>(this)->OnClose();
            
            // Send close message to trigger proper shutdown
            if (hwnd_) {
            	PostMessageA(hwnd_, WM_CLOSE, 0, 0) ;
            }
        }

		// Window operations
		void show(int cmd = SW_SHOW) noexcept {
			if (hwnd_) {
				ShowWindow(hwnd_, cmd) ;
				UpdateWindow(hwnd_) ;
			}
		}

		void hide() noexcept { 
			if (hwnd_) ShowWindow(hwnd_, SW_HIDE) ; 
		}

		void minimize() noexcept { 
			if (hwnd_) ShowWindow(hwnd_, SW_MINIMIZE) ; 
		}

		void maximize() noexcept { 
			if (hwnd_) ShowWindow(hwnd_, SW_MAXIMIZE) ; 
		}

		void restore() noexcept { 
			if (hwnd_) ShowWindow(hwnd_, SW_RESTORE) ; 
		}

		// Getters
		HWND handle() const noexcept { 
			return hwnd_ ; 
		}

		const Quad& bounds() const noexcept { 
			return bounds_ ; 
		}

		cstr title() const noexcept { 
			return title_.c_str() ; 
		}

		float width() const noexcept { 
			return bounds_.w ; 
		}

		float height() const noexcept { 
			return bounds_.h ; 
		}

		Point size() const noexcept { 
			return bounds_.getSize() ; 
		}

		Point position() const noexcept { 
			return bounds_.getPos() ; 
		}

		bool should_close() const noexcept { 
			return should_close_.load(std::memory_order_relaxed) ; 
		}
		
		bool is_valid() const noexcept { 
			return hwnd_ && IsWindow(hwnd_) ; 
		}

		// Setters
		void set_title(cstr new_title) noexcept {
			title_ = new_title ;
			if (hwnd_) SetWindowTextA(hwnd_, new_title) ;
		}

		template<typename T>
		void set_size(T w, T h) noexcept requires std::is_arithmetic_v<T> {
			bounds_.setSize(static_cast<float>(w), static_cast<float>(h)) ;
			if (hwnd_) {
				SetWindowPos(hwnd_, nullptr, 0, 0, 
					static_cast<int>(bounds_.w), static_cast<int>(bounds_.h), 
					SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE) ;
			}
		}

		template<typename T>
		void set_position(T x, T y) noexcept requires std::is_arithmetic_v<T> {
			bounds_.setPos(static_cast<float>(x), static_cast<float>(y)) ;
			if (hwnd_) {
				SetWindowPos(hwnd_, nullptr, 
					static_cast<int>(bounds_.x), static_cast<int>(bounds_.y), 
					0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE) ;
			}
		}

		void set_position(const Point& pos) noexcept {
			set_position(pos.x, pos.y) ;
		}

		void set_bounds(const Quad& new_bounds) noexcept {
			bounds_ = new_bounds ;
			if (hwnd_) {
				SetWindowPos(hwnd_, nullptr, 
					static_cast<int>(bounds_.x), static_cast<int>(bounds_.y), 
					static_cast<int>(bounds_.w), static_cast<int>(bounds_.h), 
					SWP_NOZORDER | SWP_NOACTIVATE) ;
			}
		}

		// Client area operations
		Point get_client_size() const noexcept {
			if (!hwnd_) return {} ;
			RECT r ;
			GetClientRect(hwnd_, &r) ;
			return {static_cast<float>(r.right - r.left), static_cast<float>(r.bottom - r.top)} ;
		}

		Quad get_client_bounds() const noexcept {
			if (!hwnd_) return {} ;
			RECT r ;
			GetClientRect(hwnd_, &r) ;
			return {0.0f, 0.0f, static_cast<float>(r.right - r.left), static_cast<float>(r.bottom - r.top)} ;
		}

		// Coordinate transformations
		Point screen_to_client(const Point& screen_pos) const noexcept {
			if (!hwnd_) return screen_pos ;
			POINT pt = static_cast<POINT>(screen_pos) ;
			ScreenToClient(hwnd_, &pt) ;
			return {static_cast<float>(pt.x), static_cast<float>(pt.y)} ;
		}

		Point client_to_screen(const Point& client_pos) const noexcept {
			if (!hwnd_) return client_pos ;
			POINT pt = static_cast<POINT>(client_pos) ;
			ClientToScreen(hwnd_, &pt) ;
			return {static_cast<float>(pt.x), static_cast<float>(pt.y)} ;
		}

		// Utility functions
		void center_on_screen() noexcept {
			Point screen_size{
				static_cast<float>(GetSystemMetrics(SM_CXSCREEN)), 
				static_cast<float>(GetSystemMetrics(SM_CYSCREEN))
			} ;
			Point window_size = size() ;
			Point centered_pos = (screen_size - window_size) / 2.0f ;
			set_position(centered_pos.x, centered_pos.y) ;
		}

		void invalidate() noexcept { 
			if (hwnd_) InvalidateRect(hwnd_, nullptr, FALSE) ; 
		}

		bool contains_point(const Point& pt) const noexcept {
			Quad client_bounds = get_client_bounds() ;
			return pt.x >= client_bounds.x && pt.x < client_bounds.x + client_bounds.w && 
				   pt.y >= client_bounds.y && pt.y < client_bounds.y + client_bounds.h ;
		}

		// Event system
		bool has_events() const noexcept { 
			return !events_.empty() ; 
		}
		
		void clear_events() noexcept {
			std::queue<Event, std::deque<Event>> empty ;
			events_.swap(empty) ;
		}

		bool poll_event(Event& event) noexcept {
			if (!events_.empty()) {
				event = std::move(events_.front()) ;
				events_.pop() ;
				return true ;
			}
			return false ;
		}

		// Static operations
		static uint8_t get_window_count() noexcept {
			return window_count_.load(std::memory_order_relaxed) ;
		}

		static void quit_application() noexcept {
			PostQuitMessage(0) ;
		}

		// FIXED: Process messages with proper quit handling
		static bool process_messages() noexcept {
			MSG msg ;
			while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE)) {
				if (msg.message == WM_QUIT) {
					return false ; // Signal to exit main loop
				}
				TranslateMessage(&msg) ;
				DispatchMessageA(&msg) ;
			}
			return true ; // Continue running
		}

		static bool poll_event_from_window(HWND hwnd, Event& event) noexcept {
			auto it = hwnd_map_.find(hwnd) ;
			return (it != hwnd_map_.end()) ? it->second->poll_event(event) : false ;
		}
	} ;

}

#ifdef WIN32_LEAN_AND_MEAN
	#undef WIN32_LEAN_AND_MEAN
#endif

#ifdef NOMINMAX
	#undef NOMINMAX
#endif

#ifdef USE_ZKETCH_ALIAS
	#undef USE_ZKETCH_ALIAS
#endif