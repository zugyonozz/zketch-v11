#pragma once

#include <ostream>
#include <vector>

#ifndef NOMINMAX
#define NOMINMAX
#endif

#define WIN32_LEAN_AND_MEAN // Ini juga praktik yang baik
#include <minwindef.h>
#include <objidl.h>
#include <windef.h>

#pragma push_macro("min")
#pragma push_macro("max")
#undef min
#undef max
#include <gdiplus.h>
#pragma pop_macro("min")
#pragma pop_macro("max")

#undef near
#undef far

// forward declaration

struct PT ;
struct PTF ;
struct SZ ;
struct SZF ;
struct Quad ;
struct QuadF ;

// template spesialize for type checking

template <typename> struct is_size_unit_ {
	static constexpr bool val = false ;
} ;

template <> struct is_size_unit_<SZ> {
	static constexpr bool val = true ;
} ;

template <> struct is_size_unit_<SZF> {
	static constexpr bool val = true ;
} ;

template <typename> struct is_point_unit_ {
	static constexpr bool val = false ;
} ;

template <> struct is_point_unit_<PT> {
	static constexpr bool val = true ;
} ;

template <> struct is_point_unit_<PTF> {
	static constexpr bool val = true ;
} ;
namespace z_helper {
template <typename T> constexpr bool is_paired_data_unit = is_point_unit_<T>::val || is_size_unit_<T>::val ;
}

template <typename> struct is_bound_unit_ {
	static constexpr bool val = false ;
} ;

template <> struct is_bound_unit_<Quad> {
	static constexpr bool val = true ;
} ;

template <> struct is_bound_unit_<QuadF> {
	static constexpr bool val = true ;
} ;

// implementation zunit.h

struct PT : Gdiplus::Point {

	using Base = Point ;

	PT() noexcept ;

	PT(int v) noexcept ;
    
	PT(int x, int y) noexcept ;

	PT(const PT& o) noexcept ;

	PT(const PTF& o) noexcept ;

	PT(const SZ& o) noexcept ;

	PT(const SZF& o) noexcept ;

	explicit PT(const tagPOINT& o) noexcept ;
	
	explicit PT(const POINTL& o) noexcept ;
	
	explicit PT(const tagSIZE& o) noexcept ;
	
	explicit PT(const tagPOINTS& o) noexcept ;

	constexpr PT& operator=(int v) noexcept ;

	constexpr PT& operator=(const PT& o) noexcept ;

	constexpr PT& operator=(const PTF& o) noexcept ;

	constexpr PT& operator=(const SZ& o) noexcept ;

	constexpr PT& operator=(const SZF& o) noexcept ;
	
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

	explicit operator tagPOINT() const noexcept ;

	explicit operator _POINTL() const noexcept ;

	explicit operator tagSIZE() const noexcept ;

	explicit operator tagPOINTS() const noexcept ;

	operator SZ() const noexcept ;

	operator PTF() const noexcept ;

	operator SZF() const noexcept ;

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

std::ostream& operator<<(std::ostream& os, const PT& pt) noexcept ;

struct SZ : Gdiplus::Size {

	using Base = Size ;

	SZ() noexcept ;

	SZ(int v) noexcept ;
    
	SZ(int x, int y) noexcept ;

	SZ(const SZ& o) noexcept ;

	SZ(const SZF& o) noexcept ;

	SZ(const PT& o) noexcept ;

	SZ(const PTF& o) noexcept ;

	SZ(const tagPOINT& o) noexcept ;
	
	SZ(const POINTL& o) noexcept ;
	
	SZ(const tagSIZE& o) noexcept ;
	
	SZ(const tagPOINTS& o) noexcept ;

	constexpr SZ& operator=(int v) noexcept ;

	constexpr SZ& operator=(const SZ& o) noexcept ;

	constexpr SZ& operator=(const SZF& o) noexcept ;

	constexpr SZ& operator=(const PT& o) noexcept ;

	constexpr SZ& operator=(const PTF& o) noexcept ;
	
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

	explicit operator tagPOINT() const noexcept ;

	explicit operator _POINTL() const noexcept ;

	explicit operator tagSIZE() const noexcept ;

	explicit operator tagPOINTS() const noexcept ;

	operator PT() const noexcept ;

	operator PTF() const noexcept ;

	operator SZF() const noexcept ;

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

std::ostream& operator<<(std::ostream& os, const SZ& sz) noexcept ;

struct PTF : Gdiplus::PointF {

	using Base = PointF ;

	PTF() noexcept ;

	PTF(float v) noexcept ;
    
	PTF(float x, float y) noexcept ;

	PTF(const PTF& o) noexcept ;

	PTF(const PT& o) noexcept ;

	PTF(const SZ& o) noexcept ;

	PTF(const SZF& o) noexcept ;

	PTF(const tagPOINT& o) noexcept ;
	
	PTF(const POINTL& o) noexcept ;
	
	PTF(const tagSIZE& o) noexcept ;
	
	PTF(const tagPOINTS& o) noexcept ;

	constexpr PTF& operator=(float v) noexcept ;

	constexpr PTF& operator=(const PTF& o) noexcept ;

	constexpr PTF& operator=(const PT& o) noexcept ;

	constexpr PTF& operator=(const SZ& o) noexcept ;

	constexpr PTF& operator=(const SZF& o) noexcept ;
	
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

    bool operator==(const PTF& o) const noexcept ;

