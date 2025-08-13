#pragma once

#include <ostream>
#include <algorithm>
#include <type_traits>
#include "zdef.h"

#define USE_Z_ALIAS
#define USE_ZUNIT_HELPER

#ifdef USE_Z_ALIAS

template <bool cond, typename T = void> 
using EI = std::enable_if_t<cond, T> ;

template <typename ... Ts> 
using CT = std::common_type_t<Ts...> ;

#endif

template <typename T, typename = EI<std::is_arithmetic_v<T>>> 
struct Point {
    T x, y ;

    constexpr Point() noexcept : x(0), y(0) {}
	
	template <typename U, typename = EI<std::is_arithmetic_v<U>>> 
	constexpr Point(U v) noexcept : x(v), y(v) {}
    
	template <typename U, typename = EI<std::is_arithmetic_v<U>>> 
	constexpr Point(U x, U y) noexcept : x(x), y(y) {}
	
    template <typename U> 
	constexpr Point(const Point<U>& o) noexcept : x(static_cast<T>(o.x)), y(static_cast<T>(o.y)) {}

	constexpr Point(const tagPOINT& o) noexcept : x(static_cast<T>(o.x)), y(static_cast<T>(o.y)) {}
	
	constexpr Point(const _POINTL& o) noexcept : x(static_cast<T>(o.x)), y(static_cast<T>(o.y)) {}
	
	constexpr Point(const tagSIZE& o) noexcept : x(static_cast<T>(o.cx)), y(static_cast<T>(o.cy)) {}
	
	constexpr Point(const tagPOINTS& o) noexcept : x(static_cast<T>(o.x)), y(static_cast<T>(o.y)) {}
	

	template <typename U, typename = EI<std::is_arithmetic_v<U>>> 
	constexpr Point& operator=(U v) noexcept { 
		x = y = v ; 
		return *this ; 
	}
	
