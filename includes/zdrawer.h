#pragma once

#include "zfont.h"

#ifndef USE_ZKETCH_ALIAS
	#define USE_ZKETCH_ALIAS
#endif

namespace zketch {

	// Basic rectangle drawing
	void drawRect(HDC hdc, const Quad& rect, const Color& fill, const Color& outline, ullong thickness = 1) noexcept ;

	// Ellipse drawing
	void drawEllipse(HDC hdc, const Quad& rect, const Color& fill, const Color& outline, ullong thickness = 1) noexcept ;

	// Rounded rectangle drawing
	void drawRect(HDC hdc, const Quad& rect, const Color& fill, const Color& outline, float radius, ullong thickness = 1) noexcept ;

	// Polygon drawing
	void drawPixels(HDC hdc, const Vertex& verts, const Color& fill, const Color& outline, ullong thickness = 1) noexcept ;

	// Arc drawing (sector/pie slice with fill)
	void drawArc(HDC hdc, const Quad& rect, float startAngle, float sweepAngle, const Color& fill, const Color& outline, ullong thickness = 1) noexcept ;

	// Pie drawing
	void drawPie(HDC hdc, const Quad& rect, float start, float end, const Color& fill, const Color& outline, ullong thickness = 1) noexcept ;

	// drawText function
	void drawText(HDC hdc, const cwstr& text, const Point& pos, const Color& color, const Font& font) noexcept ;

}

#ifdef USE_ZKETCH_ALIAS
	#undef USE_ZKETCH_ALIAS
#endif