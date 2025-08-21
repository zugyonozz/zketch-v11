#pragma once

#include <algorithm>
#include <functional>

#include "ztimer.h"

namespace zketch {

    enum class EasingType {
        Linear,
        QuadIn, QuadOut, QuadInOut,
        CubicIn, CubicOut, CubicInOut,
        BounceOut
    } ;

    class Animator {
    private:
        struct Animation {
            float start_value ;
            float end_value ;
            float duration ;
            float elapsed ;
            EasingType easing ;
            std::function<void(float)> callback ;
            bool active = false ;
        } ;
        
        std::vector<Animation> animations_ ;
        
    public:
        static float ease(float t, EasingType type) noexcept {
            switch (type) {
                case EasingType::Linear : return t ;
                case EasingType::QuadIn : return t * t ;
                case EasingType::QuadOut : return 1.0f - (1.0f - t) * (1.0f - t) ;
                case EasingType::QuadInOut : return t < 0.5f ? 2.0f * t * t : 1.0f - 2.0f * (1.0f - t) * (1.0f - t) ;
                case EasingType::CubicIn : return t * t * t ;
                case EasingType::CubicOut : return 1.0f - (1.0f - t) * (1.0f - t) * (1.0f - t) ;
                case EasingType::BounceOut: {
					if (t < 1.0f / 2.75f)
						return 7.5625f * t * t ;

					if (t < 2.0f / 2.75f) {
						t -= 1.5f / 2.75f ;
						return 7.5625f * t * t + 0.75f ;
					}

					if (t < 2.5f / 2.75f) {
						t -= 2.25f / 2.75f ;
						return 7.5625f * t * t + 0.9375f ;
					}

					t -= 2.625f / 2.75f ;
					return 7.5625f * t * t + 0.984375f ;
				}
                default : return t ;
            }
        }
        
        void animate(float from, float to, float duration, EasingType easing, std::function<void(float)> callback) {
            animations_.push_back({from, to, duration, 0.0f, easing, callback, true}) ;
        }
        
        void update(float deltaTime) {
            for (auto& anim : animations_) {
                if (!anim.active) 
					continue ;
                
                anim.elapsed += deltaTime ;
                float t = std::min(anim.elapsed / anim.duration, 1.0f) ;
                float eased_t = ease(t, anim.easing) ;
                float value = anim.start_value + (anim.end_value - anim.start_value) * eased_t ;
                
                anim.callback(value) ;
                
                if (t >= 1.0f) {
                    anim.active = false ;
                }
            }
            
            // Remove finished animations
            animations_.erase(
                std::remove_if(animations_.begin(), animations_.end(), 
                    [](const Animation& a) { return !a.active ; }
				),
                animations_.end()
            ) ;
        }
        
        void clear() {
            animations_.clear() ;
        }
    } ;
}