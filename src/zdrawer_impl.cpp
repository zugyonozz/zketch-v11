#include "zdrawer.h"

#define USE_ZDRAWER_HELPER

void drawRect(HDC hdc, const Quad& rect, const Color& fill, const Color& outline, uint thickness) noexcept {
	GDIPLUS_BOUNDARY::Gdiplus::Graphics g(hdc) ;
	GDIPLUS_BOUNDARY::Gdiplus::SolidBrush f(static_cast<GDIPLUS_BOUNDARY::Gdiplus::Color>(fill)) ;
	GDIPLUS_BOUNDARY::Gdiplus::Pen o(static_cast<GDIPLUS_BOUNDARY::Gdiplus::Color>(outline), thickness) ;

	g.FillRectangle(&f, static_cast<GDIPLUS_BOUNDARY::Gdiplus::RectF>(rect)) ;
	g.DrawRectangle(&o, static_cast<GDIPLUS_BOUNDARY::Gdiplus::RectF>(rect)) ;
}

void drawEllipse(HDC hdc, const Quad& rect, const Color& fill, const Color& outline, uint thickness) noexcept {
	GDIPLUS_BOUNDARY::Gdiplus::Graphics g(hdc) ;
	GDIPLUS_BOUNDARY::Gdiplus::SolidBrush f(static_cast<GDIPLUS_BOUNDARY::Gdiplus::Color>(fill)) ;
	GDIPLUS_BOUNDARY::Gdiplus::Pen o(static_cast<GDIPLUS_BOUNDARY::Gdiplus::Color>(outline), thickness) ;

	g.FillEllipse(&f, static_cast<GDIPLUS_BOUNDARY::Gdiplus::RectF>(rect)) ;
	g.DrawEllipse(&o, static_cast<GDIPLUS_BOUNDARY::Gdiplus::RectF>(rect)) ;
}

#ifdef USE_ZDRAWER_HELPER

GDIPLUS_BOUNDARY::Gdiplus::GraphicsPath* CreateRoundedRectPath(const Quad& rect, float radius) noexcept {
	auto path = new GDIPLUS_BOUNDARY::Gdiplus::GraphicsPath() ;
	
	float diameter = radius * 2 ;
	Quad arcRect ;

	arcRect = Quad(rect.x, rect.y, diameter, diameter) ;
	path->AddArc(static_cast<GDIPLUS_BOUNDARY::Gdiplus::RectF>(arcRect), 180, 90) ;

	arcRect = Quad(rect.x + rect.w - diameter, rect.y, diameter, diameter) ;
	path->AddArc(static_cast<GDIPLUS_BOUNDARY::Gdiplus::RectF>(arcRect), 270, 90) ;

	arcRect = Quad(rect.x + rect.w - diameter, rect.y + rect.h - diameter, diameter, diameter) ;
	path->AddArc(static_cast<GDIPLUS_BOUNDARY::Gdiplus::RectF>(arcRect), 0, 90) ;

	arcRect = Quad(rect.x, rect.y + rect.h - diameter, diameter, diameter) ;
	path->AddArc(static_cast<GDIPLUS_BOUNDARY::Gdiplus::RectF>(arcRect), 90, 90) ;

	path->CloseFigure() ;
	return path ;
}

#endif

void drawRect(HDC hdc, const Quad& rect, const Color& fill, const Color& outline, float radius, uint thickness) noexcept {
	GDIPLUS_BOUNDARY::Gdiplus::Graphics g(hdc) ;
	GDIPLUS_BOUNDARY::Gdiplus::SolidBrush f(static_cast<GDIPLUS_BOUNDARY::Gdiplus::Color>(fill)) ;
	GDIPLUS_BOUNDARY::Gdiplus::Pen o(static_cast<GDIPLUS_BOUNDARY::Gdiplus::Color>(outline), thickness) ;
	GDIPLUS_BOUNDARY::Gdiplus::GraphicsPath* p = CreateRoundedRectPath(rect, radius) ;

	g.FillPath(&f, p) ;
	g.DrawPath(&o, p) ;

	delete p ;
}

