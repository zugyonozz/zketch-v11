#include "../zdrawer.h"

#define USE_ZDRAWER_HELPER

void drawRect(HDC hdc, const QuadF& rect, const Color& fill, const Color& outline, uint thickness) noexcept {
	Gdiplus::Graphics g(hdc) ;
	Gdiplus::SolidBrush f(fill) ;
    Gdiplus::Pen o(outline, thickness) ;

	g.FillRectangle(&f, rect) ;
	g.DrawRectangle(&o, rect) ;
}

void drawEllipse(HDC hdc, const QuadF& rect, const Color& fill, const Color& outline, uint thickness) noexcept {
	Gdiplus::Graphics g(hdc) ;
	Gdiplus::SolidBrush f(fill) ;
    Gdiplus::Pen o(outline, thickness) ;

	g.FillEllipse(&f, rect) ;
	g.DrawEllipse(&o, rect) ;
}

#ifdef USE_ZDRAWER_HELPER

Gdiplus::GraphicsPath* CreateRoundedRectPath(const QuadF& rect, float radius) noexcept {
    auto path = new Gdiplus::GraphicsPath() ;
    
    float diameter = radius * 2 ;
    QuadF arcRect ;

    arcRect = QuadF(rect.X, rect.Y, diameter, diameter) ;
    path->AddArc(arcRect, 180, 90) ;

    arcRect = QuadF(rect.X + rect.Width - diameter, rect.Y, diameter, diameter) ;
    path->AddArc(arcRect, 270, 90) ;

    arcRect = QuadF(rect.X + rect.Width - diameter, rect.Y + rect.Height - diameter, diameter, diameter) ;
    path->AddArc(arcRect, 0, 90) ;

    arcRect = QuadF(rect.X, rect.Y + rect.Height - diameter, diameter, diameter) ;
    path->AddArc(arcRect, 90, 90) ;

    path->CloseFigure() ;
    return path ;
}


#endif

void drawRect(HDC hdc, const QuadF& rect, const Color& fill, const Color& outline, float radius, uint thickness) noexcept {
	Gdiplus::Graphics g(hdc) ;
	Gdiplus::SolidBrush f(fill) ;
    Gdiplus::Pen o(outline, thickness) ;
	Gdiplus::GraphicsPath* p = CreateRoundedRectPath(rect, radius) ;

	g.FillPath(&f, p) ;
	g.DrawPath(&o, p) ;

	delete p ;
}

void drawPixels(HDC hdc, const Vertex& verts, const Color& fill, const Color& outline, uint thickness) noexcept {
	Gdiplus::Graphics g(hdc) ;
	Gdiplus::SolidBrush f(fill) ;
    Gdiplus::Pen o(outline, thickness) ;
	
	g.FillPolygon(&f, verts.data(), verts.size()) ;
	g.DrawPolygon(&o, verts.data(), verts.size()) ;
}

void drawArc(HDC hdc, const QuadF& rect, float startAngle, float sweepAngle, const Color& fill, const Color& outline, uint thickness) noexcept {
	Gdiplus::Graphics g(hdc) ;
	Gdiplus::SolidBrush f(fill) ;
    Gdiplus::Pen o(outline, thickness) ;
	Gdiplus::GraphicsPath p ;

	PTF lastP ;
	p.GetLastPoint(&lastP) ;

	p.AddArc(rect, startAngle, sweepAngle) ;
	p.AddLine(
		rect.X + rect.Width / 2, rect.Y + rect.Height / 2, 
		lastP.X, 
		lastP.Y
	) ;
	p.CloseFigure() ;
	
	g.FillPath(&f, &p) ;
	g.DrawArc(&o, rect, startAngle, sweepAngle) ;
}

void drawPie(HDC hdc, const QuadF& rect, float start, float end, const Color& fill, const Color& outline, uint thickness) noexcept {
    Gdiplus::Graphics g(hdc) ;
	Gdiplus::SolidBrush f(fill) ;
    Gdiplus::Pen o(outline, thickness) ;

	g.FillPie(&f, rect, start, end) ;
	g.DrawPie(&o, rect, start, end) ;
}