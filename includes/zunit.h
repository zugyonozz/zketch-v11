#pragma once

#include <ostream>
#include <algorithm>
#include <vector>
#include <type_traits>
#include "zdef.h"

#define USE_ZUNIT_HELPER

struct Point {
    sllong x = 0LL, y = 0LL ;

    constexpr Point() noexcept = default ;
	constexpr Point(const Point&) noexcept = default ;
	constexpr Point& operator=(const Point&) noexcept = default ;
	
	constexpr Point(sllong v) noexcept : x(v), y(v) {}
    
	constexpr Point(sllong x, sllong y) noexcept : x(x), y(y) {}

	constexpr Point(const tagPOINT& o) noexcept : x(o.x), y(o.y) {}
	
	constexpr Point(const _POINTL& o) noexcept : x(o.x), y(o.y) {}
	
	constexpr Point(const tagSIZE& o) noexcept : x(o.cx), y(o.cy) {}
	
	constexpr Point(const tagPOINTS& o) noexcept : x(o.x), y(o.y) {}

	template <typename T, typename U, typename = std::enable_if_t<std::is_arithmetic_v<std::remove_cv_t<std::remove_reference_t<T>>> && std::is_arithmetic_v<std::remove_cv_t<std::remove_reference_t<U>>>>> 
	constexpr Point(const std::pair<T&, U&>& p) noexcept : x(static_cast<sllong>(p.first)), y(static_cast<sllong>(p.second)) {}
	
	constexpr Point& operator=(sllong v) noexcept { 
		x = y = v ; 
		return *this ; 
	}

	template <typename T, typename U, typename = std::enable_if_t<std::is_arithmetic_v<std::remove_cv_t<std::remove_reference_t<T>>> && std::is_arithmetic_v<std::remove_cv_t<std::remove_reference_t<U>>>>> 
	constexpr Point& operator=(const std::pair<T&, U&>& p) noexcept {
		x = static_cast<sllong>(p.first) ;
		y = static_cast<sllong>(p.second) ;
		return *this ;
	}
	
    constexpr Point operator+() const noexcept { 
		return *this ; 
	}

    constexpr Point operator-() const noexcept { 
		return {static_cast<sllong>(-x), static_cast<sllong>(-y)} ; 
	}

	constexpr Point& operator+=(const Point& o) noexcept { 
		x += o.x ; 
		y += o.y ; 
		return *this ; 
	}

	constexpr Point& operator-=(const Point& o) noexcept { 
		x -= o.x ; 
		y -= o.y ; 
		return *this ; 
	}

	constexpr Point& operator*=(const Point& o) noexcept { 
		x *= o.x ; 
		y *= o.y ; 
		return *this ; 
	}

	constexpr Point& operator/=(const Point& o) noexcept { 
		x /= o.x ; 
		y /= o.y ; 
		return *this ; 
	}

	constexpr Point& operator+=(sllong v) noexcept { 
		x += v ; 
		y += v ; 
		return *this ; 
	}

	constexpr Point& operator-=(sllong v) noexcept { 
		x -= v ; 
		y -= v ; 
		return *this ; 
	}

	constexpr Point& operator*=(sllong v) noexcept { 
		x *= v ; 
		y *= v ; 
		return *this ; 
	}

	constexpr Point& operator/=(sllong v) noexcept { 
		x /= v ; 
		y /= v ; 
		return *this ; 
	}

    constexpr bool operator==(const Point& o) const noexcept { 
		return x == o.x && y == o.y ; 
	}

    constexpr bool operator!=(const Point& o) const noexcept { 
		return !(*this == o) ; 
	}

	operator tagPOINT() const noexcept { 
		return {
			static_cast<slong>(x), 
			static_cast<slong>(y)
		} ; 
	}

	operator _POINTL() const noexcept { 
		return {
			static_cast<slong>(x), 
			static_cast<slong>(y)
		} ; 
	}

	operator tagSIZE() const noexcept { 
		return {
			static_cast<slong>(x), 
			static_cast<slong>(y)
		} ; 
	}

