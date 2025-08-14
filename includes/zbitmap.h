#pragma once

#define USE_Z_ALIAS

#include "zunit.h"

class Bitmap {
private :
	HBITMAP hbmp = nullptr ;
	Rect bound = {} ;

public :
	Bitmap(const Bitmap&) = delete ;
	Bitmap& operator=(const Bitmap&) = delete ;

	Bitmap() noexcept  = default ;

	Bitmap(HBITMAP bmp) noexcept ;

	Bitmap(Bitmap&& o) noexcept ;

	Bitmap& operator=(Bitmap&& o) noexcept ;

	~Bitmap() noexcept ;

	operator HBITMAP() noexcept ;

	operator HBITMAP() const noexcept ;

	const Rect& getRect() const noexcept ;

	Rect& getRect() noexcept ;

	const uint& getHeight() const noexcept ;

	uint& getHeight() noexcept ;

	const uint& getWidth() const noexcept ;

	uint& getWidth() noexcept ;
} ;

inline HBITMAP LoadBMP(cstr path) noexcept ;

#include "zbitmapimpl.h"

#undef USE_Z_ALIAS