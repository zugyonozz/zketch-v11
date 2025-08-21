#include <iostream>
#include <exception>
#include "zwindow.h"
#include "ztimer.h" 
#include "ztexture.h"
#include "zinput.h"      
#include "zanim.h"

using namespace zketch ;

class EnhancedApp : public Window<EnhancedApp> {
private:
    // Core rendering
    Image logo ;
    Renderer renderer ;
    Canvas canvas ;
    
    // Input system
    InputManager input ;
    
    // Animation system
    Animator animator ;
    
    // UI Elements
    struct Button {
        Quad bounds ;
        str text ;
        Color color = Color::White() ;
        Color hover_color = {200, 200, 255, 255} ;
        Color press_color = {150, 150, 200, 255} ;
        bool hovered = false ;
        bool pressed = false ;
        std::function<void()> onclick ;
        
        // Default constructor
        Button() = default ;
        
        // Constructor dengan parameters
        Button(const str& button_text, const Quad& button_bounds) 
            : bounds(button_bounds), text(button_text) {}
        
        // Constructor dengan text, bounds, dan color
        Button(const str& button_text, const Quad& button_bounds, const Color& button_color)
            : bounds(button_bounds), text(button_text), color(button_color) {}
        
        void update(const Point& mouse_pos, bool mouse_down) {
            bool was_hovered = hovered ;
            hovered = geometry::contains(bounds, mouse_pos) ;
            pressed = hovered && mouse_down ;
        }
        
        void draw(Renderer& r) const {
            Color draw_color = pressed ? press_color : (hovered ? hover_color : color) ;
            r.FillRect(bounds, draw_color) ;
            r.DrawRect(bounds, Color::Black(), 2.0f) ;
            
            // Simple text centering
            Point text_pos = bounds.getPos() + bounds.getSize() * 0.5f ;
            text_pos.y -= 10 ; // Rough text height adjustment
            Font font{L"Arial", 16.0f, FontStyle::Regular} ;
            
            // Convert string to wstring for display
            std::wstring wtext(text.begin(), text.end()) ;
            r.DrawString(wtext.c_str(), text_pos, Color::Black(), font) ;
        }
    } ;
    
    std::vector<Button> buttons ;
    
    // Animation properties
    float rotation = 0.0f ;
    float scale = 1.0f ;
    Point animated_pos = {400, 300} ;
    
    bool need_redraw = true ;
    
public:
    EnhancedApp(cstr title, const Point& size) : Window(title, size) {
        setupUI() ;
    }
    
    void setupUI() {
        // Setup buttons with proper error handling
        try {
            buttons.clear() ;
            buttons.reserve(3) ;
            
            // Method 1: Using emplace_back with constructor
            buttons.emplace_back("Animate Rotation", Quad{50, 50, 150, 40}) ;
            buttons.back().onclick = [this]() {
                animator.animate(rotation, rotation + 360.0f, 2.0f, EasingType::QuadOut,
                    [this](float value) { 
                        rotation = value ; 
                        need_redraw = true ; 
                        invalidate() ; 
                    }) ;
            } ;
            
            buttons.emplace_back("Pulse Scale", Quad{50, 100, 150, 40}) ;
            buttons.back().onclick = [this]() {
                animator.animate(scale, 1.5f, 0.5f, EasingType::BounceOut,
                    [this](float value) { 
                        scale = value ; 
                        need_redraw = true ; 
                        invalidate() ; 
                    }) ;
                // Return to normal after
                animator.animate(1.5f, 1.0f, 0.5f, EasingType::QuadIn,
                    [this](float value) { 
                        scale = value ; 
                        need_redraw = true ; 
                        invalidate() ; 
                    }) ;
            } ;
            
            buttons.emplace_back("Move Object", Quad{50, 150, 150, 40}) ;
            buttons.back().onclick = [this]() {
                Point current = animated_pos ;
                Point target = {
                    static_cast<float>(rand() % 600 + 100), 
                    static_cast<float>(rand() % 400 + 100)
                } ;
                
                animator.animate(current.x, target.x, 1.0f, EasingType::QuadInOut,
                    [this](float value) { 
                        animated_pos.x = value ; 
                        need_redraw = true ; 
                        invalidate() ; 
                    }) ;
                animator.animate(current.y, target.y, 1.0f, EasingType::QuadInOut,
                    [this](float value) { 
                        animated_pos.y = value ; 
                        need_redraw = true ; 
                        invalidate() ; 
                    }) ;
            } ;
        } catch (const std::exception& e) {
            std::cerr << "Error in setupUI: " << e.what() << std::endl ;
        }
    }