	operator tagPOINTS() const noexcept { 
		return {
			static_cast<sshort>(x), 
			static_cast<sshort>(y)
		} ; 
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

constexpr Point operator+(const Point& a, sllong v) noexcept { 
	return {
		a.x + v, 
		a.y + v
	} ; 
}

constexpr Point operator-(const Point& a, sllong v) noexcept { 
	return {
		a.x - v, 
		a.y - v
	} ; 
}

constexpr Point operator*(const Point& a, sllong v) noexcept { 
	return {
		a.x * v, 
		a.y * v
	} ; 
}

constexpr Point operator/(const Point& a, sllong v) noexcept { 
	return {
		a.x / v, 
		a.y / v
	} ; 
}

constexpr Point operator+(sllong v, const Point& a) noexcept { 
	return a + v ; 
}

constexpr Point operator*(sllong v, const Point& a) noexcept { 
	return a * v ; 
}

constexpr Point operator-(sllong v, const Point& a) noexcept { 
	return {
		v - a.x, 
		v - a.y
	} ; 
}

constexpr Point operator/(sllong v, const Point& a) noexcept { 
	return {
		v / a.x, 
		v / a.y
	} ; 
}

#ifdef ZUNIT_DEBUG

template <typename T> 
std::ostream& operator<<(std::ostream& os, const Point<T>& pt) const noexcept {
	return os << "{" << pt.x << ", " << pt.y << "}" ;
}

#endif

struct Quad {
	sllong x, y ; 
	uint w, h ;

	constexpr Quad() noexcept : x(0), y(0), w(0), h(0) {}

	constexpr Quad(sllong v) noexcept : x(v), y(v), w(v), h(v) {}

	constexpr Quad(sllong x, sllong y, uint w, uint h) noexcept : x(x), y(y), w(w), h(h) {}

	constexpr Quad(const Point& pos, const Point& size) noexcept : x(pos.x), y(pos.y), w(size.x), h(size.y) {}

	constexpr Quad(const Quad& o) noexcept : x(o.x), y(o.y), w(o.w), h(o.h) {}

	constexpr Quad(const tagRECT& o) noexcept : x(o.left), y(o.top), w(o.right - o.left), h(o.bottom - o.top) {}

	constexpr Quad(const _RECTL& o) noexcept : x(o.left), y(o.top), w(o.right - o.left), h(o.bottom - o.top) {}

	constexpr Quad& operator=(sllong v) noexcept { 
		x = y = w = h = v ; 
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

	constexpr Quad& operator+=(sllong v) noexcept { 
		x += v ; 
		y += v ; 
		w += v ; 
		h += v ; 
		return *this ; 
	}

	constexpr Quad& operator-=(sllong v) noexcept { 
		x -= v ; 
		y -= v ; 
		w -= v ; 
		h -= v ; 
		return *this ; 
	}

	constexpr Quad& operator*=(sllong v) noexcept { 
		x *= v ; 
		y *= v ; 
		w *= v ; 
		h *= v ; 
		return *this ; 
	}

	constexpr Quad& operator/=(sllong v) noexcept { 
		x /= v ; 
		y /= v ; 
		w /= v ; 
		h /= v ; 
		return *this ; 
	}

    constexpr bool operator==(const Quad& o) const noexcept { 
		return x == o.x && y == o.y && w == o.w && h == o.h ; 
	}

    constexpr bool operator!=(const Quad& o) const noexcept { 
		return !(*this == o) ; 
	}

	operator tagRECT() const noexcept { 
		return {
			static_cast<slong>(x), 
			static_cast<slong>(y), 
			static_cast<slong>(x) + static_cast<slong>(w), 
			static_cast<slong>(y) +  static_cast<slong>(h) 
		} ; 
	}

	operator _RECTL() const noexcept { 
		return {
			static_cast<slong>(x), 
			static_cast<slong>(y), 
			static_cast<slong>(x) + static_cast<slong>(w), 
			static_cast<slong>(y) +  static_cast<slong>(h) 
		} ; 
	}

	constexpr std::pair<const sllong&, const sllong&> getPos() const noexcept { 
		return {x, y} ; 
	}

	constexpr std::pair<sllong&, sllong&> getPos() noexcept { 
		return {x, y} ; 
	}

	constexpr std::pair<const uint&, const uint&> getSize() const noexcept { 
		return {w, h} ; 
	}

	constexpr std::pair<uint&, uint&> getSize() noexcept { 
		return {w, h} ; 
	}

	constexpr Quad& setPos(sllong x, sllong y) noexcept { 
		this->x = x ; 
		this->y = y ; 
		return *this ;
	}

	constexpr Quad& setPos(const Point& pos) noexcept { 
		x = pos.x ; 
		y = pos.y ; 
		return *this ;
	}

	constexpr Quad& setSize(sllong w, sllong h) noexcept { 
		this->w = w ; 
		this->h = h ; 
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

constexpr Quad operator+(const Quad& a, sllong v) noexcept { 
	return {
		a.x + v, 
		a.y + v, 
		static_cast<uint>(a.w + v), 
		static_cast<uint>(a.h + v)
	} ; 
}

constexpr Quad operator-(const Quad& a, sllong v) noexcept { 
	return {
		a.x - v, 
		a.y - v, 
		static_cast<uint>(a.w - v), 
		static_cast<uint>(a.h - v)
	} ; 
}

constexpr Quad operator*(const Quad& a, sllong v) noexcept { 
	return {
		a.x * v, 
		a.y * v, 
		static_cast<uint>(a.w * v), 
		static_cast<uint>(a.h * v)
	} ; 
}

constexpr Quad operator/(const Quad& a, sllong v) noexcept { 
	return {
		a.x / v, 
		a.y / v, 
		static_cast<uint>(a.w / v), 
		static_cast<uint>(a.h / v)
	} ; 
}

constexpr Quad operator+(sllong v, const Quad& a) noexcept { 
	return a + v ; 
}

constexpr Quad operator-(sllong v, const Quad& a) noexcept { 
	return {
		v - a.x, 
		v - a.y, 
		static_cast<uint>(v - a.w), 
		static_cast<uint>(v - a.h)
	} ; 
}

constexpr Quad operator*(sllong v, const Quad& a) noexcept { 
	return a * v ; 
}

constexpr Quad operator/(sllong v, const Quad& a) noexcept { 
	return {
		v / a.x, 
		v / a.y, 
		static_cast<uint>(v / a.w), 
		static_cast<uint>(v / a.h)
	} ; 
}

#ifdef ZUNIT_DEBUG

template <typename T> 
std::ostream& operator<<(std::ostream& os, const Quad<T>& q) const noexcept {
	return os << "{" << q.x << ", " << q.y << ", " << q.w << ", " << q.h << "}" ;
}

#endif

#ifdef USE_ZUNIT_HELPER

constexpr uchar cclamp(uchar val, uchar lim) noexcept { 
	return val > lim ? lim : val ; 
}

#endif

class Color {
private :
	union C {
		uint d = 0 ;
		uchar b[sizeof(uint)] ;
	} c ;

public :
	enum elements : uchar { A, B, G, R } ;

	constexpr Color() noexcept : c{} {}

	constexpr Color(COLORREF d) noexcept { 
		c.d = d ;
	}

	constexpr Color(uchar r, uchar g, uchar b, uchar a = 0) noexcept : c{} {
		c.b[0] = a ;
		c.b[1] = b ;
		c.b[2] = g ;
		c.b[3] = r ;
	}

	constexpr Color(const Color& o) noexcept : c(o.c) {}

    constexpr Color& operator=(COLORREF v) noexcept { 
		c.d = static_cast<uint>(v) ;
		return *this ; 
	}

	constexpr Color& operator=(const Color& o) noexcept { 
		c = o.c ;
		return *this ; 
	}

	constexpr Color& operator+=(const Color& o) noexcept { 
		c.b[0] = cclamp(c.b[0] + o.c.b[0], 255) ;
		c.b[1] = cclamp(c.b[1] + o.c.b[1], 255) ;
		c.b[2] = cclamp(c.b[2] + o.c.b[2], 255) ;
		c.b[3] = cclamp(c.b[3] + o.c.b[3], 255) ;
		return *this ; 
	}

	constexpr Color& operator-=(const Color& o) noexcept { 
		c.b[0] = (c.b[0] > o.c.b[0]) ? c.b[0] - o.c.b[0] : 0 ;
		c.b[1] = (c.b[1] > o.c.b[1]) ? c.b[1] - o.c.b[1] : 0 ;
		c.b[2] = (c.b[2] > o.c.b[2]) ? c.b[2] - o.c.b[2] : 0 ;
		c.b[3] = (c.b[3] > o.c.b[3]) ? c.b[3] - o.c.b[3] : 0 ;
		return *this ; 
	}

	constexpr Color& operator*=(const Color& o) noexcept { 
		c.b[0] = cclamp(c.b[0] * o.c.b[0], 255) ;
		c.b[1] = cclamp(c.b[1] * o.c.b[1], 255) ;
		c.b[2] = cclamp(c.b[2] * o.c.b[2], 255) ;
		c.b[3] = cclamp(c.b[3] * o.c.b[3], 255) ;
		return *this ; 
	}

	constexpr Color& operator/=(const Color& o) noexcept { 
		if (o.c.b[0] != 0) 
			c.b[0] /= o.c.b[0] ; 
		if (o.c.b[1] != 0) 
			c.b[1] /= o.c.b[1] ; 
		if (o.c.b[2] != 0) 
			c.b[2] /= o.c.b[2] ; 
		if (o.c.b[3] != 0) 
			c.b[3] /= o.c.b[3] ; 
		return *this ; 
	}

	constexpr uchar& operator[](elements e) noexcept {
		return c.b[e] ;
	}

	constexpr const uchar& operator[](elements e) const noexcept {
		return c.b[e] ;
	}

	constexpr uchar& operator[](uchar i) noexcept {
		return c.b[i] ;
	}

	constexpr const uchar& operator[](uchar i) const noexcept {
		return c.b[i] ;
	}

	constexpr explicit operator COLORREF() const noexcept { 
		return RGB(c.b[3], c.b[2], c.b[1]) ; 
	} 

	constexpr uchar& alpha() noexcept { 
		return c.b[0] ; 
	} 

	constexpr const uchar& alpha() const noexcept { 
		return c.b[0] ; 
	} 
} ;

constexpr Color operator+(const Color& a, const Color& b) noexcept { 
	return Color { 
		cclamp(a[Color::R] + b[Color::R], 255), 
		cclamp(a[Color::G] + b[Color::G], 255), 
		cclamp(a[Color::B] + b[Color::B], 255), 
		cclamp(a[Color::A] + b[Color::A], 255) 
	} ; 
}

constexpr Color operator-(const Color& a, const Color& b) { 
	return Color { 
		(a[Color::R] > b[Color::R]) ? static_cast<uchar>(a[Color::R] - b[Color::R]) : static_cast<uchar>(0), 
		(a[Color::G] > b[Color::G]) ? static_cast<uchar>(a[Color::G] - b[Color::G]) : static_cast<uchar>(0), 
		(a[Color::B] > b[Color::B]) ? static_cast<uchar>(a[Color::B] - b[Color::B]) : static_cast<uchar>(0), 
		(a[Color::A] > b[Color::A]) ? static_cast<uchar>(a[Color::A] - b[Color::A]) : static_cast<uchar>(0) 
	} ; 
}

constexpr Color operator*(const Color& a, const Color& b) noexcept  { 
	return Color { 
		cclamp(a[Color::R] * b[Color::R], 255), 
		cclamp(a[Color::G] * b[Color::G], 255), 
		cclamp(a[Color::B] * b[Color::B], 255), 
		cclamp(a[Color::A] * b[Color::A], 255) 
	} ; 
}

constexpr Color operator/(const Color& a, const Color& b) noexcept { 
	return Color { 
		(b[Color::R] != 0) ? static_cast<uchar>(a[Color::R] / b[Color::R]) : static_cast<uchar>(0), 
		(b[Color::G] != 0) ? static_cast<uchar>(a[Color::G] / b[Color::G]) : static_cast<uchar>(0), 
		(b[Color::B] != 0) ? static_cast<uchar>(a[Color::B] / b[Color::B]) : static_cast<uchar>(0), 
		(b[Color::A] != 0) ? static_cast<uchar>(a[Color::A] / b[Color::A]) : static_cast<uchar>(0) 
	} ; 
}

constexpr Color operator+(const Color& a, uchar v) noexcept { 
	return Color { 
		cclamp(a[Color::R] + v, 255), 
		cclamp(a[Color::G] + v, 255), 
		cclamp(a[Color::B] + v, 255), 
		cclamp(a[Color::A] + v, 255) 
	} ; 
}

constexpr Color operator-(const Color& a, uchar v) noexcept { 
	return Color { 
		(a[Color::R] > v) ? static_cast<uchar>(a[Color::R] - v) : static_cast<uchar>(0), 
		(a[Color::G] > v) ? static_cast<uchar>(a[Color::G] - v) : static_cast<uchar>(0), 
		(a[Color::B] > v) ? static_cast<uchar>(a[Color::B] - v) : static_cast<uchar>(0), 
		(a[Color::A] > v) ? static_cast<uchar>(a[Color::A] - v) : static_cast<uchar>(0) 
	} ; 
}

constexpr Color operator*(const Color& a, uchar v) noexcept { 
	return Color { 
		cclamp(a[Color::R] * v, 255), 
		cclamp(a[Color::G] * v, 255), 
		cclamp(a[Color::B] * v, 255), 
		cclamp(a[Color::A] * v, 255) 
	} ; 
}

constexpr Color operator/(const Color& a, uchar v) noexcept { 
	return Color { 
		(v != 0) ? static_cast<uchar>(a[Color::R] / v) : static_cast<uchar>(0), 
		(v != 0) ? static_cast<uchar>(a[Color::G] / v) : static_cast<uchar>(0), 
		(v != 0) ? static_cast<uchar>(a[Color::B] / v) : static_cast<uchar>(0), 
		(v != 0) ? static_cast<uchar>(a[Color::A] / v) : static_cast<uchar>(0) 
	} ; 
}

constexpr auto operator+(uchar v, const Color& a) noexcept { 
	return a + v; 
}

constexpr auto operator-(uchar v, const Color& a) noexcept { 
	return Color{ 
		(v > a[Color::R]) ? static_cast<uchar>(v - a[Color::R]) : static_cast<uchar>(0), 
		(v > a[Color::G]) ? static_cast<uchar>(v - a[Color::G]) : static_cast<uchar>(0), 
		(v > a[Color::B]) ? static_cast<uchar>(v - a[Color::B]) : static_cast<uchar>(0), 
		(v > a[Color::A]) ? static_cast<uchar>(v - a[Color::A]) : static_cast<uchar>(0) 
	} ; 
}

constexpr auto operator*(uchar v, const Color& a) noexcept { 
	return a * v; 
}

constexpr auto operator/(uchar v, const Color& a) noexcept { 
	return Color{ 
		(a[Color::R] != 0) ? static_cast<uchar>(v / a[Color::R]) : static_cast<uchar>(0), 
		(a[Color::G] != 0) ? static_cast<uchar>(v / a[Color::G]) : static_cast<uchar>(0), 
		(a[Color::B] != 0) ? static_cast<uchar>(v / a[Color::B]) : static_cast<uchar>(0), 
		(a[Color::A] != 0) ? static_cast<uchar>(v / a[Color::A]) : static_cast<uchar>(0) 
	} ; 
}

#ifdef ZUNIT_DEBUG

std::ostream& operator<<(std::ostream& os, const Color& c) noexcept {
	return os << "{" << static_cast<uint>(c[Color::R]) << ", " << static_cast<uint>(c[Color::G]) << ", " << static_cast<uint>(c[Color::B]) << ", " << static_cast<uint>(c[Color::A]) << "}" ;
}

#endif

using Size = Point ;
using Pos = Point ;
using Rect = Quad ;
using RGBA = Color ;
using Vertex = std::vector<POINT> ;

#undef USE_ZUNIT_HELPER