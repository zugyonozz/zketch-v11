#pragma once
#include "zunit.h"
#include <bitset>

namespace zketch {

    class InputManager {
    private:
        std::bitset<256> keys_down_ ;
        std::bitset<256> keys_pressed_ ;
        std::bitset<256> keys_released_ ;
        
        std::bitset<3> mouse_down_ ;
        std::bitset<3> mouse_pressed_ ;
        std::bitset<3> mouse_released_ ;
        
        Point mouse_pos_ ;
        Point mouse_delta_ ;
        float mouse_wheel_ = 0.0f ;
        
    public:
        void update() noexcept {
            keys_pressed_.reset() ;
            keys_released_.reset() ;
            mouse_pressed_.reset() ;
            mouse_released_.reset() ;
            mouse_wheel_ = 0.0f ;
        }
        
        void setKeyDown(int key) noexcept {
            if (key >= 0 && key < 256 && !keys_down_[key]) 
                keys_pressed_[key] = true ;

            keys_down_[key] = true ;
        }
        
        void setKeyUp(int key) noexcept {
            if (key >= 0 && key < 256 && keys_down_[key]) 
                keys_released_[key] = true ;

            keys_down_[key] = false ;
        }
        
        void setMouseDown(int button) noexcept {
            if (button >= 0 && button < 3 && !mouse_down_[button]) 
                mouse_pressed_[button] = true ;

            mouse_down_[button] = true ;
        }
        
        void setMouseUp(int button) noexcept {
            if (button >= 0 && button < 3 && mouse_down_[button]) 
                mouse_released_[button] = true ;

            mouse_down_[button] = false ;
        }
        
        void setMousePos(const Point& pos) noexcept {
            mouse_delta_ = pos - mouse_pos_ ;
            mouse_pos_ = pos ;
        }
        
        void setMouseWheel(float delta) noexcept {
            mouse_wheel_ = delta ;
        }
        
        // Query methods
        bool isKeyDown(int key) const noexcept {
            return key >= 0 && key < 256 && keys_down_[key] ;
        }
        
        bool isKeyPressed(int key) const noexcept {
            return key >= 0 && key < 256 && keys_pressed_[key] ;
        }
        
        bool isKeyReleased(int key) const noexcept {
            return key >= 0 && key < 256 && keys_released_[key] ;
        }
        
        bool isMouseDown(int button) const noexcept {
            return button >= 0 && button < 3 && mouse_down_[button] ;
        }
        
        bool isMousePressed(int button) const noexcept {
            return button >= 0 && button < 3 && mouse_pressed_[button] ;
        }
        
        bool isMouseReleased(int button) const noexcept {
            return button >= 0 && button < 3 && mouse_released_[button] ;
        }
        
        Point getMousePos() const noexcept { 
			return mouse_pos_ ; 
		}

        Point getMouseDelta() const noexcept { 
			return mouse_delta_ ; 
		}

        float getMouseWheel() const noexcept { 
			return mouse_wheel_ ; 
		}
        
        // Convenience methods
        bool isShiftDown() const noexcept { 
			return isKeyDown(VK_SHIFT) ; 
		}

        bool isCtrlDown() const noexcept { 
			return isKeyDown(VK_CONTROL) ; 
		}

        bool isAltDown() const noexcept { 
			return isKeyDown(VK_MENU) ; 
		}

    } ;
}