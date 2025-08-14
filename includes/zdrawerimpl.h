#pragma once

inline void drawRect(HDC hdc, const RECT& rect, const Color& fill, const Color& outline, uint thickness) noexcept {
    HBRUSH b0 = CreateSolidBrush(static_cast<COLORREF>(fill));
    HBRUSH b1 = static_cast<HBRUSH>(SelectObject(hdc, b0)) ;

    HPEN p0 = CreatePen(PS_SOLID, thickness, static_cast<COLORREF>(outline));
    HPEN p1 = static_cast<HPEN>(SelectObject(hdc, p0)) ;

    Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom) ;

    SelectObject(hdc, b1) ;
	SelectObject(hdc, p1) ;
	DeleteObject(b0) ;
	DeleteObject(p0) ;
}

inline void drawEllipse(HDC hdc, const RECT& rect, const Color& fill, const Color& outline, uint thickness) noexcept {
	HBRUSH b0 = CreateSolidBrush(static_cast<COLORREF>(fill)) ;
	HBRUSH b1 = static_cast<HBRUSH>(SelectObject(hdc, b0)) ;

	HPEN p0 = CreatePen(PS_SOLID, thickness, static_cast<COLORREF>(outline)) ;
	HPEN p1 = static_cast<HPEN>(SelectObject(hdc, p0)) ;

	Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom) ;

	SelectObject(hdc, b1) ;
	DeleteObject(b0) ;

	SelectObject(hdc, p1) ;
	DeleteObject(p0) ;
}

inline void drawRect(HDC hdc, const RECT& rect, const Color& fill, const Color& outline, uint cw, uint ch, uint thickness) noexcept {
	HBRUSH b0 = CreateSolidBrush(static_cast<COLORREF>(fill)) ;
	HBRUSH b1 = static_cast<HBRUSH>(SelectObject(hdc, b0)) ;

	HPEN p0 = CreatePen(PS_SOLID, thickness, static_cast<COLORREF>(outline)) ;
	HPEN p1 = static_cast<HPEN>(SelectObject(hdc, p0)) ;

	RoundRect(hdc, rect.left, rect.top, rect.right, rect.bottom, cw, ch) ;

	SelectObject(hdc, b1) ;
	DeleteObject(b0) ;

	SelectObject(hdc, p1) ;
	DeleteObject(p0) ;
}

inline void drawPixel(HDC hdc, const Vertex& verts, const Color& fill, const Color& outline, uint thickness) noexcept {
	HBRUSH b0 = CreateSolidBrush(static_cast<COLORREF>(fill)) ;
	HBRUSH b1 = static_cast<HBRUSH>(SelectObject(hdc, b0)) ;

	HPEN p0 = CreatePen(PS_SOLID, thickness, static_cast<COLORREF>(outline)) ;
	HPEN p1 = static_cast<HPEN>(SelectObject(hdc, p0)) ;

	Polygon(hdc, verts.data(), verts.size()) ;

	SelectObject(hdc, b1) ;
	DeleteObject(b0) ;

	SelectObject(hdc, p1) ;
	DeleteObject(p0) ;
}

inline void drawArc(HDC hdc, const RECT& rect, const POINT& start, const POINT& end, const Color& outline, uint thickness) noexcept {
    HPEN p0 = CreatePen(PS_SOLID, thickness, static_cast<COLORREF>(outline));
    HPEN p1 = static_cast<HPEN>(SelectObject(hdc, p0));

    Arc(hdc, rect.left, rect.top, rect.right, rect.bottom, start.x, start.y, end.x, end.y);

    SelectObject(hdc, p1); DeleteObject(p0);
}

inline void drawChord(HDC hdc, const RECT& rect, const POINT& start, const POINT& end, const Color& fill, const Color& outline, uint thickness) noexcept {
    HBRUSH b0 = CreateSolidBrush(static_cast<COLORREF>(fill));
    HBRUSH b1 = static_cast<HBRUSH>(SelectObject(hdc, b0));

    HPEN p0 = CreatePen(PS_SOLID, thickness, static_cast<COLORREF>(outline));
    HPEN p1 = static_cast<HPEN>(SelectObject(hdc, p0));

    Chord(hdc, rect.left, rect.top, rect.right, rect.bottom, start.x, start.y, end.x, end.y);

    SelectObject(hdc, b1); DeleteObject(b0);
    SelectObject(hdc, p1); DeleteObject(p0);
}

