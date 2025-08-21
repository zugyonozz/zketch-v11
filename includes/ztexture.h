#pragma once

#ifndef USE_ZTEXTURE_HELPER
	#define USE_ZTEXTURE_HELPER
#endif

// standard header
#include <memory>

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
			bmp_ = std::make_unique<Gdiplus::Bitmap>(filepath) ;

			if (bmp_ && bmp_->GetLastStatus() == Gdiplus::Ok) {
				size_ = {bmp_->GetWidth(), bmp_->GetHeight()} ;
				return true ;
			}

			bmp_.reset() ;
			size_ = {} ;
			return false ;
		}

		float getWidth() const noexcept { return size_.x ; }
		float getHeight() const noexcept { return size_.y ; }
		bool isValid() const noexcept { return bmp_ != nullptr ; }
	} ;

    class Canvas {
		friend class Renderer ;
    private:
		std::unique_ptr<Gdiplus::Bitmap> bmp_ ;
        Point size_ = {} ;

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

			if (size.contains([](float n) { return n <= 0.0f ; }))
				return false ;

			bmp_ = std::make_unique<Gdiplus::Bitmap>(size.x, size.y, PixelFormat32bppARGB) ;

			if (bmp_ && bmp_->GetLastStatus() == Gdiplus::Ok) {
				size_ = size ;
				return true ;
			}

			bmp_.reset() ;
			return false ;
		}

		void Present(HDC targetHdc) const {
            if (!bmp_ || !targetHdc) 
				return ;

            Gdiplus::Graphics screenGraphics(targetHdc) ;
            screenGraphics.DrawImage(bmp_.get(), 0, 0) ;
        }

        float getWidth() const noexcept {
            return size_.x ;
        }

        float getHeight() const noexcept {
            return size_.y ;
        }

        bool isValid() const noexcept {
            return bmp_ != nullptr ;
        }
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

		bool isValid() const noexcept {
			if (!gfx_) {
				#if defined(ZKECTH_DEBUG)
					zlog::warning("gfx is nullptr!") ;
				#endif

				return false ;
			}
			return true ;
		}

	public :
		Renderer() noexcept = default ;
		~Renderer() noexcept = default ;

		Renderer(const Renderer&) noexcept = delete ;
		Renderer& operator=(const Renderer&) noexcept = delete ;

		template <typename ... Fn>
		bool Draw(Canvas& canvas, Fn&& ... fn) noexcept requires (is_draw_function<Fn>::val && ...) {
			if (!Begin(canvas))
				return false ;
			(fn(),  ...) ;
			End() ;
			return true ;
		}

		bool Begin(Canvas& canvas) noexcept {
			if (!canvas.isValid()) 
				return false ;
            
            gfx_ = std::make_unique<Gdiplus::Graphics>(canvas.bmp_.get()) ;
            if (gfx_ && gfx_->GetLastStatus() == Gdiplus::Ok) {
                targetCanvas_ = &canvas;
                gfx_->SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias) ;
                gfx_->SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic) ;
                gfx_->SetPixelOffsetMode(Gdiplus::PixelOffsetModeHighQuality) ;
                return true ;
            }
            return false ;
		}

		void End() noexcept {
			gfx_.reset() ;
			targetCanvas_ = nullptr ;
		}

		void Clear(const Color& color) {
            if (!gfx_) 
				return ;
            gfx_->Clear(color) ;
        }

		void DrawRect(const Quad& rect, const Color& color, float thickness = 1.0f) noexcept {
			if (!isValid())
				return ;

			if (thickness < 0.1f) {
				#if defined(ZKECTH_DEBUG)
					zlog::warning("thickness lower than 0.1") ;
				#endif
				return ;
			}

			Gdiplus::Pen p(color, thickness) ;
			gfx_->DrawRectangle(&p, static_cast<Gdiplus::RectF>(rect)) ;
		}

		void FillRect(const Quad& rect, const Color& color) noexcept {
			if (!isValid())
				return ;

			Gdiplus::SolidBrush b(color) ;
			gfx_->FillRectangle(&b, static_cast<Gdiplus::RectF>(rect)) ;
		}

		void DrawEllipse(const Quad& rect, const Color& color, float thickness = 1.0f) noexcept {
            if (!isValid()) 
				return ;

            Gdiplus::Pen p(color, thickness) ;
            gfx_->DrawEllipse(&p, static_cast<Gdiplus::RectF>(rect)) ;
        }

        void FillEllipse(const Quad& rect, const Color& color) {
            if (!isValid()) 
				return ;

            Gdiplus::SolidBrush b(color) ;
            gfx_->FillEllipse(&b, rect.x, rect.y, rect.w, rect.h);
        }

		void DrawString(const cwstr& text, const Point& pos, const Color& color, const Font& font) noexcept {
			Gdiplus::SolidBrush brush(color) ;
			Gdiplus::FontFamily family(font.family()) ;
			Gdiplus::Font f(&family, font.size(), font.style(), Gdiplus::UnitPixel) ;

			gfx_->DrawString(text, wcslen(text), &f, pos, &brush) ;
		}

		void DrawImage(const Image& image, const Point& pos) {
            if (!gfx_ || !image.isValid()) 
				return ;
            gfx_->DrawImage(image.bmp_.get(), pos.x, pos.y) ;
        }

        void DrawImage(const Image& image, const Quad& destRect) {
            if (!gfx_ || !image.isValid()) 
				return ;
            gfx_->DrawImage(image.bmp_.get(), static_cast<Gdiplus::RectF>(destRect)) ;
        }
	} ;

} // namespace zketch

#ifdef USE_ZTEXTURE_HELPER
	#undef USE_ZTEXTURE_HELPER
#endif