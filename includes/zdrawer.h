#pragma once

#define USE_Z_ALIAS

#include "zbitmap.h"

inline void drawRect(HDC hdc, const RECT& rect, const Color& fill, const Color& outline, uint thickness = 1) noexcept ;

inline void drawEllipse(HDC hdc, const RECT& rect, const Color& fill, const Color& outline, uint thickness = 1) noexcept ;

inline void drawRect(HDC hdc, const RECT& rect, const Color& fill, const Color& outline, uint cw, uint ch, uint thickness = 1) noexcept ;

inline void drawPixel(HDC hdc, const Vertex& verts, const Color& fill, const Color& outline, uint thickness = 1) noexcept ;

inline void drawArc(HDC hdc, const RECT& rect, const POINT& start, const POINT& end, const Color& outline, uint thickness = 1) noexcept ;

inline void drawChord(HDC hdc, const RECT& rect, const POINT& start, const POINT& end, const Color& fill, const Color& outline, uint thickness = 1) noexcept ;

inline void drawPie(HDC hdc, const RECT& rect, const POINT& start, const POINT& end, const Color& fill, const Color& outline, uint thickness = 1) noexcept ;

inline void drawPolyline(HDC hdc, const Vertex& verts, const Color& outline, uint thickness = 1) noexcept ;

inline void drawPolyBezier(HDC hdc, const Vertex& verts, const Color& outline, uint thickness = 1) noexcept ;

inline void drawPolyBezierTo(HDC hdc, const Vertex& verts, const Color& outline, uint thickness = 1) noexcept ;

inline void drawBitmap(HDC hdc, const Rect& rect, const Bitmap& bmp) noexcept ;

inline void drawBitmapAlpha(HDC hdc, const Pos& pos, const Bitmap& bmp, BYTE alpha = 255) noexcept ;

inline void drawBitmapTransparent(HDC hdc, const Pos& pos, const Bitmap& bmp, COLORREF transColor) noexcept ;

#include "zdrawerimpl.h"

#undef USE_Z_ALIAS