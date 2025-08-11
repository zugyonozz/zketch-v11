#pragma once

#include <algorithm>
#include <type_traits>
#include "zdef.h"

template <bool cond, typename T = void> 
using EI = std::enable_if_t<cond, T> ;
template <typename ... Ts> using CT = std::common_type_t<Ts...> ;

template <typename T, typename = EI<std::is_unsigned_v<T>>> 
constexpr T uclamp(T val, T lim) noexcept { 
	return val > lim ? lim : val ; 
}

template <typename T, typename = EI<std::is_arithmetic_v<T>>> 
struct Point {
    T x, y;

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

template <typename T, typename = EI<std::is_unsigned_v<T>>> 
constexpr T rangeCtrl(T val) noexcept { 
	return val > 255 ? 255 : val ; 
}

template <typename T, typename = EI<std::is_unsigned_v<T>>> 
struct Color {
	T r, g, b, a ;

	constexpr Color() noexcept : r(0), g(0), b(0), a(0) {}

	template <typename U, typename = EI<std::is_integral_v<U>>> 
	constexpr Color(U v) noexcept { 
		*this = translateRGBA<T>(static_cast<uint>(v)) ; 
	}

	template <typename U, typename = EI<std::is_unsigned_v<U>>> 
	constexpr Color(U r, U g, U b, U a = 0) noexcept : 	r(rangeCtrl(static_cast<T>(r))), 
														g(rangeCtrl(static_cast<T>(g))), 
														b(rangeCtrl(static_cast<T>(b))), 
														a(rangeCtrl(static_cast<T>(a))) {}

	template <typename U> constexpr Color(const Color<U>& o) noexcept : r(o.r), g(o.g), b(o.b), a(o.a) {}

    constexpr Color& operator=(COLORREF v) noexcept { 
		Color c = translateRGBA<uchar>(v) ; 
		r = c.r ; 
		g = c.g ; 
		b = c.b ; 
		a = c.a ; 
		return *this ; 
	}

	template <typename U> 
	constexpr Color& operator=(const Color<U>& o) noexcept { 
		r = o.r ; 
		g = o.g ; 
		b = o.b ; 
		a = o.a ; 
		return *this ; 
	}

	template <typename U> 
	constexpr Color& operator+=(const Color<U>& o) noexcept { 
		r = rangeCtrl(r + static_cast<T>(o.r)) ; 
		g = rangeCtrl(g + static_cast<T>(o.g)) ; 
		b = rangeCtrl(b + static_cast<T>(o.b)) ; 
		a = rangeCtrl(a + static_cast<T>(o.a)) ; 
		return *this ; 
	}

    template <typename U> 
	constexpr Color& operator-=(const Color<U>& o) noexcept { 
		r = (r > o.r) ? r - static_cast<T>(o.r) : 0 ; 
		g = (g > o.g) ? g - static_cast<T>(o.g) : 0 ; 
		b = (b > o.b) ? b - static_cast<T>(o.b) : 0 ; 
		a = (a > o.a) ? a - static_cast<T>(o.a) : 0 ; 
		return *this ; 
	}

    template <typename U> 
	constexpr Color& operator*=(const Color<U>& o) noexcept { 
		r = rangeCtrl(r * static_cast<T>(o.r)) ; 
		g = rangeCtrl(g * static_cast<T>(o.g)) ; 
		b = rangeCtrl(b * static_cast<T>(o.b)) ; 
		a = rangeCtrl(a * static_cast<T>(o.a)) ; 
		return *this ; 
	}

    template <typename U> 
	constexpr Color& operator/=(const Color<U>& o) noexcept { 
		if (o.r != 0) 
			r /= static_cast<T>(o.r) ; 
		if (o.g != 0) 
			g /= static_cast<T>(o.g) ; 
		if (o.b != 0) 
			b /= static_cast<T>(o.b) ; 
		if (o.a != 0) 
			a /= static_cast<T>(o.a) ; 
		return *this ; 
	}

	template <typename U, typename = EI<std::is_arithmetic_v<U>>> 
	static constexpr uint makeColor(U r = 0, U g = 0, U b = 0, U a = 0) noexcept { 
		auto cr = static_cast<uint>(std::clamp(r, 0, 255)) ; 
		auto cg = static_cast<uint>(std::clamp(g, 0, 255)) ; 
		auto cb = static_cast<uint>(std::clamp(b, 0, 255)) ; 
		auto ca = static_cast<uint>(std::clamp(a, 0, 255)) ; 
		return ca << 24 | cb << 16 | cg << 8 | cr ; 
	}

