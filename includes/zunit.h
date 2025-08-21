#pragma once

#ifndef USE_ZUNIT_HELPER
	#define USE_ZUNIT_HELPER
#endif

// standard header

#include <ostream>
#include <vector>

// zketch header

#include "zenums.h"

namespace zketch {

	// forward declaration

	struct Point ;;
	struct Quad ;

	#ifdef USE_ZUNIT_HELPER

		// template spesialize for type checking

		template <typename> 
		struct is_point_unit_ {
			static constexpr bool val = false ;
		} ;

		template <> 
		struct is_point_unit_<Point> {
			static constexpr bool val = true ;
		} ;

		template <typename> struct is_quad_unit_ {
			static constexpr bool val = false ;
		} ;

		template <> struct is_quad_unit_<Quad> {
			static constexpr bool val = true ;
		} ;

		template <typename T> 
		constexpr bool is_point_unit = is_point_unit_<T>::val ;

		template <typename T>
		constexpr bool is_quad_unit = is_quad_unit_<T>::val ;

		template <typename T>
		constexpr bool is_zunit = is_point_unit<T> || is_quad_unit<T> ;

		// helper for print hex

		template <typename T> requires std::is_integral_v<T>
		std::string to_hex(const T& val) {
			static char hex_chars[] = "0123456789ABCDEF" ;
			std::string hex;
			hex.reserve(sizeof(T) * 2) ;

			using U = std::make_unsigned_t<T> ; 
			U uval = static_cast<U>(val);

			bool leading = true ;
			for (int i = sizeof(T) * 2 - 1; i >= 0; --i) {
				unsigned shift = i * 4 ;
				unsigned nibble = (uval >> shift) & 0xF ;
				if (nibble != 0 || !leading || i == 0) {
					hex.push_back(hex_chars[nibble]) ;
					leading = false ;
				}
			}

			return hex;
		}

	#endif

	// implementation of point

	struct Point {
		float x, y ;

		constexpr Point() noexcept : x(0.0f), y(0.0f) {}

		template <typename T>
		constexpr Point(T v) noexcept requires std::is_arithmetic_v<T> : x(v), y(v) {}

		template <typename T>
		constexpr Point(T x, T y) noexcept requires std::is_arithmetic_v<T> : x(x), y(y) {}

		template <typename X, typename Y>
		constexpr Point(X x, Y y) noexcept requires std::is_arithmetic_v<X> && std::is_arithmetic_v<Y> : 
		x(static_cast<float>(x)), 
		y(static_cast<float>(y)) {}

		constexpr Point(const Point& o) noexcept : x(o.x), y(o.y) {}

		constexpr Point& operator=(float v) noexcept { 
			x = y = v ;
			return *this ; 
		}

		constexpr Point& operator=(const Point& o) noexcept {
			x = o.x ;
			y = o.y ;
			return *this ;
		}

		constexpr Point operator+() const noexcept { 
			return *this ; 
		}

		constexpr Point operator-() const noexcept { 
			return {-x, -y} ; 
		}

		constexpr Point& operator+=(const Point& o) noexcept { 
			x += static_cast<float>(o.x) ; 
			y += static_cast<float>(o.y) ; 
			return *this ; 
		}

		constexpr Point& operator-=(const Point& o) noexcept { 
			x -= static_cast<float>(o.x) ; 
			y -= static_cast<float>(o.y) ; 
			return *this ; 
		}

		constexpr Point& operator*=(const Point& o) noexcept { 
			x *= static_cast<float>(o.x) ; 
			y *= static_cast<float>(o.y) ; 
			return *this ; 
		}

		constexpr Point& operator/=(const Point& o) noexcept { 
			x /= static_cast<float>(o.x) ; 
			y /= static_cast<float>(o.y) ; 
			return *this ; 
		}

		template <typename T>
		constexpr Point& operator+=(T v) noexcept requires std::is_arithmetic_v<T> { 
			x += static_cast<float>(v) ; 
			y += static_cast<float>(v) ; 
			return *this ; 
		}

		template <typename T>
		constexpr Point& operator-=(T v) noexcept requires std::is_arithmetic_v<T> { 
			x -= static_cast<float>(v) ; 
			y -= static_cast<float>(v) ; 
			return *this ; 
		}

