#pragma once

#undef __OBJC__
#define WIN32_LEAN_AND_MEAN

#include <ostream>
#include <vector>
#include "zdef.h"
#include <objidl.h>
#include <gdiplus.h>

typedef Gdiplus::Color Color ;

#define USE_ZUNIT_HELPER

// forward declaration

struct SZ ;
struct PTF ;
struct SZF ;
struct QuadF ;

// implementation zunit.h

struct PT : Gdiplus::Point {

	using Base = Gdiplus::Point ;

	PT() noexcept ;

	PT(int v) noexcept ;
    
	PT(int x, int y) noexcept ;

	PT(const PT& o) noexcept ;

	PT(const SZ& o) noexcept ;

	explicit PT(const tagPOINT& o) noexcept ;
	
	explicit PT(const POINTL& o) noexcept ;
	
	explicit PT(const tagSIZE& o) noexcept ;
	
	explicit PT(const tagPOINTS& o) noexcept ;

	template <typename T, typename U, typename = std::enable_if_t<std::is_arithmetic_v<std::remove_cv_t<std::remove_reference_t<T>>> && std::is_arithmetic_v<std::remove_cv_t<std::remove_reference_t<U>>>>> 
	constexpr PT(const std::pair<T&, U&>& pt) noexcept : Base(static_cast<int>(pt.first), static_cast<int>(pt.second)) {}
	
	constexpr PT& operator=(int v) noexcept;

	template <typename T, typename U, typename = std::enable_if_t<std::is_arithmetic_v<std::remove_cv_t<std::remove_reference_t<T>>> && std::is_arithmetic_v<std::remove_cv_t<std::remove_reference_t<U>>>>> 
	constexpr PT& operator=(const std::pair<T&, U&>& pt) noexcept {
		X = static_cast<int>(pt.first) ;
		Y = static_cast<int>(pt.second) ;
		return *this ;
	}
	
    PT operator+() const noexcept ;

    PT operator-() const noexcept ;

	constexpr PT& operator+=(const PT& o) noexcept ;

	constexpr PT& operator-=(const PT& o) noexcept ;

	constexpr PT& operator*=(const PT& o) noexcept ;

	constexpr PT& operator/=(const PT& o) noexcept ;

	constexpr PT& operator+=(int v) noexcept ;

	constexpr PT& operator-=(int v) noexcept ;

	constexpr PT& operator*=(int v) noexcept ;

	constexpr PT& operator/=(int v) noexcept ;

    bool operator==(const PT& o) const noexcept ;

    bool operator!=(const PT& o) const noexcept ;

	operator tagPOINT() const noexcept ;

	operator _POINTL() const noexcept ;

	operator tagSIZE() const noexcept ;

	operator tagPOINTS() const noexcept ;

	explicit operator SZ() const noexcept ;

	explicit operator PTF() const noexcept ;

	explicit operator SZF() const noexcept ;

} ;

PT operator+(const PT& a, const PT& b) noexcept ;

PT operator-(const PT& a, const PT& b) noexcept ;

PT operator*(const PT& a, const PT& b) noexcept ;

PT operator/(const PT& a, const PT& b) noexcept ;

PT operator+(const PT& a, int v) noexcept ;

PT operator-(const PT& a, int v) noexcept ;

PT operator*(const PT& a, int v) noexcept ;

PT operator/(const PT& a, int v) noexcept ;

PT operator+(int v, const PT& a) noexcept ;

PT operator*(int v, const PT& a) noexcept ;

PT operator-(int v, const PT& a) noexcept ;

PT operator/(int v, const PT& a) noexcept ;

#ifdef ZUNIT_DEBUG

std::ostream& operator<<(std::ostream& os, const PT& pt) const noexcept ;

#endif

struct SZ : Gdiplus::Size {

	using Base = Gdiplus::Size ;

	SZ() noexcept ;

	SZ(int v) noexcept ;
    
	SZ(int x, int y) noexcept ;

