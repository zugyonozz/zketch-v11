#pragma once

#define USE_Z_ALIAS

#include "zunit.h"

class Bitmap {
private :
	HBITMAP hbmp = nullptr ;
	Quad bound = {} ;

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

	const Quad& getRect() const noexcept ;

	Quad& getRect() noexcept ;

	int getHeight() const noexcept ;

	int getHeight() noexcept ;

	int getWidth() const noexcept ;

	int getWidth() noexcept ;
} ;

HBITMAP LoadBMP(cstr path) noexcept ;

#undef USE_Z_ALIAS