		template <typename T>
		constexpr Point& operator*=(T v) noexcept requires std::is_arithmetic_v<T> { 
			x *= static_cast<float>(v) ; 
			y *= static_cast<float>(v) ; 
			return *this ; 
		}

		template <typename T>
		constexpr Point& operator/=(T v) noexcept requires std::is_arithmetic_v<T> { 
			x /= static_cast<float>(v) ; 
			y /= static_cast<float>(v) ; 
			return *this ; 
		}

		constexpr bool operator==(const Point& o) const noexcept { 
			return x == o.x && y == o.y ; 
		}

		constexpr bool operator!=(const Point& o) const noexcept { 
			return !(*this == o) ; 
		}

		constexpr operator tagPOINT() const noexcept { 
			return {
				static_cast<long>(x), 
				static_cast<long>(y)
			} ; 
		}

		constexpr operator _POINTL() const noexcept { 
			return {
				static_cast<long>(x), 
				static_cast<long>(y)
			} ; 
		}

		constexpr operator tagSIZE() const noexcept { 
			return {
				static_cast<long>(x), 
				static_cast<long>(y)
			} ; 
		}

		constexpr operator tagPOINTS() const noexcept { 
			return {
				static_cast<short>(x), 
				static_cast<short>(y)
			} ; 
		}

		operator Gdiplus::PointF() const noexcept {
			return {x, y} ;
		}

		operator Gdiplus::SizeF() const noexcept {
			return {x, y} ;
		}

		operator Gdiplus::Point() const noexcept {
			return {static_cast<int>(x), static_cast<int>(y)} ;
		}

		operator Gdiplus::Size() const noexcept {
			return {static_cast<int>(x), static_cast<int>(y)} ;
		}

		template <typename ... Args>
		constexpr bool contains(Args ... args) const noexcept requires (std::is_arithmetic_v<Args> && ...) {
			return ((x == static_cast<float>(args) || y == static_cast<float>(args)) && ...) ;
		}

		template <typename ... Args>
		constexpr bool contains(Args ... args) const noexcept requires (std::invocable<Args, float> && ...) {
			return ((args(x) || args(y)) && ...) ;
		}

	} ;

	constexpr Point operator+(const Point& a, const Point& b) noexcept { 
		return {
			a.x + b.x, 
			a.y + b.y
		} ; 
	}

	constexpr Point operator-(const Point& a, const Point& b) noexcept { 
		return {
			a.x - b.x, 
			a.y - b.y
		} ; 
	}

	constexpr Point operator*(const Point& a, const Point& b) noexcept { 
		return {
			a.x * b.x, 
			a.y * b.y
		} ; 
	}

	constexpr Point operator/(const Point& a, const Point& b) noexcept { 
		return {
			a.x / b.x, 
			a.y / b.y
		} ; 
	}

	template <typename T>
	constexpr Point operator+(const Point& a, T v) noexcept requires std::is_arithmetic_v<T> { 
		return {
			a.x + static_cast<float>(v), 
			a.y + static_cast<float>(v)
		} ; 
	}

	template <typename T>
	constexpr Point operator-(const Point& a, T v) noexcept requires std::is_arithmetic_v<T> { 
		return {
			a.x - static_cast<float>(v), 
			a.y - static_cast<float>(v)
		} ; 
	}

	template <typename T>
	constexpr Point operator*(const Point& a, T v) noexcept requires std::is_arithmetic_v<T> { 
		return {
			a.x * static_cast<float>(v), 
			a.y * static_cast<float>(v)
		} ; 
	}

	template <typename T>
	constexpr Point operator/(const Point& a, T v) noexcept requires std::is_arithmetic_v<T> { 
		return {
			a.x / static_cast<float>(v), 
			a.y / static_cast<float>(v)
		} ; 
	}

	template <typename T>
	constexpr Point operator+(T v, const Point& a) noexcept requires std::is_arithmetic_v<T> { 
		return a + v ; 
	}

	template <typename T>
	constexpr Point operator*(T v, const Point& a) noexcept requires std::is_arithmetic_v<T> { 
		return a * v ; 
	}

