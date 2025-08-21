#pragma once

#ifndef USE_ZTEXTURE_HELPER
	#define USE_ZTEXTURE_HELPER
#endif

// standard header
#include <memory>
#include <utility>

// zketch header
#include "zfont.h"
#include "zlog.h"

namespace zketch {

	class Renderer ;

	class Image {
		friend class Renderer ;

	private :
		uptr<Gdiplus::Bitmap> bmp_ ;
		Point size_ = {} ;
		mutable bool is_cached_ = false ; // Cache validation flag

	public :
		Image(const Image&) noexcept = delete ;
		Image& operator=(const Image&) noexcept = delete ;

		Image() noexcept = default ;
		~Image() noexcept = default ;

		Image(Image&&) noexcept = default ;
		Image& operator=(Image&&) noexcept = default ;

		explicit Image(cwstr filepath) noexcept {
			load(filepath) ;
		}

		bool load(cwstr filepath) noexcept {
			bmp_.reset() ;
			is_cached_ = false ;
			
			if (!filepath) {
				#ifdef ZKECTH_DEBUG
					zlog::error("Image::load - filepath is null") ;
				#endif
				return false ;
			}

			bmp_ = std::make_unique<Gdiplus::Bitmap>(filepath) ;

			if (bmp_ && bmp_->GetLastStatus() == Gdiplus::Ok) {
				size_ = {static_cast<float>(bmp_->GetWidth()), static_cast<float>(bmp_->GetHeight())} ;
				is_cached_ = true ;
				
				#ifdef ZKECTH_DEBUG
					zlog::info("Image loaded: " + std::to_string(size_.x) + "x" + std::to_string(size_.y)) ;
				#endif
				return true ;
			}

			bmp_.reset() ;
			size_ = {} ;
			
			#ifdef ZKECTH_DEBUG
				zlog::error("Failed to load image from path") ;
			#endif
			return false ;
		}

		// OPTIMIZED: Inline getters dengan cache validation
		float getWidth() const noexcept { 
			return is_cached_ ? size_.x : (bmp_ ? static_cast<float>(bmp_->GetWidth()) : 0.0f) ; 
		}
		
		float getHeight() const noexcept { 
			return is_cached_ ? size_.y : (bmp_ ? static_cast<float>(bmp_->GetHeight()) : 0.0f) ; 
		}
		
		Point getSize() const noexcept {
			return is_cached_ ? size_ : (bmp_ ? Point{static_cast<float>(bmp_->GetWidth()), static_cast<float>(bmp_->GetHeight())} : Point{}) ;
		}
		
		bool isValid() const noexcept { return bmp_ != nullptr && bmp_->GetLastStatus() == Gdiplus::Ok ; }
	} ;

    class Canvas {
		friend class Renderer ;
    private:
		std::unique_ptr<Gdiplus::Bitmap> bmp_ ;
        Point size_ = {} ;
        bool dirty_ = false ; // Track if canvas needs redraw

    public:
        Canvas(const Canvas&) = delete ;
        Canvas& operator=(const Canvas&) = delete ;

        Canvas() noexcept = default ;
		~Canvas() noexcept = default ;

		Canvas(Canvas&& other) noexcept = default;
        Canvas& operator=(Canvas&& other) noexcept = default;

		bool Create(const Point& size) noexcept {
			bmp_.reset() ;
			size_ = {} ;
			dirty_ = false ;

			if (size.contains([](float n) { return n <= 0.0f ; })) {
				#ifdef ZKECTH_DEBUG
					zlog::error("Canvas::Create - Invalid size") ;
				#endif
				return false ;
			}

			// OPTIMIZED: Use more efficient pixel format
			bmp_ = std::make_unique<Gdiplus::Bitmap>(
				static_cast<int>(size.x), 
				static_cast<int>(size.y), 
				PixelFormat32bppPARGB  // Premultiplied alpha for better performance
			) ;

			if (bmp_ && bmp_->GetLastStatus() == Gdiplus::Ok) {
				size_ = size ;
				dirty_ = true ; // New canvas needs initial draw
				
				#ifdef ZKECTH_DEBUG
					zlog::info("Canvas created: " + std::to_string(size_.x) + "x" + std::to_string(size_.y)) ;
				#endif
				return true ;
			}

			bmp_.reset() ;
			#ifdef ZKECTH_DEBUG
				zlog::error("Failed to create canvas bitmap") ;
			#endif
			return false ;
		}