void drawPixels(HDC hdc, const Vertex& verts, const Color& fill, const Color& outline, uint thickness) noexcept {
	if (verts.empty()) return ;
	
	GDIPLUS_BOUNDARY::Gdiplus::Graphics g(hdc) ;
	GDIPLUS_BOUNDARY::Gdiplus::SolidBrush f(static_cast<GDIPLUS_BOUNDARY::Gdiplus::Color>(fill)) ;
	GDIPLUS_BOUNDARY::Gdiplus::Pen o(static_cast<GDIPLUS_BOUNDARY::Gdiplus::Color>(outline), thickness) ;
	
	std::vector<GDIPLUS_BOUNDARY::Gdiplus::Point> points ;
	points.reserve(verts.size()) ;
	for (const auto& v : verts) 
		points.emplace_back(v.x, v.y);
	
	g.FillPolygon(&f, points.data(), points.size()) ;
	g.DrawPolygon(&o, points.data(), points.size()) ;
}

void drawArc(HDC hdc, const Quad& rect, float startAngle, float sweepAngle, const Color& fill, const Color& outline, uint thickness) noexcept {
	GDIPLUS_BOUNDARY::Gdiplus::Graphics g(hdc) ;
	GDIPLUS_BOUNDARY::Gdiplus::SolidBrush f(static_cast<GDIPLUS_BOUNDARY::Gdiplus::Color>(fill)) ;
	GDIPLUS_BOUNDARY::Gdiplus::Pen o(static_cast<GDIPLUS_BOUNDARY::Gdiplus::Color>(outline), thickness) ;
	GDIPLUS_BOUNDARY::Gdiplus::GraphicsPath p ;

	p.AddArc(static_cast<GDIPLUS_BOUNDARY::Gdiplus::RectF>(rect), startAngle, sweepAngle) ;
	
	float centerX = rect.x + rect.w / 2 ;
	float centerY = rect.y + rect.h / 2 ;
	
	float startRad = (startAngle * 3.14159f) / 180.0f ;
	float endRad = ((startAngle + sweepAngle) * 3.14159f) / 180.0f ;
	
	float startX = centerX + (rect.w / 2) * cos(startRad) ;
	float startY = centerY + (rect.h / 2) * sin(startRad ) ;
	float endX = centerX + (rect.w / 2) * cos(endRad) ;
	float endY = centerY + (rect.h / 2) * sin(endRad) ;
	
	p.AddLine(centerX, centerY, startX, startY) ;
	p.AddLine(endX, endY, centerX, centerY) ;
	p.CloseFigure();
	
	g.FillPath(&f, &p) ;
	g.DrawArc(&o, static_cast<GDIPLUS_BOUNDARY::Gdiplus::RectF>(rect), startAngle, sweepAngle) ;
}

void drawPie(HDC hdc, const Quad& rect, float start, float end, const Color& fill, const Color& outline, uint thickness) noexcept {
	GDIPLUS_BOUNDARY::Gdiplus::Graphics g(hdc) ;
	GDIPLUS_BOUNDARY::Gdiplus::SolidBrush f(static_cast<GDIPLUS_BOUNDARY::Gdiplus::Color>(fill)) ;
	GDIPLUS_BOUNDARY::Gdiplus::Pen o(static_cast<GDIPLUS_BOUNDARY::Gdiplus::Color>(outline), thickness) ;

	float sweepAngle = end - start ;
	g.FillPie(&f, static_cast<GDIPLUS_BOUNDARY::Gdiplus::RectF>(rect), start, sweepAngle) ;
	g.DrawPie(&o, static_cast<GDIPLUS_BOUNDARY::Gdiplus::RectF>(rect), start, sweepAngle) ;
}

void drawText(HDC hdc, const wchar_t*& text, const Point& pos, const Color& color, const Font& fontSpec) noexcept {
    GDIPLUS_BOUNDARY::Gdiplus::Graphics g(hdc);
    GDIPLUS_BOUNDARY::Gdiplus::SolidBrush brush(static_cast<GDIPLUS_BOUNDARY::Gdiplus::Color>(color));
    GDIPLUS_BOUNDARY::Gdiplus::FontFamily fontFamily(fontSpec.name);
    GDIPLUS_BOUNDARY::Gdiplus::Font font(&fontFamily, fontSpec.size, fontSpec.style, GDIPLUS_BOUNDARY::Gdiplus::UnitPixel);

    g.DrawString(text, wcslen(text), &font, GDIPLUS_BOUNDARY::Gdiplus::PointF(pos.x, pos.y), &brush) ;
}