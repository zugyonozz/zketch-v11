#pragma once

#include "zunit.h"

namespace zketch {

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

		float getHeight() const noexcept ;

		float getHeight() noexcept ;

		float getWidth() const noexcept ;

		float getWidth() noexcept ;
	} ;

	HBITMAP LoadBMP(cstr path) noexcept ;

}