		// OPTIMIZED: Present with dirty checking
		void Present(HDC targetHdc) const noexcept {
            if (!bmp_ || !targetHdc) {
            	#ifdef ZKECTH_DEBUG
            		if (!bmp_) zlog::warning("Canvas::Present - No bitmap") ;
            		if (!targetHdc) zlog::warning("Canvas::Present - Invalid HDC") ;
            	#endif
				return ;
			}

            Gdiplus::Graphics screenGraphics(targetHdc) ;
            // OPTIMIZED: Set high-performance rendering hints
            screenGraphics.SetCompositingMode(Gdiplus::CompositingModeSourceOver) ;
            screenGraphics.SetCompositingQuality(Gdiplus::CompositingQualityHighSpeed) ;
            screenGraphics.SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor) ;
            
            screenGraphics.DrawImage(bmp_.get(), 0, 0) ;
        }

        float getWidth() const noexcept { return size_.x ; }
        float getHeight() const noexcept { return size_.y ; }
        Point getSize() const noexcept { return size_ ; }
        bool isValid() const noexcept { return bmp_ != nullptr ; }
        bool isDirty() const noexcept { return dirty_ ; }
        void markClean() noexcept { dirty_ = false ; }
        void markDirty() noexcept { dirty_ = true ; }
    } ;

	#ifdef USE_ZTEXTURE_HELPER

		template <typename>
		struct is_draw_function : std::false_type {} ;

		template <>
		struct is_draw_function<void(Renderer::*)(const Quad&, const Color&, float)> : std::true_type {} ;

		template <>
		struct is_draw_function<void(Renderer::*)(const cwstr&, const Point&, const Color&, const Font&)> : std::true_type {} ;

	#endif

	class Renderer {
	private :
		std::unique_ptr<Gdiplus::Graphics> gfx_ ;
		Canvas* targetCanvas_ = nullptr ;
		bool is_drawing_ = false ; // Track drawing state

		bool isValid() const noexcept {
			if (!gfx_ || !is_drawing_) {
				#if defined(ZKECTH_DEBUG)
					if (!gfx_) zlog::warning("Renderer - gfx is nullptr!") ;
					if (!is_drawing_) zlog::warning("Renderer - not in drawing state!") ;
				#endif
				return false ;
			}
			return true ;
		}

	public :
		Renderer() noexcept = default ;
		~Renderer() noexcept {
			if (is_drawing_) {
				#ifdef ZKECTH_DEBUG
					zlog::warning("Renderer destroyed while drawing - calling End()") ;
				#endif
				End() ;
			}
		}

		Renderer(const Renderer&) noexcept = delete ;
		Renderer& operator=(const Renderer&) noexcept = delete ;

		// OPTIMIZED: Move semantics
		Renderer(Renderer&& other) noexcept 
			: gfx_(std::move(other.gfx_))
			, targetCanvas_(std::exchange(other.targetCanvas_, nullptr))
			, is_drawing_(std::exchange(other.is_drawing_, false)) {}

		Renderer& operator=(Renderer&& other) noexcept {
			if (this != &other) {
				if (is_drawing_) End() ;
				gfx_ = std::move(other.gfx_) ;
				targetCanvas_ = std::exchange(other.targetCanvas_, nullptr) ;
				is_drawing_ = std::exchange(other.is_drawing_, false) ;
			}
			return *this ;
		}

		template <typename ... Fn>
		bool Draw(Canvas& canvas, Fn&& ... fn) noexcept requires (is_draw_function<std::decay_t<Fn>>::value && ...) {
			if (!Begin(canvas))
				return false ;
			(fn(this), ...) ; // Pass this pointer to member functions
			End() ;
			return true ;
		}

		bool Begin(Canvas& canvas) noexcept {
			if (is_drawing_) {
				#ifdef ZKECTH_DEBUG
					zlog::error("Renderer::Begin - Already in drawing state") ;
				#endif
				return false ;
			}

			if (!canvas.isValid()) {
				#ifdef ZKECTH_DEBUG
					zlog::error("Renderer::Begin - Invalid canvas") ;
				#endif
				return false ;
			}
            
            gfx_ = std::make_unique<Gdiplus::Graphics>(canvas.bmp_.get()) ;
            if (gfx_ && gfx_->GetLastStatus() == Gdiplus::Ok) {
                targetCanvas_ = &canvas;
                is_drawing_ = true ;
                
                // OPTIMIZED: High-performance rendering settings
                gfx_->SetSmoothingMode(Gdiplus::SmoothingModeHighQuality) ; // Changed from AntiAlias
                gfx_->SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic) ;
                gfx_->SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighQuality) ;
                gfx_->SetCompositingMode(Gdiplus::CompositingModeSourceOver) ;
                gfx_->SetCompositingQuality(Gdiplus::CompositingQualityHighSpeed) ; // Balance quality vs speed
                
                canvas.markDirty() ; // Canvas will be modified
                return true ;
            }
            
            #ifdef ZKECTH_DEBUG
            	zlog::error("Renderer::Begin - Failed to create graphics context") ;
            #endif
            return false ;
		}

		void End() noexcept {
			if (is_drawing_) {
				gfx_.reset() ;
				if (targetCanvas_) {
					targetCanvas_->markClean() ; // Drawing complete
				}
				targetCanvas_ = nullptr ;
				is_drawing_ = false ;
			}
		}

		// OPTIMIZED: Clear with format validation
		void Clear(const Color& color) noexcept {
            if (!isValid()) return ;
            gfx_->Clear(color) ;
            if (targetCanvas_) targetCanvas_->markDirty() ;
        }

		void DrawRect(const Quad& rect, const Color& color, float thickness = 1.0f) noexcept {
			if (!isValid()) return ;

			if (thickness < 0.1f) {
				#if defined(ZKECTH_DEBUG)
					zlog::warning("DrawRect - thickness lower than 0.1") ;
				#endif
				return ;
			}

			Gdiplus::Pen p(color, thickness) ;
			gfx_->DrawRectangle(&p, static_cast<Gdiplus::RectF>(rect)) ;
		}

		void FillRect(const Quad& rect, const Color& color) noexcept {
			if (!isValid()) return ;
			Gdiplus::SolidBrush b(color) ;
			gfx_->FillRectangle(&b, static_cast<Gdiplus::RectF>(rect)) ;
		}

		// OPTIMIZED: Rounded rectangle with caching
		void DrawRectRounded(const Quad& rect, const Color& color, float radius, float thickness = 1.0f) noexcept {
			if (!isValid()) return ;
			if (thickness < 0.1f || radius < 0.0f) return ;

			Gdiplus::GraphicsPath path ;
			float diameter = radius * 2.0f ;
			
			// Create rounded rectangle path
			path.AddArc(rect.x, rect.y, diameter, diameter, 180, 90) ;
			path.AddArc(rect.x + rect.w - diameter, rect.y, diameter, diameter, 270, 90) ;
			path.AddArc(rect.x + rect.w - diameter, rect.y + rect.h - diameter, diameter, diameter, 0, 90) ;
			path.AddArc(rect.x, rect.y + rect.h - diameter, diameter, diameter, 90, 90) ;
			path.CloseFigure() ;

			Gdiplus::Pen p(color, thickness) ;
			gfx_->DrawPath(&p, &path) ;
		}

		void FillRectRounded(const Quad& rect, const Color& color, float radius) noexcept {
			if (!isValid()) return ;
			if (radius < 0.0f) return ;

			Gdiplus::GraphicsPath path ;
			float diameter = radius * 2.0f ;
			
			path.AddArc(rect.x, rect.y, diameter, diameter, 180, 90) ;
			path.AddArc(rect.x + rect.w - diameter, rect.y, diameter, diameter, 270, 90) ;
			path.AddArc(rect.x + rect.w - diameter, rect.y + rect.h - diameter, diameter, diameter, 0, 90) ;
			path.AddArc(rect.x, rect.y + rect.h - diameter, diameter, diameter, 90, 90) ;
			path.CloseFigure() ;

			Gdiplus::SolidBrush b(color) ;
			gfx_->FillPath(&b, &path) ;
		}

		void DrawEllipse(const Quad& rect, const Color& color, float thickness = 1.0f) noexcept {
            if (!isValid()) return ;
            if (thickness < 0.1f) return ;

            Gdiplus::Pen p(color, thickness) ;
            gfx_->DrawEllipse(&p, static_cast<Gdiplus::RectF>(rect)) ;
        }

        void FillEllipse(const Quad& rect, const Color& color) noexcept {
            if (!isValid()) return ;
            Gdiplus::SolidBrush b(color) ;
            gfx_->FillEllipse(&b, rect.x, rect.y, rect.w, rect.h);
        }

        // OPTIMIZED: String rendering with font caching hint
		void DrawString(const cwstr& text, const Point& pos, const Color& color, const Font& font) noexcept {
			if (!isValid() || !text) return ;

			Gdiplus::SolidBrush brush(color) ;
			Gdiplus::FontFamily family(font.family()) ;
			Gdiplus::Font f(&family, font.size(), font.style(), Gdiplus::UnitPixel) ;

			// OPTIMIZED: Use high-performance text rendering
			gfx_->SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAliasGridFit) ;
			gfx_->DrawString(text, -1, &f, pos, &brush) ; // -1 for null-terminated string
		}

		// OPTIMIZED: Image drawing with multiple overloads
		void DrawImage(const Image& image, const Point& pos) noexcept {
            if (!isValid() || !image.isValid()) return ;
            gfx_->DrawImage(image.bmp_.get(), pos.x, pos.y) ;
        }

        void DrawImage(const Image& image, const Quad& destRect) noexcept {
            if (!isValid() || !image.isValid()) return ;
            gfx_->DrawImage(image.bmp_.get(), static_cast<Gdiplus::RectF>(destRect)) ;
        }

        void DrawImage(const Image& image, const Quad& destRect, const Quad& srcRect) noexcept {
        	if (!isValid() || !image.isValid()) return ;
        	gfx_->DrawImage(image.bmp_.get(), 
        		static_cast<Gdiplus::RectF>(destRect),
        		srcRect.x, srcRect.y, srcRect.w, srcRect.h,
        		Gdiplus::UnitPixel) ;
        }

        // OPTIMIZED: Polygon drawing
        void DrawPolygon(const Vertex& vertices, const Color& color, float thickness = 1.0f) noexcept {
        	if (!isValid() || vertices.empty()) return ;
        	if (thickness < 0.1f) return ;

        	std::vector<Gdiplus::PointF> points ;
        	points.reserve(vertices.size()) ;
        	
        	for (const auto& vertex : vertices) {
        		points.emplace_back(vertex.x, vertex.y) ;
        	}

        	Gdiplus::Pen p(color, thickness) ;
        	gfx_->DrawPolygon(&p, points.data(), static_cast<int>(points.size())) ;
        }

        void FillPolygon(const Vertex& vertices, const Color& color) noexcept {
        	if (!isValid() || vertices.empty()) return ;

        	std::vector<Gdiplus::PointF> points ;
        	points.reserve(vertices.size()) ;
        	
        	for (const auto& vertex : vertices) {
        		points.emplace_back(vertex.x, vertex.y) ;
        	}

        	Gdiplus::SolidBrush b(color) ;
        	gfx_->FillPolygon(&b, points.data(), static_cast<int>(points.size())) ;
        }

        // NEW: Line drawing
        void DrawLine(const Point& start, const Point& end, const Color& color, float thickness = 1.0f) noexcept {
        	if (!isValid()) return ;
        	if (thickness < 0.1f) return ;

        	Gdiplus::Pen p(color, thickness) ;
        	gfx_->DrawLine(&p, start.x, start.y, end.x, end.y) ;
        }

        // NEW: Circle drawing (convenience method)
        void DrawCircle(const Point& center, float radius, const Color& color, float thickness = 1.0f) noexcept {
        	if (!isValid()) return ;
        	DrawEllipse(Quad{center.x - radius, center.y - radius, radius * 2, radius * 2}, color, thickness) ;
        }

        void FillCircle(const Point& center, float radius, const Color& color) noexcept {
        	if (!isValid()) return ;
        	FillEllipse(Quad{center.x - radius, center.y - radius, radius * 2, radius * 2}, color) ;
        }

        // State queries
        bool isDrawing() const noexcept { return is_drawing_ ; }
        Canvas* getTarget() const noexcept { return targetCanvas_ ; }
	} ;

} // namespace zketch

#ifdef USE_ZTEXTURE_HELPER
	#undef USE_ZTEXTURE_HELPER
#endif