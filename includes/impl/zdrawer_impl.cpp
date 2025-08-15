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
	if (verts.empty()) return ;
	
	Gdiplus::Graphics g(hdc) ;
	Gdiplus::SolidBrush f(fill) ;
	Gdiplus::Pen o(outline, thickness) ;
	
	std::vector<Gdiplus::Point> points ;
	points.reserve(verts.size()) ;
	for (const auto& v : verts) 
		points.emplace_back(v.X, v.Y);
	
	g.FillPolygon(&f, points.data(), points.size()) ;
	g.DrawPolygon(&o, points.data(), points.size()) ;
}

void drawArc(HDC hdc, const QuadF& rect, float startAngle, float sweepAngle, const Color& fill, const Color& outline, uint thickness) noexcept {
	Gdiplus::Graphics g(hdc) ;
	Gdiplus::SolidBrush f(fill) ;
	Gdiplus::Pen o(outline, thickness) ;
	Gdiplus::GraphicsPath p ;

	p.AddArc(rect, startAngle, sweepAngle) ;
	
	float centerX = rect.X + rect.Width / 2 ;
	float centerY = rect.Y + rect.Height / 2 ;
	
	float startRad = (startAngle * 3.14159f) / 180.0f ;
	float endRad = ((startAngle + sweepAngle) * 3.14159f) / 180.0f ;
	
	float startX = centerX + (rect.Width / 2) * cos(startRad) ;
	float startY = centerY + (rect.Height / 2) * sin(startRad ) ;
	float endX = centerX + (rect.Width / 2) * cos(endRad) ;
	float endY = centerY + (rect.Height / 2) * sin(endRad) ;
	
	p.AddLine(centerX, centerY, startX, startY) ;
	p.AddLine(endX, endY, centerX, centerY) ;
	p.CloseFigure();
	
	g.FillPath(&f, &p) ;
	g.DrawArc(&o, rect, startAngle, sweepAngle) ;
}

void drawPie(HDC hdc, const QuadF& rect, float start, float end, const Color& fill, const Color& outline, uint thickness) noexcept {
	Gdiplus::Graphics g(hdc) ;
	Gdiplus::SolidBrush f(fill) ;
	Gdiplus::Pen o(outline, thickness) ;

	float sweepAngle = end - start ;
	g.FillPie(&f, rect, start, sweepAngle) ;
	g.DrawPie(&o, rect, start, sweepAngle) ;
}