	template <typename T>
	constexpr Point operator-(T v, const Point& a) noexcept requires std::is_arithmetic_v<T> { 
		return {
			v - a.x, 
			v - a.y
		} ; 
	}

	template <typename T>
	constexpr Point operator/(T v, const Point& a) noexcept requires std::is_arithmetic_v<T> { 
		return {
			v / a.x, 
			v / a.y
		} ; 
	}

	inline std::ostream& operator<<(std::ostream& os, const Point& pt) noexcept {
		return os << "{" << pt.x << ", " << pt.y << "}" ;
	}

	// implementation of Quad

	struct Quad {

		float x, y, w, h ;

		constexpr Quad() noexcept : x(0.0f), y(0.0f), w(0.0f), h(0.0f) {}

		template <typename T>
		constexpr Quad(T v) noexcept requires std::is_arithmetic_v<T> : x(static_cast<float>(v)), y(static_cast<float>(v)), w(static_cast<float>(v)), h(static_cast<float>(v)) {}

		template <typename T>
		constexpr Quad(T x, T y, T w, T h) noexcept requires std::is_arithmetic_v<T> : x(static_cast<float>(x)), y(static_cast<float>(y)), w(static_cast<float>(w)), h(static_cast<float>(h)) {}

		template <typename X, typename Y, typename W, typename H>
		constexpr Quad(X x, Y y, W w, H h) noexcept requires std::is_arithmetic_v<X> && std::is_arithmetic_v<Y> && std::is_arithmetic_v<W> && std::is_arithmetic_v<H> : 
		x(static_cast<float>(x)), 
		y(static_cast<float>(y)), 
		w(static_cast<float>(w)), 
		h(static_cast<float>(h)) {}

		constexpr Quad(const Quad& o) noexcept : x(o.x), y(o.y), w(o.w), h(o.h) {}

		constexpr Quad(const Point& p, const Point& s) noexcept : x(p.x), y(p.y), w(s.x), h(s.y) {}

		template <typename T>
		constexpr Quad& operator=(T v) noexcept requires std::is_arithmetic_v<T> { 
			x = y = w = h = static_cast<float>(v) ; 
			return *this ; 
		}

		constexpr Quad& operator=(const Quad& o) noexcept { 
			x = o.x ; 
			y = o.y ; 
			w = o.w ; 
			h = o.h ; 
			return *this ; 
		}

		constexpr Quad operator+() const noexcept { 
			return *this ; 
		}

		constexpr Quad operator-() const noexcept { 
			return {-x, -y, w, h} ; 
		}

		constexpr Quad& operator+=(const Quad& o) noexcept { 
			x += o.x ; 
			y += o.y ; 
			w += o.w ; 
			h += o.h ; 
			return *this ; 
		}

		constexpr Quad& operator-=(const Quad& o) noexcept { 
			x -= o.x ; 
			y -= o.y ; 
			w -= o.w ; 
			h -= o.h ; 
			return *this ; 
		}

		constexpr Quad& operator*=(const Quad& o) noexcept { 
			x *= o.x ; 
			y *= o.y ; 
			w *= o.w ; 
			h *= o.h ; 
			return *this ; 
		}

		constexpr Quad& operator/=(const Quad& o) noexcept { 
			x /= o.x ; 
			y /= o.y ; 
			w /= o.w ; 
			h /= o.h ; 
			return *this ; 
		}

		template <typename T>
		constexpr Quad& operator+=(T v) noexcept requires std::is_arithmetic_v<T> { 
			x += static_cast<float>(v) ; 
			y += static_cast<float>(v) ; 
			w += static_cast<float>(v) ; 
			h += static_cast<float>(v) ; 
			return *this ; 
		}

		template <typename T>
		constexpr Quad& operator-=(T v) noexcept requires std::is_arithmetic_v<T> { 
			x -= static_cast<float>(v) ; 
			y -= static_cast<float>(v) ; 
			w -= static_cast<float>(v) ; 
			h -= static_cast<float>(v) ; 
			return *this ; 
		}

		template <typename T>
		constexpr Quad& operator*=(T v) noexcept requires std::is_arithmetic_v<T> { 
			x *= static_cast<float>(v) ; 
			y *= static_cast<float>(v) ; 
			w *= static_cast<float>(v) ; 
			h *= static_cast<float>(v) ; 
			return *this ; 
		}