	SZ(const tagPOINT& o) noexcept ;
	
	SZ(const POINTL& o) noexcept ;
	
	SZ(const tagSIZE& o) noexcept ;
	
	SZ(const tagPOINTS& o) noexcept ;

	template <typename T, typename U, typename = std::enable_if_t<std::is_arithmetic_v<std::remove_cv_t<std::remove_reference_t<T>>> && std::is_arithmetic_v<std::remove_cv_t<std::remove_reference_t<U>>>>> 
	constexpr SZ(const std::pair<T&, U&>& sz) noexcept : Base(static_cast<int>(sz.first), static_cast<int>(sz.second)) {}
	
	constexpr SZ& operator=(int v) noexcept ;

	template <typename T, typename U, typename = std::enable_if_t<std::is_arithmetic_v<std::remove_cv_t<std::remove_reference_t<T>>> && std::is_arithmetic_v<std::remove_cv_t<std::remove_reference_t<U>>>>> 
	constexpr SZ& operator=(const std::pair<T&, U&>& pt) noexcept {
		Width = static_cast<int>(pt.first) ;
		Height = static_cast<int>(pt.second) ;
		return *this ;
	}
	
    SZ operator+() const noexcept ;

    SZ operator-() const noexcept ;

	constexpr SZ& operator+=(const SZ& o) noexcept ;

	constexpr SZ& operator-=(const SZ& o) noexcept ;

	constexpr SZ& operator*=(const SZ& o) noexcept ;

	constexpr SZ& operator/=(const SZ& o) noexcept ;

	constexpr SZ& operator+=(int v) noexcept ;

	constexpr SZ& operator-=(int v) noexcept ;

	constexpr SZ& operator*=(int v) noexcept ;

	constexpr SZ& operator/=(int v) noexcept ;

    bool operator==(const SZ& o) const noexcept ;

    bool operator!=(const SZ& o) const noexcept ;

	operator tagPOINT() const noexcept ;

	operator _POINTL() const noexcept ;

	operator tagSIZE() const noexcept ;

	operator tagPOINTS() const noexcept ;

	explicit operator PT() const noexcept ;

	explicit operator PTF() const noexcept ;

	explicit operator SZF() const noexcept ;

} ;

SZ operator+(const SZ& a, const SZ& b) noexcept ;

SZ operator-(const SZ& a, const SZ& b) noexcept ;

SZ operator*(const SZ& a, const SZ& b) noexcept ;

SZ operator/(const SZ& a, const SZ& b) noexcept ;

SZ operator+(const SZ& a, int v) noexcept ;

SZ operator-(const SZ& a, int v) noexcept ;

SZ operator*(const SZ& a, int v) noexcept ;

SZ operator/(const SZ& a, int v) noexcept ;

SZ operator+(int v, const SZ& a) noexcept ;

SZ operator*(int v, const SZ& a) noexcept ;

SZ operator-(int v, const SZ& a) noexcept ;

SZ operator/(int v, const SZ& a) noexcept ;

#ifdef ZUNIT_DEBUG

std::ostream& operator<<(std::ostream& os, const SZ& sz) const noexcept ;

#endif

struct PTF : Gdiplus::PointF {

	using Base = Gdiplus::PointF ;

	PTF() noexcept ;

	PTF(float v) noexcept ;
    
	PTF(float x, float y) noexcept ;

	PTF(const tagPOINT& o) noexcept ;
	
	PTF(const POINTL& o) noexcept ;
	
	PTF(const tagSIZE& o) noexcept ;
	
	PTF(const tagPOINTS& o) noexcept ;

	template <typename T, typename U, typename = std::enable_if_t<std::is_arithmetic_v<std::remove_cv_t<std::remove_reference_t<T>>> && std::is_arithmetic_v<std::remove_cv_t<std::remove_reference_t<U>>>>> 
	constexpr PTF(const std::pair<T&, U&>& pt) noexcept : Base(static_cast<float>(pt.first), static_cast<float>(pt.second)) {}
	