inline void drawPie(HDC hdc, const RECT& rect, const POINT& start, const POINT& end, const Color& fill, const Color& outline, uint thickness) noexcept {
    HBRUSH b0 = CreateSolidBrush(static_cast<COLORREF>(fill));
    HBRUSH b1 = static_cast<HBRUSH>(SelectObject(hdc, b0));

    HPEN p0 = CreatePen(PS_SOLID, thickness, static_cast<COLORREF>(outline));
    HPEN p1 = static_cast<HPEN>(SelectObject(hdc, p0));

    Pie(hdc, rect.left, rect.top, rect.right, rect.bottom, start.x, start.y, end.x, end.y);

    SelectObject(hdc, b1); DeleteObject(b0);
    SelectObject(hdc, p1); DeleteObject(p0);
}

inline void drawPolyline(HDC hdc, const Vertex& verts, const Color& outline, uint thickness) noexcept {
	if (verts.size() < 2)
		return ;

	HPEN p0 = CreatePen(PS_SOLID, thickness, static_cast<COLORREF>(outline)) ;
	HPEN p1 = static_cast<HPEN>(SelectObject(hdc, p0)) ;

	Polyline(hdc, verts.data(), verts.size()) ;

	SelectObject(hdc, p1) ;
	DeleteObject(p0) ;
}

inline void drawPolyBezier(HDC hdc, const Vertex& verts, const Color& outline, uint thickness) noexcept {
	if (verts.size() < 3)
		return ;

	if ((verts.size() - 1) % 3 != 0)
        return ;

	HPEN p0 = CreatePen(PS_SOLID, thickness, static_cast<COLORREF>(outline)) ;
	HPEN p1 = static_cast<HPEN>(SelectObject(hdc, p0)) ;

	PolyBezier(hdc, verts.data(), verts.size()) ;

	SelectObject(hdc, p1) ;
	DeleteObject(p0) ;
}

inline void drawPolyBezierTo(HDC hdc, const Vertex& verts, const Color& outline, uint thickness) noexcept {
    if (verts.size() < 3)
        return ;

    HPEN p0 = CreatePen(PS_SOLID, thickness, static_cast<COLORREF>(outline)) ;
    HGDIOBJ p1 = SelectObject(hdc, p0) ;

    PolyBezierTo(hdc, verts.data(), verts.size()) ;

    SelectObject(hdc, p1) ;
    DeleteObject(p0) ;
}

inline void drawBitmap(HDC hdc, const Rect& rect, const Bitmap& bmp) noexcept {
    if (!bmp) 
		return ;

    HDC hdcMem = CreateCompatibleDC(hdc) ;
    HGDIOBJ oldBmp = SelectObject(hdcMem, bmp) ;
    StretchBlt(hdc, rect.x, rect.y, rect.w, rect.h, hdcMem, 0, 0, bmp.getWidth(), bmp.getHeight(), SRCCOPY) ;
    SelectObject(hdcMem, oldBmp) ;
    DeleteDC(hdcMem) ;
}

inline void drawBitmapAlpha(HDC hdc, const Pos& pos, const Bitmap& bmp, BYTE alpha) noexcept {
    if (!bmp) 
		return ;

    HDC hdcMem = CreateCompatibleDC(hdc) ;
    HGDIOBJ oldBmp = SelectObject(hdcMem, bmp) ;

    BLENDFUNCTION bf{} ;
    bf.BlendOp = AC_SRC_OVER ;
    bf.SourceConstantAlpha = alpha ;
    bf.AlphaFormat = AC_SRC_ALPHA ;

    AlphaBlend(hdc, pos.x, pos.y, bmp.getWidth(), bmp.getHeight(), hdcMem, 0, 0, bmp.getWidth(), bmp.getHeight(), bf) ;

    SelectObject(hdcMem, oldBmp) ;
    DeleteDC(hdcMem) ;
}

inline void drawBitmapTransparent(HDC hdc, const Pos& pos, const Bitmap& bmp, COLORREF transColor) noexcept {
    if (!bmp) 
		return ;

    HDC hdcMem = CreateCompatibleDC(hdc) ;
    HGDIOBJ oldBmp = SelectObject(hdcMem, bmp) ;

    TransparentBlt(hdc, pos.x, pos.y, bmp.getWidth(), bmp.getHeight(), hdcMem, 0, 0, bmp.getWidth(), bmp.getHeight(), transColor) ;

    SelectObject(hdcMem, oldBmp) ;
    DeleteDC(hdcMem) ;
}