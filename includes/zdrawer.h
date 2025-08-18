#pragma once

#include "zfont.h"

#ifndef USE_Z_ALIAS
#define USE_Z_ALIAS
#endif

#ifdef USE_Z_ALIAS 

using uint = unsigned int ;

#endif

// Basic rectangle drawing
void drawRect(HDC hdc, const Quad& rect, const Color& fill, const Color& outline, uint thickness = 1) noexcept;

// Ellipse drawing
void drawEllipse(HDC hdc, const Quad& rect, const Color& fill, const Color& outline, uint thickness = 1) noexcept;

// Rounded rectangle drawing
void drawRect(HDC hdc, const Quad& rect, const Color& fill, const Color& outline, float radius, uint thickness = 1) noexcept;

// Polygon drawing
void drawPixels(HDC hdc, const Vertex& verts, const Color& fill, const Color& outline, uint thickness = 1) noexcept;

// Arc drawing (sector/pie slice with fill)
void drawArc(HDC hdc, const Quad& rect, float startAngle, float sweepAngle, const Color& fill, const Color& outline, uint thickness = 1) noexcept;

// Pie drawing
void drawPie(HDC hdc, const Quad& rect, float start, float end, const Color& fill, const Color& outline, uint thickness = 1) noexcept;

// drawText function
void drawText(HDC hdc, const std::wstring& text, const Point& pos, const Color& color, const Font& fontSpec) noexcept ;

#ifdef USE_Z_ALIAS
#undef USE_Z_ALIAS
#endif