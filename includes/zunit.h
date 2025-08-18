#pragma once

static_assert(sizeof(unsigned) == 4, "Color_ assumes 32-bit unsigned") ;

#ifndef IS_LITTLE_ENDIAN
	#ifdef _MSC_VER
		#define IS_LITTLE_ENDIAN 1
	#elif defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		#define IS_LITTLE_ENDIAN 1
	#elif defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		#define IS_LITTLE_ENDIAN 0
	#else
		#error "Cannot determine endianness"
	#endif
#endif

#ifndef USE_Z_ALIAS
#define USE_Z_ALIAS
#endif

#ifndef USE_ZUNIT_HELPER
#define USE_ZUNIT_HELPER
#endif

#include <ostream>
#include <vector>
#include <math.h>

#define WIN32_LEAN_AND_MEAN
#include <minwindef.h>
#include <objidl.h>
#include <windef.h>

namespace GDIPLUS_BOUNDARY {

	#include "zgdiplusinit.h"

}

// forward declaration

struct Point ;
struct PointF ;
struct Size ;
struct SizeF ;
struct Quad ;
struct QuadF ;

// zunit alias

#ifdef USE_Z_ALIAS

typedef unsigned char uint8 ;

#endif

// template spesialize for type checking

#ifdef USE_ZUNIT_HELPER

template <typename> 
struct is_size_unit_ {
	static constexpr bool val = false ;
} ;

template <> 
struct is_size_unit_<Size> {
	static constexpr bool val = true ;
} ;

template <> 
struct is_size_unit_<SizeF> {
	static constexpr bool val = true ;
} ;

template <typename> 
struct is_point_unit_ {
	static constexpr bool val = false ;
} ;

template <> 
struct is_point_unit_<Point> {
	static constexpr bool val = true ;
} ;

template <> 
struct is_point_unit_<PointF> {
	static constexpr bool val = true ;
} ;

template <typename> struct is_quad_unit_ {
	static constexpr bool val = false ;
} ;

template <> struct is_quad_unit_<Quad> {
	static constexpr bool val = true ;
} ;

template <> struct is_quad_unit_<QuadF> {
	static constexpr bool val = true ;
} ;

template <typename T> 
constexpr bool is_point_unit = is_point_unit_<T>::val ;

template <typename T> 
constexpr bool is_size_unit = is_size_unit_<T>::val ;

template <typename T> 
constexpr bool is_pair_unit = is_point_unit<T> || is_size_unit<T> ;

template <typename T>
constexpr bool is_quad_unit = is_quad_unit_<T>::val ;

template <typename T>
constexpr bool is_zunit = is_pair_unit<T> || is_quad_unit<T> ;

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

// implementation zunit.h

struct Point {
	float x, y ;

	constexpr Point() noexcept : x(0.0f), y(0.0f) {}

	template <typename T>
	constexpr Point(T v) noexcept requires std::is_arithmetic_v<T> : x(v), y(v) {}

	template <typename T>
	constexpr Point(T x, T y) noexcept requires std::is_arithmetic_v<T> : x(x), y(y) {}

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

	operator GDIPLUS_BOUNDARY::Gdiplus::PointF() const noexcept {
		return {x, y} ;
	}

	operator GDIPLUS_BOUNDARY::Gdiplus::SizeF() const noexcept {
		return {x, y} ;
	}

	operator GDIPLUS_BOUNDARY::Gdiplus::Point() const noexcept {
		return {static_cast<int>(x), static_cast<int>(y)} ;
	}

	operator GDIPLUS_BOUNDARY::Gdiplus::Size() const noexcept {
		return {static_cast<int>(x), static_cast<int>(y)} ;
	}

} ;

constexpr Point operator+(const Point& a, const Point& b) noexcept  { 
	return {
		a.x + b.x, 
		a.y + b.y
	} ; 
}

constexpr Point operator-(const Point& a, const Point& b) noexcept  { 
	return {
		a.x - b.x, 
		a.y - b.y
	} ; 
}

constexpr Point operator*(const Point& a, const Point& b) noexcept  { 
	return {
		a.x * b.x, 
		a.y * b.y
	} ; 
}