	constexpr PTF& operator=(float v) noexcept ;

	template <typename T, typename U, typename = std::enable_if_t<std::is_arithmetic_v<std::remove_cv_t<std::remove_reference_t<T>>> && std::is_arithmetic_v<std::remove_cv_t<std::remove_reference_t<U>>>>> 
	constexpr PTF& operator=(const std::pair<T&, U&>& pt) noexcept {
		X = static_cast<float>(pt.first) ;
		Y = static_cast<float>(pt.second) ;
		return *this ;
	}
	
    PTF operator+() const noexcept ;

    PTF operator-() const noexcept ;

	constexpr PTF& operator+=(const PTF& o) noexcept ;

	constexpr PTF& operator-=(const PTF& o) noexcept ;

	constexpr PTF& operator*=(const PTF& o) noexcept ;

	constexpr PTF& operator/=(const PTF& o) noexcept ;

	constexpr PTF& operator+=(float v) noexcept ;

	constexpr PTF& operator-=(float v) noexcept ;

	constexpr PTF& operator*=(float v) noexcept ;

	constexpr PTF& operator/=(float v) noexcept ;

    constexpr bool operator==(const PTF& o) const noexcept ;

    constexpr bool operator!=(const PTF& o) const noexcept ;

	operator tagPOINT() const noexcept ;

	operator _POINTL() const noexcept ;

	operator tagSIZE() const noexcept ;

	operator tagPOINTS() const noexcept ;

	explicit operator PT() const noexcept ;

	explicit operator SZ() const noexcept ;

	explicit operator SZF() const noexcept ;

} ;

PTF operator+(const PTF& a, const PTF& b) noexcept ;

PTF operator-(const PTF& a, const PTF& b) noexcept ;

PTF operator*(const PTF& a, const PTF& b) noexcept ;

PTF operator/(const PTF& a, const PTF& b) noexcept ;

PTF operator+(const PTF& a, float v) noexcept ;

PTF operator-(const PTF& a, float v) noexcept ;

PTF operator*(const PTF& a, float v) noexcept ;

PTF operator/(const PTF& a, float v) noexcept ;

PTF operator+(float v, const PTF& a) noexcept ;

PTF operator*(float v, const PTF& a) noexcept ;

PTF operator-(float v, const PTF& a) noexcept ;

PTF operator/(float v, const PTF& a) noexcept ;

#ifdef ZUNIT_DEBUG

std::ostream& operator<<(std::ostream& os, const PTF& ptf) const noexcept ;

#endif

struct SZF : Gdiplus::SizeF {

	using Base = Gdiplus::SizeF ;

	SZF() noexcept ;

	SZF(float v) noexcept ;
    
	SZF(float x, float y) noexcept ;

	SZF(const tagPOINT& o) noexcept ;
	
	SZF(const POINTL& o) noexcept ;
	
	SZF(const tagSIZE& o) noexcept ;
	
	SZF(const tagPOINTS& o) noexcept ;

	template <typename T, typename U, typename = std::enable_if_t<std::is_arithmetic_v<std::remove_cv_t<std::remove_reference_t<T>>> && std::is_arithmetic_v<std::remove_cv_t<std::remove_reference_t<U>>>>> 
	constexpr SZF(const std::pair<T&, U&>& sz) noexcept : Base(static_cast<float>(sz.first), static_cast<float>(sz.second)) {}
	
	constexpr SZF& operator=(int v) noexcept ;

	template <typename T, typename U, typename = std::enable_if_t<std::is_arithmetic_v<std::remove_cv_t<std::remove_reference_t<T>>> && std::is_arithmetic_v<std::remove_cv_t<std::remove_reference_t<U>>>>> 
	constexpr SZF& operator=(const std::pair<T&, U&>& pt) noexcept {
		Width = static_cast<float>(pt.first) ;
		Height = static_cast<float>(pt.second) ;
		return *this ;
	}
	
    SZF operator+() const noexcept ;