    bool operator!=(const PTF& o) const noexcept ;

	explicit operator tagPOINT() const noexcept ;

	explicit operator _POINTL() const noexcept ;

	explicit operator tagSIZE() const noexcept ;

	explicit operator tagPOINTS() const noexcept ;

	operator PT() const noexcept ;

	operator SZ() const noexcept ;

	operator SZF() const noexcept ;

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

std::ostream& operator<<(std::ostream& os, const PTF& ptf) noexcept ;

struct SZF : Gdiplus::SizeF {

	using Base = SizeF ;

	SZF() noexcept ;

	SZF(float v) noexcept ;
    
	SZF(float x, float y) noexcept ;

	SZF(const SZF& o) noexcept ;

	SZF(const SZ& o) noexcept ;

	SZF(const PT& o) noexcept ;

	SZF(const PTF& o) noexcept ;

	SZF(const tagPOINT& o) noexcept ;
	
	SZF(const POINTL& o) noexcept ;
	
	SZF(const tagSIZE& o) noexcept ;
	
	SZF(const tagPOINTS& o) noexcept ;

	constexpr SZF& operator=(int v) noexcept ;
	
	constexpr SZF& operator=(const SZF& o) noexcept ;

	constexpr SZF& operator=(const SZ& o) noexcept ;

	constexpr SZF& operator=(const PT& o) noexcept ;

	constexpr SZF& operator=(const PTF& o) noexcept ;
	
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

    bool operator==(const SZF& o) const noexcept ;

    bool operator!=(const SZF& o) const noexcept ;

	explicit operator tagPOINT() const noexcept ;

	explicit operator _POINTL() const noexcept ;

	explicit operator tagSIZE() const noexcept ;

	explicit operator tagPOINTS() const noexcept ;

	operator PT() const noexcept ;

	operator PTF() const noexcept ;

	operator SZ() const noexcept ;

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

std::ostream& operator<<(std::ostream& os, const SZ& sz) noexcept ;

struct Quad : Gdiplus::Rect {

	using Base = Rect ;

	Quad() noexcept ;

	Quad(int v) noexcept ;

	Quad(int x, int y, int w, int h) noexcept ;

	template <typename T, typename U> requires z_helper::is_paired_data_unit<T> && z_helper::is_paired_data_unit<U>
	Quad(const T& p, const U& s) noexcept : Base(p, s) {}

	Quad(const Quad& o) noexcept ;

	Quad(const QuadF& o) noexcept ;

	Quad(const tagRECT& o) noexcept ;

	Quad(const _RECTL& o) noexcept ;

	Quad& operator=(int v) noexcept ;

	Quad& operator=(const Quad& o) noexcept ;

	Quad& operator=(const QuadF& o) noexcept ;

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

    bool operator==(const Quad& o) const noexcept ;

    bool operator!=(const Quad& o) const noexcept ;

	explicit operator tagRECT() const noexcept ;

	explicit operator _RECTL() const noexcept ;

	operator QuadF() const noexcept ;

	PT getPos() const noexcept ;

	PT getPos() noexcept ;

	SZ getSize() const noexcept ;

	SZ getSize() noexcept ;

	Quad& setPos(int x, int y) noexcept ;

	Quad& setPos(const PT& pos) noexcept ;

	Quad& setPos(const PTF& pos) noexcept ;

	Quad& setSize(int w, int h) noexcept ;

	Quad& setSize(const SZ& size) noexcept ;

	Quad& setSize(const SZF& size) noexcept ;
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

std::ostream& operator<<(std::ostream& os, const Quad& q) noexcept ;

struct QuadF : Gdiplus::RectF {

	using Base = RectF ;

	QuadF() noexcept ;

	QuadF(float v) noexcept ;

	QuadF(float x, float y, float w, float h) noexcept ;

	template <typename T, typename U> requires z_helper::is_paired_data_unit<T> && z_helper::is_paired_data_unit<U>
	QuadF(const T& p, const U& s) noexcept : Base(p, s) {}

	QuadF(const QuadF& o) noexcept ;

	QuadF(const Quad& o) noexcept ;

	QuadF(const tagRECT& o) noexcept ;

	QuadF(const _RECTL& o) noexcept ;

	QuadF& operator=(float v) noexcept ;

	QuadF& operator=(const QuadF& o) noexcept ;

	QuadF& operator=(const Quad& o) noexcept ;

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

    bool operator==(const QuadF& o) const noexcept ;

    bool operator!=(const QuadF& o) const noexcept ;

	explicit operator tagRECT() const noexcept ;

	explicit operator _RECTL() const noexcept ;

	explicit operator Quad() const noexcept ;

	PTF getPos() const noexcept ;

	PTF getPos() noexcept ;

	SZF getSize() const noexcept ;

	SZF getSize() noexcept ;

	constexpr QuadF& setPos(float x, float y) noexcept ;

	constexpr QuadF& setPos(const PT& pos) noexcept ;

	constexpr QuadF& setPos(const PTF& pos) noexcept ;

	constexpr QuadF& setSize(float w, float h) noexcept ;

	constexpr QuadF& setSize(const SZ& size) noexcept ;

	constexpr QuadF& setSize(const SZF& size) noexcept ;
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

std::ostream& operator<<(std::ostream& os, const QuadF& qf) noexcept ;

using Vertex = std::vector<PT> ;
using Color = Gdiplus::Color ;