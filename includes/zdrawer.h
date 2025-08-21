#pragma once

#include "ztexture.h"

#ifndef USE_ZDRAWER_HELPER
	#define USE_ZDRAWER_HELPER
#endif

namespace zketch {

	#ifdef USE_ZDRAWER_HELPER

		Gdiplus::GraphicsPath* CreateRoundedRectPath(const Quad& rect, float radius) noexcept {
			auto path = new Gdiplus::GraphicsPath() ;
			
			float diameter = radius * 2 ;
			Gdiplus::RectF arcRect ;

			arcRect = Quad(rect.x, rect.y, diameter, diameter) ;
			path->AddArc(arcRect, 180, 90) ;

			arcRect = Quad(rect.x + rect.w - diameter, rect.y, diameter, diameter) ;
			path->AddArc(arcRect, 270, 90) ;

			arcRect = Quad(rect.x + rect.w - diameter, rect.y + rect.h - diameter, diameter, diameter) ;
			path->AddArc(arcRect, 0, 90) ;

			arcRect = Quad(rect.x, rect.y + rect.h - diameter, diameter, diameter) ;
			path->AddArc(arcRect, 90, 90) ;

			path->CloseFigure() ;
			return path ;
		}

	#endif

	void drawRect(HDC hdc, const Quad& rect, const Color& fill, const Color& outline, ullong thickness) noexcept {
		Gdiplus::Graphics g(hdc) ;
		Gdiplus::SolidBrush f(fill) ;
		Gdiplus::Pen o(outline, thickness) ;

		g.FillRectangle(&f, static_cast<Gdiplus::RectF>(rect)) ;
		g.DrawRectangle(&o, static_cast<Gdiplus::RectF>(rect)) ;
	}

	void drawEllipse(HDC hdc, const Quad& rect, const Color& fill, const Color& outline, ullong thickness) noexcept {
		Gdiplus::Graphics g(hdc) ;
		Gdiplus::SolidBrush f(fill) ;
		Gdiplus::Pen o(outline, thickness) ;

		g.FillEllipse(&f, static_cast<Gdiplus::RectF>(rect)) ;
		g.DrawEllipse(&o, static_cast<Gdiplus::RectF>(rect)) ;
	}

	void drawRect(HDC hdc, const Quad& rect, const Color& fill, const Color& outline, float radius, ullong thickness) noexcept {
		Gdiplus::Graphics g(hdc) ;
		Gdiplus::SolidBrush f(fill) ;
		Gdiplus::Pen o(outline, thickness) ;
		Gdiplus::GraphicsPath* p = CreateRoundedRectPath(rect, radius) ;

		g.FillPath(&f, p) ;
		g.DrawPath(&o, p) ;

		delete p ;
	}

	void drawPixels(HDC hdc, const Vertex& verts, const Color& fill, const Color& outline, ullong thickness) noexcept {
		if (verts.empty()) 
			return ;
		
		Gdiplus::Graphics g(hdc) ;
		Gdiplus::SolidBrush f(fill) ;
		Gdiplus::Pen o(outline, thickness) ;

		std::vector<Gdiplus::PointF> pts ;
		pts.reserve(verts.size()) ;

		for (auto& v : verts) 
			pts.emplace_back(v) ;
		
		g.FillPolygon(&f, pts.data(), pts.size()) ;
		g.DrawPolygon(&o, pts.data(), pts.size()) ;
	}

	void drawArc(HDC hdc, const Quad& rect, float startAngle, float sweepAngle, const Color& fill, const Color& outline, ullong thickness) noexcept {
		Gdiplus::Graphics g(hdc) ;
		Gdiplus::SolidBrush f(fill) ;
		Gdiplus::Pen o(outline, thickness) ;
		Gdiplus::GraphicsPath p ;

		p.AddArc(static_cast<Gdiplus::RectF>(rect), startAngle, sweepAngle) ;
		
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
		g.DrawArc(&o, static_cast<Gdiplus::RectF>(rect), startAngle, sweepAngle) ;
	}

	void drawPie(HDC hdc, const Quad& rect, float start, float end, const Color& fill, const Color& outline, ullong thickness) noexcept {
		Gdiplus::Graphics g(hdc) ;
		Gdiplus::SolidBrush f(fill) ;
		Gdiplus::Pen o(outline, thickness) ;

		float sweepAngle = end - start ;
		g.FillPie(&f, static_cast<Gdiplus::RectF>(rect), start, sweepAngle) ;
		g.DrawPie(&o, static_cast<Gdiplus::RectF>(rect), start, sweepAngle) ;
	}

	void drawText(HDC hdc, const cwstr& text, const Point& pos, const Color& color, const Font& font) noexcept {
		Gdiplus::Graphics g(hdc) ;
		Gdiplus::SolidBrush brush(color) ;
		Gdiplus::FontFamily family(font.family()) ;
		Gdiplus::Font f(&family, font.size(), font.style(), Gdiplus::UnitPixel) ;

		g.DrawString(text, wcslen(text), &f, pos, &brush) ;
	}

}

#ifdef USE_ZDRAWER_HELPER
	#undef USE_ZDRAWER_HELPER
#endif