    SZF operator-() const noexcept ;

	constexpr SZF& operator+=(const SZF& o) noexcept ;

	constexpr SZF& operator-=(const SZF& o) noexcept ;

	constexpr SZF& operator*=(const SZF& o) noexcept ;

	constexpr SZF& operator/=(const SZF& o) noexcept ;

	constexpr SZF& operator+=(int v) noexcept ;

	constexpr SZF& operator-=(int v) noexcept ;

	constexpr SZF& operator*=(int v) noexcept ;

	constexpr SZF& operator/=(int v) noexcept ;

    constexpr bool operator==(const SZF& o) const noexcept ;

    constexpr bool operator!=(const SZF& o) const noexcept ;

	operator tagPOINT() const noexcept ;

	operator _POINTL() const noexcept ;

	operator tagSIZE() const noexcept ;

	operator tagPOINTS() const noexcept ;

	explicit operator PT() const noexcept ;

	explicit operator PTF() const noexcept ;

	explicit operator SZ() const noexcept ;

} ;

SZF operator+(const SZF& a, const SZF& b) noexcept ;

SZF operator-(const SZF& a, const SZF& b) noexcept ;

SZF operator*(const SZF& a, const SZF& b) noexcept ;

SZF operator/(const SZF& a, const SZF& b) noexcept ;

SZF operator+(const SZF& a, float v) noexcept ;

SZF operator-(const SZF& a, float v) noexcept ;

SZF operator*(const SZF& a, float v) noexcept ;

SZF operator/(const SZF& a, float v) noexcept ;

SZF operator+(float v, const SZF& a) noexcept ;

SZF operator*(float v, const SZF& a) noexcept ;

SZF operator-(float v, const SZF& a) noexcept ;

SZF operator/(float v, const SZF& a) noexcept ;

#ifdef ZUNIT_DEBUG

std::ostream& operator<<(std::ostream& os, const SZ& sz) const noexcept ;

#endif

struct Quad : Gdiplus::Rect {

	using Base = Gdiplus::Rect ;

	Quad() noexcept ;

	Quad(int v) noexcept ;

	Quad(int x, int y, int w, int h) noexcept ;

	Quad(const PT& pos, const SZ& size) noexcept ;

	Quad(const Quad& o) noexcept ;

	Quad(const tagRECT& o) noexcept ;

	Quad(const _RECTL& o) noexcept ;

	Quad& operator=(int v) noexcept ;

	Quad& operator=(const Quad& o) noexcept ;

    Quad operator+() const noexcept ;

    Quad operator-() const noexcept ;

	constexpr Quad& operator+=(const Quad& o) noexcept ;

	constexpr Quad& operator-=(const Quad& o) noexcept ;

	constexpr Quad& operator*=(const Quad& o) noexcept ;

	constexpr Quad& operator/=(const Quad& o) noexcept ;

	constexpr Quad& operator+=(int v) noexcept ;

	constexpr Quad& operator-=(int v) noexcept ;

	constexpr Quad& operator*=(int v) noexcept ;

	constexpr Quad& operator/=(int v) noexcept ;

    constexpr bool operator==(const Quad& o) const noexcept ;

    constexpr bool operator!=(const Quad& o) const noexcept ;

	explicit operator tagRECT() const noexcept ;

	explicit operator _RECTL() const noexcept ;

	explicit operator QuadF() const noexcept ;

	std::pair<const int&, const int&> getPos() const noexcept ;

	std::pair<int&, int&> getPos() noexcept ;

	std::pair<const int&, const int&> getSize() const noexcept ;

	std::pair<int&, int&> getSize() noexcept ;

	Quad& setPos(int x, int y) noexcept ;

	Quad& setPos(const PT& pos) noexcept ;

	Quad& setSize(int w, int h) noexcept ;

	Quad& setSize(const SZ& size) noexcept ;
} ;

Quad operator+(const Quad& a, const Quad& b) noexcept ;

