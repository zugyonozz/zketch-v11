#include "Windows API/Model/z_window.h"

int main() {
	Window w1("Z Framework Demo", Point<uint>{800, 600}) ;
	w1.show() ;
	w1.centerOnScreen() ;

	while (!w1.shouldClose()) {
		Event ev ;
		while (Window::pollEvent(ev)) {
			if (ev.type == EventType::Quit)
				w1.close() ;
		}
	}
}