		template <typename T>
		constexpr Quad& operator/=(T v) noexcept requires std::is_arithmetic_v<T> { 
			x /= static_cast<float>(v) ; 
			y /= static_cast<float>(v) ; 
			w /= static_cast<float>(v) ; 
			h /= static_cast<float>(v) ; 
			return *this ; 
		}

		constexpr bool operator==(const Quad& o) const noexcept { 
			return x == o.x && y == o.y && w == o.w && h == o.h ; 
		}

		constexpr bool operator!=(const Quad& o) const noexcept { 
			return !(*this == o) ; 
		}

		constexpr operator tagRECT() const noexcept { 
			return {
				static_cast<long>(x), 
				static_cast<long>(y), 
				static_cast<long>(w) + static_cast<long>(x), 
				static_cast<long>(h) + static_cast<long>(y) 
			} ; 
		}

		constexpr operator _RECTL() const noexcept { 
			return {
				static_cast<long>(x), 
				static_cast<long>(y), 
				static_cast<long>(w) + static_cast<long>(x), 
				static_cast<long>(h) + static_cast<long>(y) 
			} ; 
		}

		operator Gdiplus::Rect() const noexcept {
			return {static_cast<int>(x), static_cast<int>(y), static_cast<int>(w), static_cast<int>(h)} ;
		}

		operator Gdiplus::RectF() const noexcept {
			return {x, y, w, h} ;
		}

		constexpr const Point getPos() const noexcept { 
			return {x, y} ; 
		}

		constexpr Point getPos() noexcept { 
			return {x, y} ; 
		}

		constexpr const Point getSize() const noexcept { 
			return {w, h} ; 
		}

		constexpr Point getSize() noexcept { 
			return {w, h} ; 
		}

		template <typename T>
		constexpr Quad& setPos(T x, T y) noexcept requires std::is_arithmetic_v<T> { 
			x = static_cast<float>(x) ; 
			y = static_cast<float>(y) ; 
			return *this ;
		}

		constexpr Quad& setPos(const Point& pos) noexcept { 
			x = pos.x ; 
			y = pos.y ; 
			return *this ;
		}

		template <typename T>
		constexpr Quad& setSize(T w, T h) noexcept requires std::is_arithmetic_v<T> { 
			w = static_cast<float>(w) ; 
			h = static_cast<float>(h) ; 
			return *this ;
		}

		constexpr Quad& setSize(const Point& size) noexcept { 
			w = size.x ; 
			h = size.y ; 
			return *this ;
		}

		template <typename ... Args>
		constexpr bool contains(Args ... args) const noexcept requires (std::is_arithmetic_v<Args> && ...) {
			return ((x == static_cast<float>(args) || y == static_cast<float>(args) || w == static_cast<float>(args) || h == static_cast<float>(args)) && ...) ;
		}

		template <typename ... Args>
		constexpr bool contains(Args ... args) const noexcept requires (std::invocable<Args, float> && ...) {
			return ((args(x) || args(y) || args(w) || args(h)) && ...) ;
		}
	} ;

	constexpr Quad operator+(const Quad& a, const Quad& b) noexcept { 
		return {
			a.x + b.x, 
			a.y + b.y, 
			a.w + b.w, 
			a.h + b.h
		} ; 
	}

	constexpr Quad operator-(const Quad& a, const Quad& b) noexcept { 
		return {
			a.x - b.x, 
			a.y - b.y, 
			a.w - b.w, 
			a.h - b.h
		} ; 
	}

	constexpr Quad operator*(const Quad& a, const Quad& b) noexcept { 
		return {
			a.x * b.x, 
			a.y * b.y, 
			a.w * b.w, 
			a.h * b.h
		} ; 
	}

	constexpr Quad operator/(const Quad& a, const Quad& b) noexcept { 
		return {
			a.x / b.x, 
			a.y / b.y, 
			a.w / b.w, 
			a.h / b.h
		} ; 
	}

	template <typename T>
	constexpr Quad operator+(const Quad& a, T v) noexcept requires std::is_arithmetic_v<T> { 
		return {
			a.x + static_cast<float>(v), 
			a.y + static_cast<float>(v), 
			a.w + static_cast<float>(v), 
			a.h + static_cast<float>(v)
		} ; 
	}