Quad operator-(const Quad& a, const Quad& b) noexcept ;

Quad operator*(const Quad& a, const Quad& b) noexcept ;

Quad operator/(const Quad& a, const Quad& b) noexcept ;

Quad operator+(const Quad& a, int v) noexcept ;

Quad operator-(const Quad& a, int v) noexcept ;

Quad operator*(const Quad& a, int v) noexcept ;

Quad operator/(const Quad& a, int v) noexcept ;

Quad operator-(int v, const Quad& a) noexcept ;

Quad operator/(int v, const Quad& a) noexcept ;

Quad operator+(int v, const Quad& a) noexcept ;

Quad operator*(int v, const Quad& a) noexcept ;

#ifdef ZUNIT_DEBUG

std::ostream& operator<<(std::ostream& os, const Quad& q) const noexcept ;

#endif

struct QuadF : Gdiplus::RectF {

	using Base = Gdiplus::RectF ;

	QuadF() noexcept ;

	QuadF(float v) noexcept ;

	QuadF(float x, float y, float w, float h) noexcept ;

	QuadF(const PTF& pos, const SZF& size) noexcept ;

	QuadF(const QuadF& o) noexcept ;

	QuadF(const tagRECT& o) noexcept ;

	QuadF(const _RECTL& o) noexcept ;

	QuadF& operator=(float v) noexcept ;

	QuadF& operator=(const QuadF& o) noexcept ;

    QuadF operator+() const noexcept ;

    QuadF operator-() const noexcept ;

	constexpr QuadF& operator+=(const QuadF& o) noexcept ;

	constexpr QuadF& operator-=(const QuadF& o) noexcept ;

	constexpr QuadF& operator*=(const QuadF& o) noexcept ;

	constexpr QuadF& operator/=(const QuadF& o) noexcept ;

	constexpr QuadF& operator+=(float v) noexcept ;

	constexpr QuadF& operator-=(float v) noexcept ;

	constexpr QuadF& operator*=(float v) noexcept ;

	constexpr QuadF& operator/=(float v) noexcept ;

    constexpr bool operator==(const QuadF& o) const noexcept ;

    constexpr bool operator!=(const QuadF& o) const noexcept ;

	explicit operator tagRECT() const noexcept ;

	explicit operator _RECTL() const noexcept ;

	explicit operator Quad() const noexcept ;

	std::pair<const float&, const float&> getPos() const noexcept ;

	constexpr std::pair<float&, float&> getPos() noexcept ;

	constexpr std::pair<const float&, const float&> getSize() const noexcept ;

	constexpr std::pair<float&, float&> getSize() noexcept ;

	constexpr QuadF& setPos(float x, float y) noexcept ;

	constexpr QuadF& setPos(const PT& pos) noexcept ;

	constexpr QuadF& setSize(float w, float h) noexcept ;

	constexpr QuadF& setSize(const SZ& size) noexcept ;
} ;

QuadF operator+(const QuadF& a, const QuadF& b) noexcept ;

QuadF operator-(const QuadF& a, const QuadF& b) noexcept ;

QuadF operator*(const QuadF& a, const QuadF& b) noexcept ;

QuadF operator/(const QuadF& a, const QuadF& b) noexcept ;

QuadF operator+(const QuadF& a, float v) noexcept ;

QuadF operator-(const QuadF& a, float v) noexcept ;

QuadF operator*(const QuadF& a, float v) noexcept ;

QuadF operator/(const QuadF& a, float v) noexcept ;

QuadF operator-(float v, const QuadF& a) noexcept ;

QuadF operator/(float v, const QuadF& a) noexcept ;

QuadF operator+(float v, const QuadF& a) noexcept ;

QuadF operator*(float v, const QuadF& a) noexcept ;

#ifdef ZUNIT_DEBUG

std::ostream& operator<<(std::ostream& os, const QuadF& qf) const noexcept ;

#endif

using Vertex = std::vector<PT> ;

#undef USE_ZUNIT_HELPER