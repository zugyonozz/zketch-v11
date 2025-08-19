#pragma once

// standard header

#include <unordered_map>
#include <queue>
#include <memory>
#include <atomic>
#include <utility>

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

#ifdef USE_ZKETCH_ALIAS

	template<typename Key, typename Value>
	using fast_map = std::unordered_map<Key, Value> ;

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

	// Window registry for managing HWND to Window mappings
	template<typename Derived>
	class WindowRegistry {
	public:
		using WindowPtr = Window<Derived>* ;
		
	private:
		static inline fast_map<HWND, WindowPtr> windows_ ;
		static inline std::atomic<uint8_t> window_count_{0} ;
		
	public:
		static void register_window(HWND hwnd, WindowPtr window) noexcept {
			windows_[hwnd] = window ;
			window_count_.fetch_add(1, std::memory_order_relaxed) ;
		}
		
		static void unregister_window(HWND hwnd) noexcept {
			if (windows_.erase(hwnd) > 0) {
				window_count_.fetch_sub(1, std::memory_order_relaxed) ;
			}
		}
		
		static WindowPtr find_window(HWND hwnd) noexcept {
			auto it = windows_.find(hwnd) ;
			return (it != windows_.end()) ? it->second : nullptr ;
		}
		
		static uint8_t get_count() noexcept {
			return window_count_.load(std::memory_order_relaxed) ;
		}
		
		static bool empty() noexcept {
			return window_count_.load(std::memory_order_relaxed) == 0 ;
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
		
		// Static registry
		static inline fast_map<HWND, Window*> hwnd_map_ ;
		static inline std::atomic<uint8_t> window_count_{0} ;

		// Window class registration
		constexpr bool register_window_class() noexcept {
			WNDCLASSEX wc{} ;
			wc.cbSize = sizeof(WNDCLASSEX) ;
			wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC ; // Added CS_OWNDC for better performance
			wc.lpfnWndProc = window_procedure ;
			wc.hInstance = instance_ ;
			wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION) ;
			wc.hCursor = LoadCursor(nullptr, IDC_ARROW) ;
			wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1) ;
			wc.lpszClassName = class_id_.c_str() ;
			wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION) ;

			if (!RegisterClassExA(&wc)) 
				return GetLastError() == ERROR_CLASS_ALREADY_EXISTS ;

			return true ;
		}

		// Window creation
		void create_window() {
			hwnd_ = CreateWindowExA(
				0,
				class_id_.c_str(),
				title_.c_str(),
				WS_OVERLAPPEDWINDOW,
				bounds_.x, bounds_.y,
				bounds_.w, bounds_.h,
				nullptr, nullptr,
				instance_,
				this
			) ;

			if (!hwnd_) 
				throw error_handler::create_window_failed() ;

			hwnd_map_[hwnd_] = this ;
			window_count_.fetch_add(1, std::memory_order_relaxed) ;
		}

		// Cleanup
		constexpr void destroy() noexcept {
			if (hwnd_) {
				DestroyWindow(hwnd_) ;
				hwnd_ = nullptr ;
			}
			
			if (instance_) 
				UnregisterClassA(class_id_.c_str(), instance_) ;
		}

		// Message handling - optimized for performance
		LRESULT handle_message(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) noexcept {
			switch (msg) {
				case WM_PAINT: {
					PAINTSTRUCT ps ;
					HDC hdc = BeginPaint(hwnd, &ps) ;
					
					if constexpr (requires(HDC hdc) { static_cast<Derived*>(this)->OnPaint(hdc) ; }) 
						static_cast<Derived*>(this)->OnPaint(hdc) ;
					
					EndPaint(hwnd, &ps) ;
					return 0 ;
				}
				
				case WM_CLOSE:
					destroy() ;
					should_close_.store(true, std::memory_order_relaxed) ;
					return 0 ;
					
				case WM_DESTROY: {
					auto it = hwnd_map_.find(hwnd) ;
					if (it != hwnd_map_.end()) {
						hwnd_map_.erase(it) ;
					}
					
					if (window_count_.fetch_sub(1, std::memory_order_relaxed) <= 1) {
						PostQuitMessage(0) ;
					}
					return 0 ;
				}
				
				case WM_SIZE:
					bounds_.setSize(LOWORD(lp), HIWORD(lp)) ;
					break ;
					
				case WM_MOVE:
					bounds_.setPos(LOWORD(lp), HIWORD(lp)) ;
					break ;
					
				default:
					break ;
			}

			// Convert and queue event
			Event event = translateWinEvent(hwnd, msg, wp, lp) ;
			if (event.type != EventType::None) 
				events_.emplace(std::move(event)) ;

			return DefWindowProcA(hwnd, msg, wp, lp) ;
		}

		// Static window procedure
		static LRESULT CALLBACK window_procedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) noexcept {
			Window* window = nullptr ;

			if (msg == WM_NCCREATE) {
				auto cs = reinterpret_cast<CREATESTRUCTA*>(lp) ;
				window = static_cast<Window*>(cs->lpCreateParams) ;
				SetWindowLongPtrA(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window)) ;
				hwnd_map_[hwnd] = window ;
			} else 
				window = reinterpret_cast<Window*>(GetWindowLongPtrA(hwnd, GWLP_USERDATA)) ;

			return window ? window->handle_message(hwnd, msg, wp, lp) : DefWindowProcA(hwnd, msg, wp, lp) ;
		}

	protected:
		// Protected constructors for CRTP
		explicit Window(cstr title, const Point& size, const Point& pos = {0, 0}) noexcept
			: bounds_(pos, size)
			, title_(title)
			, class_id_(IdGenerator::generate("Window"))
			, instance_(GetModuleHandleA(nullptr)) {
			
			if (register_window_class()) {
				create_window() ;
				SetWindowLongPtrA(hwnd_, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this)) ;
			}
		}

		explicit Window(cstr title, const Quad& bounds) noexcept
			: bounds_(bounds)
			, title_(title)
			, class_id_(IdGenerator::generate("Window"))
			, instance_(GetModuleHandleA(nullptr)) {
			
			if (register_window_class()) {
				create_window() ;
				SetWindowLongPtrA(hwnd_, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this)) ;
			}
		}

		// Move semantics
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

		// Window operations
		constexpr void show(int cmd = SW_SHOW) noexcept {
			ShowWindow(hwnd_, cmd) ;
			UpdateWindow(hwnd_) ;
		}

		constexpr void hide() noexcept { 
			ShowWindow(hwnd_, SW_HIDE) ; 
		}

		constexpr void minimize() noexcept { 
			ShowWindow(hwnd_, SW_MINIMIZE) ; 
		}

		constexpr void maximize() noexcept { 
			ShowWindow(hwnd_, SW_MAXIMIZE) ; 
		}

		constexpr void restore() noexcept { 
			ShowWindow(hwnd_, SW_RESTORE) ; 
		}

		void close() noexcept { 
			should_close_.store(true, std::memory_order_relaxed) ; 
		}


		// Getters
		constexpr HWND handle() const noexcept { 
			return hwnd_ ; 
		}

		constexpr const Quad& bounds() const noexcept { 
			return bounds_ ; 
		}

		constexpr cstr title() const noexcept { 
			return title_.c_str() ; 
		}

		constexpr unsigned width() const noexcept { 
			return bounds_.w ; 
		}

		constexpr unsigned height() const noexcept { 
			return bounds_.h ; 
		}


		constexpr Point size() const noexcept { 
			return bounds_.getSize() ; 
		}

		constexpr Point position() const noexcept { 
			return bounds_.getPos() ; 
		}

		
		bool should_close() const noexcept { 
			return should_close_.load(std::memory_order_relaxed) ; 
		}
		
		constexpr bool is_valid() const noexcept { 
			return hwnd_ && IsWindow(hwnd_) ; 
		}

		// Setters with performance optimization
		constexpr void set_title(cstr new_title) noexcept {
			title_ = new_title ;
			SetWindowTextA(hwnd_, new_title) ;
		}

		template<typename T>
		constexpr void set_size(T w, T h) noexcept requires std::is_arithmetic_v<T> {
			bounds_.setSize(w, h) ;
			SetWindowPos(hwnd_, nullptr, 0, 0, bounds_.w, bounds_.h, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE) ;
		}

		template<typename T>
		constexpr void set_position(T x, T y) noexcept requires std::is_arithmetic_v<T> {
			bounds_.setPos(x, y) ;
			SetWindowPos(hwnd_, nullptr, bounds_.x, bounds_.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE) ;
		}

		constexpr void set_position(const Point& pos) noexcept {
			set_position(pos.x, pos.y) ;
		}

		constexpr void set_bounds(const Quad& new_bounds) noexcept {
			bounds_ = new_bounds ;
			SetWindowPos(hwnd_, nullptr, bounds_.x, bounds_.y, bounds_.w, bounds_.h, SWP_NOZORDER | SWP_NOACTIVATE) ;
		}

		// Client area operations
		constexpr Point get_client_size() const noexcept {
			RECT r ;
			GetClientRect(hwnd_, &r) ;
			return {r.right - r.left, r.bottom - r.top} ;
		}

		constexpr Quad get_client_bounds() const noexcept {
			RECT r ;
			GetClientRect(hwnd_, &r) ;
			return {0L, 0L, r.right - r.left, r.bottom - r.top} ;
		}

		// Coordinate transformations
		constexpr Point screen_to_client(const Point& screen_pos) const noexcept {
			tagPOINT pt = static_cast<tagPOINT>(screen_pos) ;
			ScreenToClient(hwnd_, &pt) ;
			return {static_cast<float>(pt.x), static_cast<float>(pt.y)} ;
		}

		constexpr Point client_to_screen(const Point& client_pos) const noexcept {
			POINT pt = static_cast<POINT>(client_pos) ;
			ClientToScreen(hwnd_, &pt) ;
			return {static_cast<float>(pt.x), static_cast<float>(pt.y)} ;
		}

		// Utility functions
		constexpr void center_on_screen() noexcept {
			Point screen_size{GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)} ;
			Point window_size = static_cast<Point>(get_client_size()) ;
			Point centered_pos = (screen_size - window_size) / 2  ;
			set_position(centered_pos.x, centered_pos.y)  ;
		}

		constexpr bool contains_point(const Point& pt) const noexcept {
			Quad client_bounds = get_client_bounds() ;
			return pt.x >= client_bounds.x && pt.x < client_bounds.x + client_bounds.w && pt.y >= client_bounds.y && pt.y < client_bounds.y + client_bounds.h ;
		}

		// Event system
		constexpr bool has_events() const noexcept { 
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

		static void process_messages() noexcept {
			MSG msg ;
			while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE)) {
				TranslateMessage(&msg) ;
				DispatchMessageA(&msg) ;
			}
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