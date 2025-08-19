#pragma once

// standard header
#include <memory>
#include <utility>

// zketch header
#include "zunit.h"

namespace zketch {

    class Texture {
    private:
        Point size_ = {} ;
        bool isValid_ = false ;
        std::unique_ptr<Gdiplus::Bitmap> bmp_ ;

    public:
        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;

        Texture() noexcept = default;

        Texture(Texture&& other) noexcept : size_(std::exchange(other.size_, {})), isValid_(std::exchange(other.isValid_, false)), bmp_(std::move(other.bmp_)) {}

        Texture& operator=(Texture&& other) noexcept {
            if (this != &other) {
                bmp_ = std::move(other.bmp_) ;
                size_ = std::exchange(other.size_, {}) ;
                isValid_ = std::exchange(other.isValid_, false) ;
            }
            return *this ;
        }

        explicit Texture(Gdiplus::Bitmap* bmp) noexcept : bmp_(bmp) {
            if (bmp_ && bmp_->GetLastStatus() == Gdiplus::Ok) {
                size_ = { static_cast<float>(bmp_->GetWidth()), static_cast<float>(bmp_->GetHeight()) } ;
                isValid_ = (size_.x > 0 && size_.y > 0) ;
            }
            else 
                cleanup() ;
        }

        ~Texture() noexcept {
            cleanup() ;
        }

        void cleanup() noexcept {
            bmp_.reset() ;
            size_ = {} ;
            isValid_ = false ;
        }

        bool create(const Point& size) {
            if (size.x <= 0 || size.y <= 0)
                return false ;

            bmp_ = std::make_unique<Gdiplus::Bitmap>(static_cast<int>(size.x), static_cast<int>(size.y), PixelFormat32bppPARGB);
            if (!bmp_ || bmp_->GetLastStatus() != Gdiplus::Ok) {
                cleanup() ;
                return false ;
			}

            size_ = size ;
            isValid_ = true ;
            return true ;
        }

        bool drawTo(HDC hdc, const Point& dst, const Point& size = {}) const {
            if (!isValid() || !hdc) 
                return false ;

            Gdiplus::Graphics g(hdc);
            if (size.x > 0 && size.y > 0) {
                Gdiplus::RectF dstRect(dst.x, dst.y, size.x, size.y) ;
                return g.DrawImage(bmp_.get(), dstRect) == Gdiplus::Ok ;
            }
            return g.DrawImage(bmp_.get(), static_cast<int>(dst.x), static_cast<int>(dst.y)) == Gdiplus::Ok ;
        }

        float getWidth() const noexcept {
            return size_.x ;
        }

        float getHeight() const noexcept {
            return size_.y ;
        }

        bool isValid() const noexcept {
            return isValid_ && bmp_ != nullptr ;
        }

        Gdiplus::Bitmap* rawBitmap() const noexcept {
            return bmp_.get() ;
        }
    };

    inline std::unique_ptr<Texture> loadIMG(const wchar_t* path) {
        if (!path) 
            return nullptr;

        auto src = std::unique_ptr<Gdiplus::Bitmap>(Gdiplus::Bitmap::FromFile(path));
        if (!src || src->GetLastStatus() != Gdiplus::Ok) 
            return nullptr ;

        Gdiplus::PixelFormat pf = src->GetPixelFormat();
        if (pf == PixelFormat32bppPARGB || pf == PixelFormat32bppARGB)
            return std::make_unique<Texture>(src.release()) ;
        else {
            int w = src->GetWidth();
            int h = src->GetHeight();
            auto cloned = std::unique_ptr<Gdiplus::Bitmap>(src->Clone(0, 0, w, h, PixelFormat32bppPARGB));

            if (!cloned || cloned->GetLastStatus() != Gdiplus::Ok) 
                return nullptr ;
            
            return std::make_unique<Texture>(cloned.release()) ;
        }
    }

} // namespace zketch