	template <typename T>
	constexpr Quad operator-(const Quad& a, T v) noexcept requires std::is_arithmetic_v<T> { 
		return {
			a.x - static_cast<float>(v), 
			a.y - static_cast<float>(v), 
			a.w - static_cast<float>(v), 
			a.h - static_cast<float>(v)
		} ; 
	}

	template <typename T>
	constexpr Quad operator*(const Quad& a, T v) noexcept requires std::is_arithmetic_v<T> { 
		return {
			a.x * static_cast<float>(v), 
			a.y * static_cast<float>(v), 
			a.w * static_cast<float>(v), 
			a.h * static_cast<float>(v)
		} ; 
	}

	template <typename T>
	constexpr Quad operator/(const Quad& a, T v) noexcept requires std::is_arithmetic_v<T> { 
		return {
			a.x / static_cast<float>(v), 
			a.y / static_cast<float>(v), 
			a.w / static_cast<float>(v), 
			a.h / static_cast<float>(v)
		} ; 
	}

	template <typename T>
	constexpr Quad operator+(T v, const Quad& a) noexcept requires std::is_arithmetic_v<T> { 
		return a + v ; 
	}

	template <typename T>
	constexpr Quad operator-(T v, const Quad& a) noexcept requires std::is_arithmetic_v<T> { 
		return {
			v - a.x, 
			v - a.y, 
			v - a.w, 
			v - a.h
		} ; 
	}

	template <typename T>
	constexpr Quad operator*(T v, const Quad& a) noexcept requires std::is_arithmetic_v<T> { 
		return a * v ; 
	}

	template <typename T>
	constexpr Quad operator/(T v, const Quad& a) noexcept requires std::is_arithmetic_v<T> { 
		return {
			v / a.x, 
			v / a.y, 
			v / a.w, 
			v / a.h
		} ; 
	}

	inline std::ostream& operator<<(std::ostream& os, const Quad& q) noexcept {
		return os << "{" << q.x << ", " << q.y << ", " << q.w << ", " << q.h << "}" ;
	}

	// error handler

	namespace error_handler {

		struct color_access_out_of_bound {
			const char* what() const noexcept ;
		} ;

	}

	// implementation of Color

	class Color {
	private :
		union Color_ {
			unsigned data ;
			uchar bytes[sizeof(unsigned)] ;

			constexpr Color_(Color_&&) noexcept = default ;
			constexpr Color_& operator=(Color_&&) noexcept = default ;

			constexpr Color_(unsigned data) noexcept : data(data) {}

			constexpr Color_(uchar r, uchar g, uchar b, uchar a = 255U) noexcept : data((a << 24) | (b << 16) | (g << 8) | r ) {}

			constexpr Color_(const Color_& o) noexcept : data(o.data) {}

			constexpr Color_& operator=(const Color_& o) noexcept {
				if (this != &o) 
					data = o.data ;
				return *this ;
			}
		} color_ ;

	public :
		static constexpr Color Red() { return Color(255, 0, 0, 255) ; }
		
        static constexpr Color Green() { return Color(0, 255, 0, 255) ; }
		
        static constexpr Color Blue() { return Color(0, 0, 255, 255) ; }
		
        static constexpr Color White() { return Color(255, 255, 255, 255) ; }
		
        static constexpr Color Black() { return Color(0, 0, 0, 255) ; }
		
        static constexpr Color Yellow() { return Color(255, 255, 0, 255) ; }
		
        static constexpr Color Magenta() { return Color(255, 0, 255, 255) ; }
		
        static constexpr Color Cyan() { return Color(0, 255, 255, 255) ; }
		
        static constexpr Color Transparent() { return Color(0, 0, 0, 0) ; }
		
		constexpr Color(Color&& o) noexcept = default ;

		constexpr Color& operator=(Color&& o) noexcept = default ;

		constexpr Color() noexcept : color_(0, 0, 0, 255) {}

		constexpr Color(uchar r, uchar g, uchar b, uchar a) noexcept : color_(r, g, b, a) {}

		constexpr Color(const Color& o) noexcept : color_(o.color_) {}

