#pragma once

#define USE_Z_ALIAS

#include "zunit.h"

constexpr void drawRect(HDC& hdc, const Rect& rect, const Color& fill, const Color& outline, uint thickness = 1) noexcept {
	HBRUSH b0 = CreateSolidBrush(static_cast<COLORREF>(fill)) ;
	HBRUSH b1 = static_cast<HBRUSH>(SelectObject(hdc, b0)) ;

	HPEN p0 = CreatePen(PS_SOLID, thickness, static_cast<COLORREF>(outline)) ;
	HPEN p1 = static_cast<HPEN>(SelectObject(hdc, p0)) ;

	RECT r = static_cast<RECT>(rect) ;
	Rectangle(hdc, r.left, r.top, r.right, r.bottom) ;

	SelectObject(hdc, b1) ;
	DeleteObject(b0) ;

	SelectObject(hdc, p1) ;
	DeleteObject(p0) ;
}