constexpr Point operator/(const Point& a, const Point& b) noexcept  { 
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

struct Quad {

	float x, y, w, h ;

	constexpr Quad() noexcept : x(0.0f), y(0.0f), w(0.0f), h(0.0f) {}

	template <typename T>
	constexpr Quad(T v) noexcept requires std::is_arithmetic_v<T> : x(static_cast<float>(v)), y(static_cast<float>(v)), w(static_cast<float>(v)), h(static_cast<float>(v)) {}

	template <typename T>
	constexpr Quad(T x, T y, T w, T h) noexcept requires std::is_arithmetic_v<T> : x(static_cast<float>(x)), y(static_cast<float>(y)), w(static_cast<float>(w)), h(static_cast<float>(h)) {}

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
		return x == o.x && y == o.x && w == o.x && h == o.x ; 
	}

	constexpr bool operator!=(const Quad& o) const noexcept { 
		return !(*this == o) ; 
	}

	constexpr operator tagRECT() const noexcept { 
		return {
			static_cast<long>(x), 
			static_cast<long>(y), 
			static_cast<long>(w) + static_cast<long>(x), 
			static_cast<long>(h) +  static_cast<long>(y) 
		} ; 
	}

	constexpr operator _RECTL() const noexcept { 
		return {
			static_cast<long>(x), 
			static_cast<long>(y), 
			static_cast<long>(w) + static_cast<long>(x), 
			static_cast<long>(h) +  static_cast<long>(y) 
		} ; 
	}

	operator GDIPLUS_BOUNDARY::Gdiplus::Rect() const noexcept {
		return {static_cast<int>(x), static_cast<int>(y), static_cast<int>(w), static_cast<int>(h)} ;
	}

	operator GDIPLUS_BOUNDARY::Gdiplus::RectF() const noexcept {
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

#ifdef IS_LITTLE_ENDIAN

enum class RGBA : uint8 {
	RED		= 3,
	GREEN	= 2,
	BLUE	= 1,
	ALPHA	= 0,
	R		= RED,
	G		= GREEN,
	B		= BLUE,
	A		= ALPHA
} ;

#else

enum class RGBA : uint8 {
	RED		= 0,
	GREEN	= 1,
	BLUE	= 2,
	ALPHA	= 3,
	R		= RED,
	G		= GREEN,
	B		= BLUE,
	A		= ALPHA
} ;

#endif

static_assert(static_cast<uint8>(RGBA::R) == 3 || static_cast<uint8>(RGBA::R) == 0, "Unexpected RGBA channel layout") ;

// error handler

namespace error_handler {

	struct color_access_out_of_bound {
		const char* what() const noexcept ;
	} ;

}

class Color {
private :
	union Color_ {
		unsigned data ;
		uint8 bytes[sizeof(unsigned)] ;

		constexpr Color_(Color_&&) noexcept = delete ;
		constexpr Color_& operator=(Color_&&) noexcept = delete ;

		constexpr Color_(unsigned data) noexcept : data(data) {}

		constexpr Color_(uint8 r, uint8 g, uint8 b, uint8 a = 255U) noexcept : data(r << 24 | g << 16 | b << 8 | a ) {}

		constexpr Color_(const Color_& o) noexcept : data(o.data) {}

		constexpr Color_& operator=(const Color_& o) noexcept {
			if (this != &o) 
				data = o.data ;
			return *this ;
		}
	} color_ ;

public :
	constexpr Color(Color&& o) noexcept = delete ;

	constexpr Color& operator=(Color&& o) noexcept = delete ;

	constexpr Color() noexcept : color_(0, 0, 0, 255) {}

	constexpr Color(uint8 r, uint8 g, uint8 b, uint8 a) noexcept : color_(r, g, b, a) {}

	constexpr Color(const Color& o) noexcept : color_(o.color_) {}

	constexpr Color& operator=(const Color& o) noexcept {
		if (this != &o)
			color_ = o.color_ ;
		return *this ;
	}

	constexpr const uint8& operator[](RGBA channel) const noexcept {
		return color_.bytes[static_cast<uint8>(channel)] ;
	}

	constexpr uint8& operator[](RGBA channel) noexcept {
		return color_.bytes[static_cast<uint8>(channel)] ;
	}

	const uint8& operator[](uint8 channel) const {
		if (channel > 3)
			throw error_handler::color_access_out_of_bound() ;
		return color_.bytes[channel] ;
	}

	uint8& operator[](uint8 channel) {
		if (channel > 3)
			throw error_handler::color_access_out_of_bound() ;
		return color_.bytes[channel] ;
	}

	constexpr const uint8* begin() const noexcept {
		return color_.bytes ;
	}

	constexpr uint8* begin() noexcept {
		return color_.bytes ;
	}

	constexpr const uint8* end() const noexcept {
		return color_.bytes + sizeof(unsigned) ;
	}

	constexpr uint8* end() noexcept {
		return color_.bytes + sizeof(unsigned) ;
	}

	constexpr operator COLORREF() const noexcept {
		return color_.bytes[0] << 16 | color_.bytes[1] << 8 | color_.bytes[2] ;
	}

	operator GDIPLUS_BOUNDARY::Gdiplus::Color() const noexcept {
		return color_.bytes[3] << 24 | color_.bytes[2] << 16 | color_.bytes[1] << 8 | color_.bytes[0] ;
	}

	const std::string getHex() const noexcept {
		return to_hex(color_.data) ;
	}
} ;

inline std::ostream& operator<<(std::ostream& os, const Color& c) noexcept  {
	return os << "{" << static_cast<int>(c[3]) << ", " << static_cast<int>(c[2]) << ", " << static_cast<int>(c[1]) << ", " << static_cast<int>(c[0])  << "{\n" ;
}

std::ostream& operator<<(std::ostream& os, const Color& c) noexcept ;

using Vertex = std::vector<Point> ;

#ifdef USE_ZUNIT_HELPER
#undef USE_ZUNIT_HELPER
#endif

#ifdef USE_Z_ALIAS
#undef USE_Z_ALIAS
#endif

#ifdef IS_LITTLE_ENDIAN
    #undef IS_LITTLE_ENDIAN
#endif