		constexpr Color& operator=(const Color& o) noexcept {
			if (this != &o)
				color_ = o.color_ ;
			return *this ;
		}

		constexpr const uchar& operator[](RGBA channel) const noexcept {
			return color_.bytes[static_cast<uchar>(channel)] ;
		}

		constexpr uchar& operator[](RGBA channel) noexcept {
			return color_.bytes[static_cast<uchar>(channel)] ;
		}

		const uchar& operator[](uchar channel) const {
			if (channel > 3)
				throw error_handler::color_access_out_of_bound() ;
			return color_.bytes[channel] ;
		}

		uchar& operator[](uchar channel) {
			if (channel > 3)
				throw error_handler::color_access_out_of_bound() ;
			return color_.bytes[channel] ;
		}

		constexpr const uchar* begin() const noexcept {
			return color_.bytes ;
		}

		constexpr uchar* begin() noexcept {
			return color_.bytes ;
		}

		constexpr const uchar* end() const noexcept {
			return color_.bytes + sizeof(unsigned) ;
		}

		constexpr uchar* end() noexcept {
			return color_.bytes + sizeof(unsigned) ;
		}

		constexpr operator COLORREF() const noexcept {
			return (color_.bytes[0] << 16) | (color_.bytes[1] << 8) | color_.bytes[2] ;
		}

		operator Gdiplus::Color() const noexcept {
			return Gdiplus::Color(color_.bytes[3], color_.bytes[0], color_.bytes[1], color_.bytes[2]) ;
		}

		const std::string getHex() const noexcept {
			return to_hex(color_.data) ;
		}
	} ;

	inline std::ostream& operator<<(std::ostream& os, const Color& c) noexcept {
		return os << "{" << static_cast<int>(c[0]) << ", " << static_cast<int>(c[1]) << ", " << static_cast<int>(c[2]) << ", " << static_cast<int>(c[3]) << "}\n" ;
	}

	std::ostream& operator<<(std::ostream& os, const Color& c) noexcept ;

	using Vertex = std::vector<Point> ;

	namespace math {
        
        inline float dot(const Point& a, const Point& b) noexcept {
            return a.x * b.x + a.y * b.y ;
        }
        
        inline float length(const Point& p) noexcept {
            return std::sqrt(p.x * p.x + p.y * p.y) ;
        }
        
        inline float lengthSquared(const Point& p) noexcept {
            return p.x * p.x + p.y * p.y ;
        }
        
        inline Point normalize(const Point& p) noexcept {
            float len = length(p) ;
            return len > 0.0f ? p / len : Point{} ;
        }
        
        inline float distance(const Point& a, const Point& b) noexcept {
            return length(b - a) ;
        }
        
        inline Point lerp(const Point& a, const Point& b, float t) noexcept {
            return a + (b - a) * t ;
        }
        
        inline Point rotate(const Point& p, float angle) noexcept {
            float cos_a = std::cos(angle) ;
            float sin_a = std::sin(angle) ;
            return {
				p.x * cos_a - p.y * sin_a, 
				p.x * sin_a + p.y * cos_a
			} ;
        }
    }

	namespace geometry {
        
        inline bool contains(const Quad& rect, const Point& point) noexcept {
            return point.x >= rect.x && 
				   point.x <= rect.x + rect.w &&
                   point.y >= rect.y && 
				   point.y <= rect.y + rect.h ;
        }
        
        inline bool intersects(const Quad& a, const Quad& b) noexcept {
            return !(
				a.x + a.w < b.x || 
				b.x + b.w < a.x || 
				a.y + a.h < b.y || 
				b.y + b.h < a.y
			) ;
        }
        
        inline Quad intersection(const Quad& a, const Quad& b) noexcept {
            float left = std::max(a.x, b.x) ;
            float top = std::max(a.y, b.y) ;
            float right = std::min(a.x + a.w, b.x + b.w) ;
            float bottom = std::min(a.y + a.h, b.y + b.h) ;
            
            if (left < right && top < bottom) 
                return {left, top, right - left, bottom - top} ;
            return {} ;
        }
    }

}

#ifdef USE_ZUNIT_HELPER
	#undef USE_ZUNIT_HELPER
#endif