	template <typename U> 
	constexpr Point& operator=(const Point<U>& o) noexcept { 
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

    template <typename U> 
	constexpr Point& operator+=(const Point<U>& o) noexcept { 
		x += o.x ; 
		y += o.y ; 
		return *this ; 
	}

    template <typename U> 
	constexpr Point& operator-=(const Point<U>& o) noexcept { 
		x -= o.x ; 
		y -= o.y ; 
		return *this ; 
	}

    template <typename U> 
	constexpr Point& operator*=(const Point<U>& o) noexcept { 
		x *= o.x ; 
		y *= o.y ; 
		return *this ; 
	}

    template <typename U> 
	constexpr Point& operator/=(const Point<U>& o) noexcept { 
		x /= o.x ; 
		y /= o.y ; 
		return *this ; 
	}

    template <typename U, typename = EI<std::is_arithmetic_v<U>>> 
	constexpr Point& operator+=(U v) noexcept { 
		x += v ; 
		y += v ; 
		return *this ; 
	}

    template <typename U, typename = EI<std::is_arithmetic_v<U>>> 
	constexpr Point& operator-=(U v) noexcept { 
		x -= v ; 
		y -= v ; 
		return *this ; 
	}

    template <typename U, typename = EI<std::is_arithmetic_v<U>>> 
	constexpr Point& operator*=(U v) noexcept { 
		x *= v ; 
		y *= v ; 
		return *this ; 
	}

    template <typename U, typename = EI<std::is_arithmetic_v<U>>> 
	constexpr Point& operator/=(U v) noexcept { 
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

	explicit operator tagPOINT() const noexcept { 
		return {
			static_cast<slong>(x), 
			static_cast<slong>(y)
		} ; 
	}

	explicit operator _POINTL() const noexcept { 
		return {
			static_cast<slong>(x), 
			static_cast<slong>(y)
		} ; 
	}

	explicit operator tagSIZE() const noexcept { 
		return {
			static_cast<slong>(x), 
			static_cast<slong>(y)
		} ; 
	}

	explicit operator tagPOINTS() const noexcept { 
		return {
			static_cast<sshort>(x), 
			static_cast<sshort>(y)
		} ; 
	}

} ;

template <typename T, typename U> 
constexpr auto operator+(const Point<T>& a, const Point<U>& b) noexcept -> Point<CT<T, U>> { 
	return {
		static_cast<CT<T, U>>(a.x) + static_cast<CT<T, U>>(b.x), 
		static_cast<CT<T, U>>(a.y) + static_cast<CT<T, U>>(b.y)
	} ; 
}

template <typename T, typename U> 
constexpr auto operator-(const Point<T>& a, const Point<U>& b) noexcept -> Point<CT<T, U>> { 
	return {
		static_cast<CT<T, U>>(a.x) - static_cast<CT<T, U>>(b.x), 
		static_cast<CT<T, U>>(a.y) - static_cast<CT<T, U>>(b.y)
	} ; 
}

template <typename T, typename U> 
constexpr auto operator*(const Point<T>& a, const Point<U>& b) noexcept -> Point<CT<T, U>> { 
	return {
		static_cast<CT<T, U>>(a.x) * static_cast<CT<T, U>>(b.x), 
		static_cast<CT<T, U>>(a.y) * static_cast<CT<T, U>>(b.y)
	} ; 
}

template <typename T, typename U> 
constexpr auto operator/(const Point<T>& a, const Point<U>& b) noexcept -> Point<CT<T, U>> { 
	return {
		static_cast<CT<T, U>>(a.x) / static_cast<CT<T, U>>(b.x), 
		static_cast<CT<T, U>>(a.y) / static_cast<CT<T, U>>(b.y)
	} ; 
}

template <typename T, typename U, typename = EI<std::is_arithmetic_v<U>>> 
constexpr auto operator+(const Point<T>& a, U v) noexcept -> Point<CT<T, U>> { 
	return {
		static_cast<CT<T, U>>(a.x) + static_cast<CT<T, U>>(v), 
		static_cast<CT<T, U>>(a.y) + static_cast<CT<T, U>>(v)
	} ; 
}

template <typename T, typename U, typename = EI<std::is_arithmetic_v<U>>> 
constexpr auto operator-(const Point<T>& a, U v) noexcept -> Point<CT<T, U>> { 
	return {
		static_cast<CT<T, U>>(a.x) - static_cast<CT<T, U>>(v), 
		static_cast<CT<T, U>>(a.y) - static_cast<CT<T, U>>(v)
	} ; 
}

template <typename T, typename U, typename = EI<std::is_arithmetic_v<U>>> 
constexpr auto operator*(const Point<T>& a, U v) noexcept -> Point<CT<T, U>> { 
	return {
		static_cast<CT<T, U>>(a.x) * static_cast<CT<T, U>>(v), 
		static_cast<CT<T, U>>(a.y) * static_cast<CT<T, U>>(v)
	} ; 
}

template <typename T, typename U, typename = EI<std::is_arithmetic_v<U>>> 
constexpr auto operator/(const Point<T>& a, U v) noexcept -> Point<CT<T, U>> { 
	return {
		static_cast<CT<T, U>>(a.x) / static_cast<CT<T, U>>(v), 
		static_cast<CT<T, U>>(a.y) / static_cast<CT<T, U>>(v)
	} ; 
}

template <typename T, typename U, typename = EI<std::is_arithmetic_v<U>>> 
constexpr auto operator+(U v, const Point<T>& a) noexcept -> Point<CT<T, U>> { 
	return a + v ; 
}

template <typename T, typename U, typename = EI<std::is_arithmetic_v<U>>> 
constexpr auto operator*(U v, const Point<T>& a) noexcept -> Point<CT<T, U>> { 
	return a * v ; 
}

template <typename T, typename U, typename = EI<std::is_arithmetic_v<U>>> 
constexpr auto operator-(U v, const Point<T>& a) noexcept -> Point<CT<T, U>> { 
	return {
		static_cast<CT<T, U>>(v) - static_cast<CT<T, U>>(a.x), 
		static_cast<CT<T, U>>(v) - static_cast<CT<T, U>>(a.y)
	} ; 
}

template <typename T, typename U, typename = EI<std::is_arithmetic_v<U>>> 
constexpr auto operator/(U v, const Point<T>& a) noexcept -> Point<CT<T, U>> { 
	return {
		static_cast<CT<T, U>>(v) / static_cast<CT<T, U>>(a.x), 
		static_cast<CT<T, U>>(v) / static_cast<CT<T, U>>(a.y)
	} ; 
}

#ifdef ZUNIT_DEBUG

template <typename T> 
std::ostream& operator<<(std::ostream& os, const Point<T>& pt) const noexcept {
	return os << "{" << pt.x << ", " << pt.y << "}" ;
}

#endif

template <typename T, typename = EI<std::is_arithmetic_v<T>>> 
struct Quad {
	T x, y, w, h ;

	constexpr Quad() noexcept : x(0), y(0), w(0), h(0) {}

	template <typename U, typename = EI<std::is_arithmetic_v<U>>> 
	constexpr Quad(U v) noexcept : x(v), y(v), w(v), h(v) {}

    template <typename U, typename = EI<std::is_arithmetic_v<U>>> 
	constexpr Quad(U x, U y, U w, U h) noexcept : x(x), y(y), w(w), h(h) {}

	template <typename U> 
	constexpr Quad(const Point<U>& pos, const Point<U>& size) noexcept : x(pos.x), y(pos.y), w(size.x), h(size.y) {}

    template <typename U> 
	constexpr Quad(const Quad<U>& o) noexcept : x(static_cast<T>(o.x)), y(static_cast<T>(o.y)), w(static_cast<T>(o.w)), h(static_cast<T>(o.h)) {}

	constexpr Quad(const tagRECT& o) noexcept : x(o.left), y(o.top), w(o.right - o.left), h(o.bottom - o.top) {}

	constexpr Quad(const _RECTL& o) noexcept : x(o.left), y(o.top), w(o.right - o.left), h(o.bottom - o.top) {}

	template <typename U, typename = EI<std::is_arithmetic_v<U>>> 
	constexpr Quad& operator=(U v) noexcept { 
		x = y = w = h = v ; 
		return *this ; 
	}

	template <typename U> 
	constexpr Quad& operator=(const Quad<U>& o) noexcept { 
		x = o.x ; y = o.y ; w = o.w ; h = o.h ; 
		return *this ; 
	}

    constexpr Quad operator+() const noexcept { 
		return *this ; 
	}

    constexpr Quad operator-() const noexcept { 
		return {-x, -y, w, h} ; 
	}

    template <typename U> 
	constexpr Quad& operator+=(const Quad<U>& o) noexcept { 
		x += o.x ; 
		y += o.y ; 
		w += o.w ; 
		h += o.h ; 
		return *this ; 
	}

    template <typename U> 
	constexpr Quad& operator-=(const Quad<U>& o) noexcept { 
		x -= o.x ; 
		y -= o.y ; 
		w -= o.w ; 
		h -= o.h ; 
		return *this ; 
	}

    template <typename U> 
	constexpr Quad& operator*=(const Quad<U>& o) noexcept { 
		x *= o.x ; 
		y *= o.y ; 
		w *= o.w ; 
		h *= o.h ; 
		return *this ; 
	}

    template <typename U> 
	constexpr Quad& operator/=(const Quad<U>& o) noexcept { 
		x /= o.x ; 
		y /= o.y ; 
		w /= o.w ; 
		h /= o.h ; 
		return *this ; 
	}

    template <typename U, typename = EI<std::is_arithmetic_v<U>>> 
	constexpr Quad& operator+=(U v) noexcept { 
		x += v ; 
		y += v ; 
		w += v ; 
		h += v ; 
		return *this ; 
	}

    template <typename U, typename = EI<std::is_arithmetic_v<U>>> 
	constexpr Quad& operator-=(U v) noexcept { 
		x -= v ; 
		y -= v ; 
		w -= v ; 
		h -= v ; 
		return *this ; 
	}

    template <typename U, typename = EI<std::is_arithmetic_v<U>>> 
	constexpr Quad& operator*=(U v) noexcept { 
		x *= v ; 
		y *= v ; 
		w *= v ; 
		h *= v ; 
		return *this ; 
	}

    template <typename U, typename = EI<std::is_arithmetic_v<U>>> 
	constexpr Quad& operator/=(U v) noexcept { 
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

	explicit operator tagRECT() const noexcept { 
		return {
			static_cast<slong>(x), 
			static_cast<slong>(y), 
			static_cast<slong>(x) + static_cast<slong>(w), 
			static_cast<slong>(y) +  static_cast<slong>(h) 
		} ; 
	}

	explicit operator _RECTL() const noexcept { 
		return {
			static_cast<slong>(x), 
			static_cast<slong>(y), 
			static_cast<slong>(x) + static_cast<slong>(w), 
			static_cast<slong>(y) +  static_cast<slong>(h) 
		} ; 
	}

	constexpr Point<T> getPos() const noexcept { 
		return {x, y} ; 
	}

	constexpr Point<T> getSize() const noexcept { 
		return {w, h} ; 
	}

	template <typename U, typename = EI<std::is_arithmetic_v<U>>> 
	constexpr Quad& setPos(U x, U y) noexcept { 
		this->x = x ; 
		this->y = y ; 
		return *this ;
	}

	template <typename U> 
	constexpr Quad& setPos(const Point<U>& pos) noexcept { 
		x = pos.x ; 
		y = pos.y ; 
		return *this ;
	}

	template <typename U, typename = EI<std::is_arithmetic_v<U>>> 
	constexpr Quad& setSize(U w, U h) noexcept { 
		this->w = w ; 
		this->h = h ; 
		return *this ;
	}

	template <typename U> 
	constexpr Quad& setSize(const Point<U>& size) noexcept { 
		w = size.w ; 
		h = size.h ; 
		return *this ;
	}
} ;

template <typename T, typename U> 
constexpr auto operator+(const Quad<T>& a, const Quad<U>& b) noexcept -> Quad<CT<T, U>> { 
	return {
		static_cast<CT<T, U>>(a.x) + static_cast<CT<T, U>>(b.x), 
		static_cast<CT<T, U>>(a.y) + static_cast<CT<T, U>>(b.y), 
		static_cast<CT<T, U>>(a.w) + static_cast<CT<T, U>>(b.w), 
		static_cast<CT<T, U>>(a.h) + static_cast<CT<T, U>>(b.h)
	} ; 
}

template <typename T, typename U> 
constexpr auto operator-(const Quad<T>& a, const Quad<U>& b) noexcept -> Quad<CT<T, U>> { 
	return {
		static_cast<CT<T, U>>(a.x) - static_cast<CT<T, U>>(b.x), 
		static_cast<CT<T, U>>(a.y) - static_cast<CT<T, U>>(b.y), 
		static_cast<CT<T, U>>(a.w) - static_cast<CT<T, U>>(b.w), 
		static_cast<CT<T, U>>(a.h) - static_cast<CT<T, U>>(b.h)
	} ; 
}

template <typename T, typename U> 
constexpr auto operator*(const Quad<T>& a, const Quad<U>& b) noexcept -> Quad<CT<T, U>> { 
	return {
		static_cast<CT<T, U>>(a.x) * static_cast<CT<T, U>>(b.x), 
		static_cast<CT<T, U>>(a.y) * static_cast<CT<T, U>>(b.y), 
		static_cast<CT<T, U>>(a.w) * static_cast<CT<T, U>>(b.w), 
		static_cast<CT<T, U>>(a.h) * static_cast<CT<T, U>>(b.h)
	} ; 
}

template <typename T, typename U> 
constexpr auto operator/(const Quad<T>& a, const Quad<U>& b) noexcept -> Quad<CT<T, U>> { 
	return {
		static_cast<CT<T, U>>(a.x) / static_cast<CT<T, U>>(b.x), 
		static_cast<CT<T, U>>(a.y) / static_cast<CT<T, U>>(b.y), 
		static_cast<CT<T, U>>(a.w) / static_cast<CT<T, U>>(b.w), 
		static_cast<CT<T, U>>(a.h) / static_cast<CT<T, U>>(b.h)
	} ; 
}

template <typename T, typename U, typename = EI<std::is_arithmetic_v<U>>> 
constexpr auto operator+(const Quad<T>& a, U v) noexcept -> Quad<CT<T, U>> { 
	return {
		static_cast<CT<T, U>>(a.x) + static_cast<CT<T, U>>(v), 
		static_cast<CT<T, U>>(a.y) + static_cast<CT<T, U>>(v), 
		static_cast<CT<T, U>>(a.w) + static_cast<CT<T, U>>(v), 
		static_cast<CT<T, U>>(a.h) + static_cast<CT<T, U>>(v)
	} ; 
}

template <typename T, typename U, typename = EI<std::is_arithmetic_v<U>>> 
constexpr auto operator-(const Quad<T>& a, U v) noexcept -> Quad<CT<T, U>> { 
	return {
		static_cast<CT<T, U>>(a.x) - static_cast<CT<T, U>>(v), 
		static_cast<CT<T, U>>(a.y) - static_cast<CT<T, U>>(v), 
		static_cast<CT<T, U>>(a.w) - static_cast<CT<T, U>>(v), 
		static_cast<CT<T, U>>(a.h) - static_cast<CT<T, U>>(v)
	} ; 
}

template <typename T, typename U, typename = EI<std::is_arithmetic_v<U>>> 
constexpr auto operator*(const Quad<T>& a, U v) noexcept -> Quad<CT<T, U>> { 
	return {
		static_cast<CT<T, U>>(a.x) * static_cast<CT<T, U>>(v), 
		static_cast<CT<T, U>>(a.y) * static_cast<CT<T, U>>(v), 
		static_cast<CT<T, U>>(a.w) * static_cast<CT<T, U>>(v), 
		static_cast<CT<T, U>>(a.h) * static_cast<CT<T, U>>(v)
	} ; 
}

template <typename T, typename U, typename = EI<std::is_arithmetic_v<U>>> 
constexpr auto operator/(const Quad<T>& a, U v) noexcept -> Quad<CT<T, U>> { 
	return {
		static_cast<CT<T, U>>(a.x) / static_cast<CT<T, U>>(v), 
		static_cast<CT<T, U>>(a.y) / static_cast<CT<T, U>>(v), 
		static_cast<CT<T, U>>(a.w) / static_cast<CT<T, U>>(v), 
		static_cast<CT<T, U>>(a.h) / static_cast<CT<T, U>>(v)
	} ; 
}

template <typename T, typename U, typename = EI<std::is_arithmetic_v<U>>> 
constexpr auto operator+(U v, const Quad<T>& a) noexcept -> Quad<CT<T, U>> { 
	return a + v ; 
}

template <typename T, typename U, typename = EI<std::is_arithmetic_v<U>>> 
constexpr auto operator-(U v, const Quad<T>& a) noexcept -> Quad<CT<T, U>> { 
	return {
		static_cast<CT<T, U>>(v) - static_cast<CT<T, U>>(a.x), 
		static_cast<CT<T, U>>(v) - static_cast<CT<T, U>>(a.y), 
		static_cast<CT<T, U>>(v) - static_cast<CT<T, U>>(a.w), 
		static_cast<CT<T, U>>(v) - static_cast<CT<T, U>>(a.h)
	} ; 
}

template <typename T, typename U, typename = EI<std::is_arithmetic_v<U>>> 
constexpr auto operator*(U v, const Quad<T>& a) noexcept -> Quad<CT<T, U>> { 
	return a * v ; 
}

template <typename T, typename U, typename = EI<std::is_arithmetic_v<U>>> 
constexpr auto operator/(U v, const Quad<T>& a) noexcept -> Quad<CT<T, U>> { 
	return {
		static_cast<CT<T, U>>(v) / static_cast<CT<T, U>>(a.x), 
		static_cast<CT<T, U>>(v) / static_cast<CT<T, U>>(a.y), 
		static_cast<CT<T, U>>(v) / static_cast<CT<T, U>>(a.w), 
		static_cast<CT<T, U>>(v) / static_cast<CT<T, U>>(a.h)
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
		return c.d ; 
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

using Size = Point<uint> ;
using Pos = Point<uint> ;
using Rect = Quad<uint> ;
using RGBA = Color ;

#undef USE_ZUNIT_HELPER