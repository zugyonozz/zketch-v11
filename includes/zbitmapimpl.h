#pragma once

Bitmap::Bitmap(HBITMAP bmp) noexcept : hbmp(bmp) {
	BITMAP bm ;
	if (GetObject(bmp, sizeof(bm), &bm))
		bound = {0LL, 0LL, static_cast<uint>(bm.bmWidth), static_cast<uint>(bm.bmHeight)} ;
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

const Rect& Bitmap::getRect() const noexcept {
	return bound ;
}

Rect& Bitmap::getRect() noexcept {
	return bound ;
}

const uint& Bitmap::getHeight() const noexcept {
	return bound.h ;
}

uint& Bitmap::getHeight() noexcept {
	return bound.h ;
}

const uint& Bitmap::getWidth() const noexcept {
	return bound.w ;
}

uint& Bitmap::getWidth() noexcept {
	return bound.w ;
}

inline HBITMAP LoadBMP(cstr path) noexcept {
	return static_cast<HBITMAP>(LoadImage(nullptr, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION)) ;
}
