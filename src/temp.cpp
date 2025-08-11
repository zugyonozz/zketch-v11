#define ZEVRECEIVE 

#include <iostream>
#include "../includes/zwindow.h"
#define ZWINDOWDEBUG

int main() {
	Window w1("Window 1", Point<uint>{800, 600}) ;
	Window w2("Window 2", Point<uint>{800, 600}) ;
	w1.show() ;
	w2.show() ;
	w1.centerOnScreen() ;

	while (!w1.shouldClose() || !w2.shouldClose()) {
		Window::processMessages() ;
		Event ev1, ev2 ;
		while (w1.pollEvent(ev1)) {
			if (ev1.type == EventType::Close)
				w1.close() ;
			if (ev1.type == EventType::MouseMove)
				std::cout << "Window 1\t: {" << ev1.getMousePosition().x << ", " << ev1.getMousePosition().y << "}\n" ;
		}

		while (w2.pollEvent(ev2)) {
			if (ev2.type == EventType::Close)
				w2.close() ;
			if (ev2.type == EventType::MouseMove)
				std::cout << "Window 2\t: {" << ev2.getMousePosition().x << ", " << ev2.getMousePosition().y << "}\n" ;
		}

		// Event globalEvent ;
        // while (Window::pollGlobalEvent(globalEvent)) {
        //     if (globalEvent.isFromWindow(w1.getHandle())) {
        //         // Event dari window 1
        //         printf("Global event from Window 1\n");
        //     }
        //     else if (globalEvent.isFromWindow(w2.getHandle())) {
        //         // Event dari window 2
        //         printf("Global event from Window 2\n");
        //     }
        // }
	}
}