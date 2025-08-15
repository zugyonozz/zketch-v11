#pragma once

#define USE_Z_ALIAS

#include "zbitmap.h"

// Basic rectangle drawing
void drawRect(HDC hdc, const QuadF& rect, const Color& fill, const Color& outline, uint thickness = 1) noexcept;

// Ellipse drawing
void drawEllipse(HDC hdc, const QuadF& rect, const Color& fill, const Color& outline, uint thickness = 1) noexcept;

// Rounded rectangle drawing
void drawRect(HDC hdc, const QuadF& rect, const Color& fill, const Color& outline, float radius, uint thickness = 1) noexcept;

// Polygon drawing
void drawPixels(HDC hdc, const Vertex& verts, const Color& fill, const Color& outline, uint thickness = 1) noexcept;

// Arc drawing (sector/pie slice with fill)
void drawArc(HDC hdc, const QuadF& rect, float startAngle, float sweepAngle, const Color& fill, const Color& outline, uint thickness = 1) noexcept;

// Pie drawing
void drawPie(HDC hdc, const QuadF& rect, float start, float end, const Color& fill, const Color& outline, uint thickness = 1) noexcept;

#undef USE_Z_ALIAS