#pragma once

#define USE_Z_ALIAS

#include "zbitmap.h"

void drawRect(HDC hdc, const QuadF& rect, const Color& fill, const Color& outline, uint thickness = 1) noexcept ;

void drawEllipse(HDC hdc, const QuadF& rect, const Color& fill, const Color& outline, uint thickness = 1) noexcept ;

void drawRect(HDC hdc, const QuadF& rect, const Color& fill, const Color& outline, uint cw, uint ch, uint thickness = 1) noexcept ;

void drawPixel(HDC hdc, const Vertex& verts, const Color& fill, const Color& outline, uint thickness = 1) noexcept ;

void drawArc(HDC hdc, const QuadF& rect, const POINT& start, const POINT& end, const Color& outline, uint thickness = 1) noexcept ;

void drawChord(HDC hdc, const QuadF& rect, const POINT& start, const POINT& end, const Color& fill, const Color& outline, uint thickness = 1) noexcept ;

void drawPie(HDC hdc, const QuadF& rect, const POINT& start, const POINT& end, const Color& fill, const Color& outline, uint thickness = 1) noexcept ;

#undef USE_Z_ALIAS