    void OnCreate() noexcept {
        try {
            std::cout << "OnCreate called - testing GDI+ first..." << std::endl ;
            
            // Test GDI+ initialization first
            std::cout << "Testing GDI+ with simple bitmap..." << std::endl ;
            std::flush(std::cout) ;
            
            try {
                auto test_bmp = std::make_unique<Gdiplus::Bitmap>(100, 100, PixelFormat32bppARGB) ;
                if (test_bmp && test_bmp->GetLastStatus() == Gdiplus::Ok) {
                    std::cout << "GDI+ test bitmap: SUCCESS" << std::endl ;
                } else {
                    std::cout << "GDI+ test bitmap: FAILED - Status: " << (test_bmp ? test_bmp->GetLastStatus() : -1) << std::endl ;
                }
            } catch (...) {
                std::cout << "GDI+ test bitmap: EXCEPTION THROWN" << std::endl ;
            }
            
            Point client_size = get_client_size() ;
            std::cout << "Client size: " << client_size.x << "x" << client_size.y << std::endl ;
            
            if (client_size.x > 0 && client_size.y > 0) {
                std::cout << "About to create canvas..." << std::endl ;
                std::flush(std::cout) ;
                
                // Create canvas with more detailed error checking
                canvas.Create(client_size) ;
                
                std::cout << "Canvas creation completed" << std::endl ;
                std::flush(std::cout) ;
            } else {
                std::cout << "Invalid client size, skipping canvas creation" << std::endl ;
            }
            
            std::cout << "Skipping logo loading for now..." << std::endl ;
            std::cout << "OnCreate completed successfully" << std::endl ;
            std::flush(std::cout) ;
        } catch (const zketch::error_handler::failed_init_gdiplussession&) {
            std::cerr << "FATAL: GDI+ session failed in OnCreate" << std::endl ;
        } catch (const std::exception& e) {
            std::cerr << "Exception in OnCreate: " << e.what() << std::endl ;
        } catch (...) {
            std::cerr << "Unknown exception in OnCreate" << std::endl ;
        }
    }