	template <typename U, typename = EI<std::is_unsigned_v<U>>> 
	static constexpr Color<U> translateRGBA(uint src) noexcept { 
		return Color<U>{ 
			static_cast<U>(src & 0xFF), 
			static_cast<U>((src >> 8) & 0xFF), 
			static_cast<U>((src >> 16) & 0xFF), 
			static_cast<U>((src >> 24) & 0xFF) 
		} ; 
	}

	constexpr explicit operator COLORREF() const noexcept { 
		return makeColor(r, g, b) ; 
	} 

	constexpr T& alpha() noexcept { 
		return a ; 
	} 

	constexpr const T& alpha() const noexcept { 
		return a ; 
	} 

} ;

template <typename T, typename U> 
constexpr auto operator+(const Color<T>& a, const Color<U>& b) noexcept -> Color<CT<T, U>> { 
	return Color<CT<T, U>>{ 
		uclamp(static_cast<CT<T, U>>(a.r) + static_cast<CT<T, U>>(b.r), static_cast<CT<T, U>>(255)), 
		uclamp(static_cast<CT<T, U>>(a.g) + static_cast<CT<T, U>>(b.g), static_cast<CT<T, U>>(255)), 
		uclamp(static_cast<CT<T, U>>(a.b) + static_cast<CT<T, U>>(b.b), static_cast<CT<T, U>>(255)), 
		uclamp(static_cast<CT<T, U>>(a.a) + static_cast<CT<T, U>>(b.a), static_cast<CT<T, U>>(255)) 
	} ; 
}
template <typename T, typename U> 
constexpr auto operator-(const Color<T>& a, const Color<U>& b) noexcept -> Color<CT<T, U>> { 
	return Color<CT<T, U>>{ 
		(a.r > b.r) ? static_cast<CT<T, U>>(a.r - b.r) : static_cast<CT<T, U>>(0), 
		(a.g > b.g) ? static_cast<CT<T, U>>(a.g - b.g) : static_cast<CT<T, U>>(0), 
		(a.b > b.b) ? static_cast<CT<T, U>>(a.b - b.b) : static_cast<CT<T, U>>(0), 
		(a.a > b.a) ? static_cast<CT<T, U>>(a.a - b.a) : static_cast<CT<T, U>>(0) 
	} ; 
}
template <typename T, typename U> 
constexpr auto operator*(const Color<T>& a, const Color<U>& b) noexcept -> Color<CT<T, U>> { 
	return Color<CT<T, U>>{ 
		uclamp(static_cast<CT<T, U>>(a.r) * static_cast<CT<T, U>>(b.r), static_cast<CT<T, U>>(255)), 
		uclamp(static_cast<CT<T, U>>(a.g) * static_cast<CT<T, U>>(b.g), static_cast<CT<T, U>>(255)), 
		uclamp(static_cast<CT<T, U>>(a.b) * static_cast<CT<T, U>>(b.b), static_cast<CT<T, U>>(255)), 
		uclamp(static_cast<CT<T, U>>(a.a) * static_cast<CT<T, U>>(b.a), static_cast<CT<T, U>>(255)) 
	} ; 
}
template <typename T, typename U> 
constexpr auto operator/(const Color<T>& a, const Color<U>& b) noexcept -> Color<CT<T, U>> { 
	return Color<CT<T, U>>{ 
		(b.r != 0) ? static_cast<CT<T, U>>(a.r / b.r) : static_cast<CT<T, U>>(0), 
		(b.g != 0) ? static_cast<CT<T, U>>(a.g / b.g) : static_cast<CT<T, U>>(0), 
		(b.b != 0) ? static_cast<CT<T, U>>(a.b / b.b) : static_cast<CT<T, U>>(0), 
		(b.a != 0) ? static_cast<CT<T, U>>(a.a / b.a) : static_cast<CT<T, U>>(0) 
	} ; 
}
template <typename T, typename U, typename = EI<std::is_arithmetic_v<U>>> 
constexpr auto operator+(const Color<T>& a, U v) noexcept -> Color<CT<T, U>> { 
	auto val = static_cast<CT<T, U>>(v) ; 
	return Color<CT<T, U>>{ 
		uclamp(static_cast<CT<T, U>>(a.r) + val, static_cast<CT<T, U>>(255)), 
		uclamp(static_cast<CT<T, U>>(a.g) + val, static_cast<CT<T, U>>(255)), 
		uclamp(static_cast<CT<T, U>>(a.b) + val, static_cast<CT<T, U>>(255)), 
		uclamp(static_cast<CT<T, U>>(a.a) + val, static_cast<CT<T, U>>(255)) 
	} ; 
}

template <typename T, typename U, typename = EI<std::is_arithmetic_v<U>>> 
constexpr auto operator-(const Color<T>& a, U v) noexcept -> Color<CT<T, U>> { 
	auto val = static_cast<CT<T, U>>(v) ; 
	return Color<CT<T, U>>{ 
		(a.r > val) ? static_cast<CT<T, U>>(a.r - val) : static_cast<CT<T, U>>(0), 
		(a.g > val) ? static_cast<CT<T, U>>(a.g - val) : static_cast<CT<T, U>>(0), 
		(a.b > val) ? static_cast<CT<T, U>>(a.b - val) : static_cast<CT<T, U>>(0), 
		(a.a > val) ? static_cast<CT<T, U>>(a.a - val) : static_cast<CT<T, U>>(0) 
	} ; 
}

template <typename T, typename U, typename = EI<std::is_arithmetic_v<U>>> 
constexpr auto operator*(const Color<T>& a, U v) noexcept -> Color<CT<T, U>> { 
	auto val = static_cast<CT<T, U>>(v) ; 
	return Color<CT<T, U>>{ 
		uclamp(static_cast<CT<T, U>>(a.r) * val, static_cast<CT<T, U>>(255)), 
		uclamp(static_cast<CT<T, U>>(a.g) * val, static_cast<CT<T, U>>(255)), 
		uclamp(static_cast<CT<T, U>>(a.b) * val, static_cast<CT<T, U>>(255)), 
		uclamp(static_cast<CT<T, U>>(a.a) * val, static_cast<CT<T, U>>(255)) 
	} ; 
}

template <typename T, typename U, typename = EI<std::is_arithmetic_v<U>>> 
constexpr auto operator/(const Color<T>& a, U v) noexcept -> Color<CT<T, U>> { 
	auto val = static_cast<CT<T, U>>(v) ; 
	return Color<CT<T, U>>{ 
		(val != 0) ? static_cast<CT<T, U>>(a.r / val) : static_cast<CT<T, U>>(0), 
		(val != 0) ? static_cast<CT<T, U>>(a.g / val) : static_cast<CT<T, U>>(0), 
		(val != 0) ? static_cast<CT<T, U>>(a.b / val) : static_cast<CT<T, U>>(0), 
		(val != 0) ? static_cast<CT<T, U>>(a.a / val) : static_cast<CT<T, U>>(0) 
	} ; 
}

template <typename T, typename U, typename = EI<std::is_arithmetic_v<U>>> 
constexpr auto operator+(U v, const Color<T>& a) noexcept -> Color<CT<T, U>> { 
	return a + v; 
}

template <typename T, typename U, typename = EI<std::is_arithmetic_v<U>>> 
constexpr auto operator-(U v, const Color<T>& a) noexcept -> Color<CT<T, U>> { 
	auto val = static_cast<CT<T, U>>(v) ; 
	return Color<CT<T, U>>{ 
		(val > a.r) ? static_cast<CT<T, U>>(val - a.r) : static_cast<CT<T, U>>(0), 
		(val > a.g) ? static_cast<CT<T, U>>(val - a.g) : static_cast<CT<T, U>>(0), 
		(val > a.b) ? static_cast<CT<T, U>>(val - a.b) : static_cast<CT<T, U>>(0), 
		(val > a.a) ? static_cast<CT<T, U>>(val - a.a) : static_cast<CT<T, U>>(0) 
	} ; 
}

template <typename T, typename U, typename = EI<std::is_arithmetic_v<U>>> 
constexpr auto operator*(U v, const Color<T>& a) noexcept -> Color<CT<T, U>> { 
	return a * v; 
}

template <typename T, typename U, typename = EI<std::is_arithmetic_v<U>>> 
constexpr auto operator/(U v, const Color<T>& a) noexcept -> Color<CT<T, U>> { 
	auto val = static_cast<CT<T, U>>(v) ; 
	return Color<CT<T, U>>{ 
		(a.r != 0) ? static_cast<CT<T, U>>(val / a.r) : static_cast<CT<T, U>>(0), 
		(a.g != 0) ? static_cast<CT<T, U>>(val / a.g) : static_cast<CT<T, U>>(0), 
		(a.b != 0) ? static_cast<CT<T, U>>(val / a.b) : static_cast<CT<T, U>>(0), 
		(a.a != 0) ? static_cast<CT<T, U>>(val / a.a) : static_cast<CT<T, U>>(0) 
	} ; 
}


using Size = Point<uint> ;
using Pos = Point<uint> ;
using Rect = Quad<uint> ;
using RGBA = Color<uchar> ;