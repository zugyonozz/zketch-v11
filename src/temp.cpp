#include <iostream>
#include "zwindow.h"
#include "ztimer.h"
#include "zdrawer.h"

using namespace zketch ;

class App : public Window<App> {
public:
    App(cstr title, const Point& size) noexcept : Window(title, size) {}
    
    // Constructor with position support
    App(cstr title, const Point& size, const Point& pos) noexcept 
        : Window(title, size, pos) {}

    // OnPaint method - automatically detected by SFINAE
    void OnPaint(HDC hdc) const noexcept {
        // Draw a magenta rectangle with black border
        drawRect(hdc, Quad{0, 0, 200, 200}, 
                 Color(255, 255, 0, 255),    // Magenta fill
                 Color(255, 0, 0, 0));       // Black outline
        
        // Draw some additional shapes to show performance
        drawEllipse(hdc, Quad{50, 50, 100, 100}, 
                   Color(0, 255, 0, 255),     // Green fill
                   Color(255, 255, 255, 255)); // White outline
		// draw text
		drawText(
			hdc, L"Hello World", 
			{get_client_bounds().getSize() / 2}, 
			{255, 0, 255, 255}, // magenta
			{L"Arial", 48.0f, FontStyle::BoldItalic}) ;
    }

    // Optional: Custom close handling
    void OnClose() const noexcept {
        std::cout << "App is closing gracefully...\n";
    }
};

int main() {
    try {
        Timer t;
        
        App main_window("Advanced App Window", {1200, 900});
        
        // Chain operations for better performance
        main_window.show();
        main_window.center_on_screen();
        
        std::cout << "Window created successfully!\n";
        std::cout << "Window count: " << App::get_window_count() << "\n";
        std::cout << "Window bounds: " << main_window.bounds() << "\n";
        
        // Performance counters
        int frame_count = 0;
        double total_time = 0.0;
        
        while (!main_window.should_close()) {
            t.start() ;
            
            App::process_messages();
            
            Event event;
            while (main_window.poll_event(event)) {
                switch (event.type) {
                    case EventType::Close:
                        main_window.close();
                        break;
                        
                    case EventType::MouseMove: {
                        Point mouse_pos = event.getMousePosition();
                        
                        static int mouse_counter = 0;
                        if (++mouse_counter % 10 == 0) {
                            std::cout << "Mouse: {" << mouse_pos.x << ", " << mouse_pos.y << "}\n";
                        }
                        break;
                    }
                    
                    case EventType::KeyDown:
                        if (event.key.keyCode == VK_ESCAPE) {
                            main_window.close();
                        } else if (event.key.keyCode == VK_F11) {
                            // Toggle fullscreen (example)
                            static bool fullscreen = false;
                            if (fullscreen) {
                                main_window.restore();
                            } else {
                                main_window.maximize();
                            }
                            fullscreen = !fullscreen;
                        }
                        break;
                        
                    case EventType::Resize: {
                        Point new_size = event.getResizeSize();
                        std::cout << "Window resized to: " << new_size << "\n";
                        break;
                    }
                    
                    default:
                        break;
                }
            }
            
            double frame_time = t.duration<milliseconds_>();
            total_time += frame_time;
            frame_count++;
            
    
            if (frame_count % 60 == 0) {
                double avg_frame_time = total_time / frame_count;
                double fps = 1000.0 / avg_frame_time;
                std::cout << "Avg Frame Time: " << avg_frame_time << "ms, FPS: " << fps << "\n";
            }
            
            // Cap at ~60 FPS (16.67ms per frame)
            t.delay(16);
        }
        
        std::cout << "\nSession Stats:\n";
        std::cout << "Total Frames: " << frame_count << "\n";
        std::cout << "Total Time: " << total_time << "ms\n";
        std::cout << "Average FPS: " << (1000.0 * frame_count / total_time) << "\n";
        std::cout << "Remaining windows: " << App::get_window_count() << "\n";
        
    } catch (const error_handler::register_class_failed& e) {
        std::cerr << "ERROR: " << e.what() << "\n";
        return -1;
    } catch (const error_handler::create_window_failed& e) {
        std::cerr << "ERROR: " << e.what() << "\n";
        return -2;
    } catch (const std::exception& e) {
        std::cerr << "UNEXPECTED ERROR: " << e.what() << "\n";
        return -3;
    }
    
    return 0;
}