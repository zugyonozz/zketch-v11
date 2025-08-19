#include "zbitmap.h"

namespace zketch {

	Bitmap::Bitmap(HBITMAP bmp) noexcept : hbmp(bmp) {
		BITMAP bm ;
		if (GetObject(bmp, sizeof(bm), &bm))
			bound = Quad{0L, 0L, bm.bmWidth, bm.bmHeight} ;
	}

	Bitmap::Bitmap(Bitmap&& o) noexcept : hbmp(o.hbmp), bound(o.bound) {
		o.hbmp = nullptr ;
		o.bound = {} ;
	}

	Bitmap& Bitmap::operator=(Bitmap&& o) noexcept {
		if (this != &o) {
			if (hbmp)
				DeleteObject(hbmp) ;
			hbmp = o.hbmp ;
			bound = o.bound ;
			o.hbmp = nullptr ;
			o.bound = {} ;
		}
		return *this ;
	}

	Bitmap::~Bitmap() noexcept {
		if (hbmp) DeleteObject(hbmp) ;
	}

	Bitmap::operator HBITMAP() noexcept {
		return hbmp ;
	}

	Bitmap::operator HBITMAP() const noexcept {
		return hbmp ;
	}

	const Quad& Bitmap::getRect() const noexcept {
		return bound ;
	}

	Quad& Bitmap::getRect() noexcept {
		return bound ;
	}

	float Bitmap::getWidth() const noexcept {
		return bound.w ;
	}

	float Bitmap::getWidth() noexcept {
		return bound.w ;
	}

	float Bitmap::getHeight() const noexcept {
		return bound.h ;
	}

	float Bitmap::getHeight() noexcept {
		return bound.h ;
	}

	HBITMAP LoadBMP(cstr path) noexcept {
		return static_cast<HBITMAP>(LoadImage(nullptr, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION)) ;
	}

}