    void OnResize(const Point& newSize) noexcept {
        try {
            std::cout << "OnResize called: " << newSize.x << "x" << newSize.y << std::endl ;
            
            if (newSize.x > 0 && newSize.y > 0) {
                bool canvas_ok = canvas.Create(newSize) ;
                if (canvas_ok) {
                    need_redraw = true ;
                    invalidate() ;
                } else {
                    std::cerr << "Failed to recreate canvas on resize" << std::endl ;
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Exception in OnResize: " << e.what() << std::endl ;
        }
    }

    void RedrawScene() noexcept {
        try {
            if (!canvas.isValid()) {
                std::cout << "Canvas not valid, skipping redraw" << std::endl ;
                return ;
            }
            
            if (renderer.Begin(canvas)) {
                // Clear with gradient-like effect
                renderer.Clear({20, 25, 35, 255}) ;
                
                // Draw simple test content first
                DrawSimpleContent() ;
                
                // Draw UI
                DrawUI() ;
                
                renderer.End() ;
                need_redraw = false ;
            } else {
                std::cerr << "Failed to begin rendering" << std::endl ;
            }
        } catch (const std::exception& e) {
            std::cerr << "Exception in RedrawScene: " << e.what() << std::endl ;
        }
    }
    
    void DrawSimpleContent() {
        try {
            Point center = get_client_size() * 0.5f ;
            
            // Draw simple rectangle
            Quad test_rect = {center.x - 50, center.y - 50, 100, 100} ;
            renderer.FillRect(test_rect, {255, 100, 100, 200}) ;
            renderer.DrawRect(test_rect, Color::White(), 2.0f) ;
            
            // Draw scaled circle at animated position
            float radius = 30.0f * scale ;
            renderer.FillCircle(animated_pos, radius, {100, 255, 100, 200}) ;
            renderer.DrawCircle(animated_pos, radius, Color::White(), 2.0f) ;
            
            // Draw logo if available
            if (logo.isValid()) {
                Quad logo_rect = {center.x - 64, center.y + 100, 128, 128} ;
                renderer.DrawImage(logo, logo_rect) ;
            }
        } catch (const std::exception& e) {
            std::cerr << "Exception in DrawSimpleContent: " << e.what() << std::endl ;
        }
    }
    
    void DrawUI() {
        try {
            for (auto& button : buttons) {
                button.draw(renderer) ;
            }
            
            // Draw simple text info
            Point size = get_client_size() ;
            renderer.DrawString(L"zketch Framework Demo", 
                Point{50, 20}, 
                Color::White(), 
                {L"Arial", 18.0f, FontStyle::Bold}) ;
            
            // Draw input state
            Point mouse = input.getMousePos() ;
            std::wstring mouse_info = L"Mouse: (" + std::to_wstring(static_cast<int>(mouse.x)) + 
                                     L", " + std::to_wstring(static_cast<int>(mouse.y)) + L")" ;
            renderer.DrawString(mouse_info.c_str(), 
                Point{50, size.y - 60}, 
                Color::White(), 
                {L"Arial", 14.0f, FontStyle::Regular}) ;
            
        } catch (const std::exception& e) {
            std::cerr << "Exception in DrawUI: " << e.what() << std::endl ;
        }
    }

    void OnPaint(HDC hdc) noexcept {
        try {
            if (need_redraw || !canvas.isValid()) {
                RedrawScene() ;
            }
            
            if (canvas.isValid()) {
                canvas.Present(hdc) ;
            } else {
                std::cout << "Canvas not valid in OnPaint" << std::endl ;
            }
        } catch (const std::exception& e) {
            std::cerr << "Exception in OnPaint: " << e.what() << std::endl ;
        }
    }
    
    void Update(float deltaTime) {
        try {
            // Update input
            input.update() ;
            
            // Update animations
            animator.update(deltaTime) ;
            
            // Update UI elements
            Point mouse_pos = input.getMousePos() ;
            bool mouse_down = input.isMouseDown(0) ; // Left button
            
            for (auto& button : buttons) {
                button.update(mouse_pos, mouse_down) ;
            }
            
            // Handle button clicks
            if (input.isMousePressed(0)) {
                for (auto& button : buttons) {
                    if (button.hovered && button.onclick) {
                        button.onclick() ;
                    }
                }
            }
            
            // Handle keyboard input for movement
            Point movement{} ;
            if (input.isKeyDown('W')) movement.y -= 200.0f * deltaTime ;
            if (input.isKeyDown('S')) movement.y += 200.0f * deltaTime ;
            if (input.isKeyDown('A')) movement.x -= 200.0f * deltaTime ;
            if (input.isKeyDown('D')) movement.x += 200.0f * deltaTime ;
            
            if (movement.x != 0.0f || movement.y != 0.0f) {
                animated_pos += movement ;
                need_redraw = true ;
                invalidate() ;
            }
            
            // Handle special keys
            if (input.isKeyPressed(VK_F1)) {
                ShowHelp() ;
            }
            
            if (input.isKeyPressed(VK_F5)) {
                need_redraw = true ;
                invalidate() ;
            }
            
            // Continuous rotation when space is held
            if (input.isKeyDown(VK_SPACE)) {
                rotation += 90.0f * deltaTime ;
                need_redraw = true ;
                invalidate() ;
            }
        } catch (const std::exception& e) {
            std::cerr << "Exception in Update: " << e.what() << std::endl ;
        }
    }
    
    void ShowHelp() {
        MessageBoxA(handle(), 
            "zketch Framework Demo\n\n"
            "Controls:\n"
            "• WASD - Move green circle\n"
            "• SPACE - Continuous rotation\n"
            "• F1 - Show this help\n"
            "• F5 - Force refresh\n"
            "• ESC - Exit\n"
            "• Click buttons for animations",
            "Help", MB_OK | MB_ICONINFORMATION) ;
    }

    void ProcessInput(const Event& event) {
        try {
            switch (event.type) {
                case EventType::KeyDown:
                    input.setKeyDown(event.key.keyCode) ;
                    break ;
                case EventType::KeyUp:
                    input.setKeyUp(event.key.keyCode) ;
                    break ;
                case EventType::MouseMove:
                    input.setMousePos(event.getMousePosition()) ;
                    need_redraw = true ; // UI hover effects
                    break ;
                case EventType::MouseDown:
                    if (event.mouse.button == MouseButton::Left) {
                        input.setMouseDown(0) ;
                    } else if (event.mouse.button == MouseButton::Right) {
                        input.setMouseDown(1) ;
                    }
                    break ;
                case EventType::MouseUp:
                    if (event.mouse.button == MouseButton::Left) {
                        input.setMouseUp(0) ;
                    } else if (event.mouse.button == MouseButton::Right) {
                        input.setMouseUp(1) ;
                    }
                    break ;
                default:
                    break ;
            }
        } catch (const std::exception& e) {
            std::cerr << "Exception in ProcessInput: " << e.what() << std::endl ;
        }
    }

    void OnClose() noexcept {
        std::cout << "Enhanced App closing gracefully..." << std::endl ;
    }
} ;

int main() {
    // Add console allocation for debugging
    AllocConsole() ;
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout) ;
    freopen_s((FILE**)stderr, "CONOUT$", "w", stderr) ;
    freopen_s((FILE**)stdin, "CONIN$", "r", stdin) ;
    
    std::cout << "=== zketch Framework Debug Version ===" << std::endl ;
    
    try {
        // Initialize random seed for demo
        srand(static_cast<unsigned>(time(nullptr))) ;
        
        std::cout << "Creating application..." << std::endl ;
        
        // Create smaller window first for testing
        EnhancedApp app("zketch Framework - Debug Version", {800, 600}) ;
        
        std::cout << "Application created successfully" << std::endl ;
        std::cout << "Window count: " << EnhancedApp::get_window_count() << std::endl ;
        
        app.show() ;
        app.center_on_screen() ;
        
        std::cout << "Window shown, entering main loop..." << std::endl ;
        
        Timer frame_timer ;
        
        // Simplified main loop for debugging
        while (app.is_valid() && !app.should_close()) {
            frame_timer.start() ;
            
            // Process Windows messages
            if (!EnhancedApp::process_messages()) {
                std::cout << "Process messages returned false, exiting..." << std::endl ;
                break ;
            }
            
            // Process events
            Event event ;
            while (app.poll_event(event)) {
                app.ProcessInput(event) ;
                
                switch (event.type) {
                    case EventType::Close:
                    case EventType::Quit:
                        std::cout << "Close/Quit event received" << std::endl ;
                        app.close() ;
                        break ;
                        
                    case EventType::KeyDown:
                        std::cout << "Key pressed: " << event.key.keyCode << std::endl ;
                        if (event.key.keyCode == VK_ESCAPE) {
                            std::cout << "ESC pressed, closing..." << std::endl ;
                            app.close() ;
                        }
                        break ;
                    
                    default:
                        break ;
                }
            }
            
            // Update with delta time
            double frame_time = frame_timer.duration<milliseconds_>() ;
            app.Update(static_cast<float>(frame_time / 1000.0)) ;
            
            // Simple frame limiting
            if (frame_time < 16.0) { // ~60 FPS
                Sleep(static_cast<DWORD>(16.0 - frame_time)) ;
            }
        }
        
        std::cout << "Main loop ended normally" << std::endl ;
        
    } catch (const zketch::error_handler::failed_init_gdiplussession&) {
        std::cerr << "FATAL: Failed to initialize GDI+ session" << std::endl ;
        std::cerr << "Make sure you have proper GDI+ support on your system" << std::endl ;
        return -1 ;
    } catch (const zketch::error_handler::register_class_failed&) {
        std::cerr << "FATAL: Failed to register window class" << std::endl ;
        return -2 ;
    } catch (const zketch::error_handler::create_window_failed&) {
        std::cerr << "FATAL: Failed to create window" << std::endl ;
        return -3 ;
    } catch (const std::exception& e) {
        std::cerr << "FATAL ERROR: " << e.what() << std::endl ;
        return -4 ;
    } catch (...) {
        std::cerr << "FATAL: Unknown exception occurred" << std::endl ;
        return -5 ;
    }
    
    std::cout << "Application finished successfully" << std::endl ;
    std::cout << "Press any key to continue..." << std::endl ;
    std::cin.get() ;
    
    return 0 ;
}