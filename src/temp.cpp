// #define ZWINDOW_DEBUG
// #define DEBUG_ALL

#include <iostream>
#include "../includes/zwindow.h"
#include "../includes/ztimer.h"
#include "../includes/zdrawer.h"

class win : public Window<win> {
public :
	win(cstr title, const SZ& size) noexcept : Window(title, size) {}

	void OnPaint(HDC hdc) const noexcept {
		drawRect(hdc, {0, 0, 200, 200}, Color(255, 0, 255, 255), Color(255, 0, 0, 0), 2) ;
	}
	void OnClose() const noexcept {}
} ;

int main() {
	Timer t ;
	win w1("Window 1", {1200, 900}) ;
	w1.show() ;
	w1.centerOnScreen() ;

	while (!w1.shouldClose()) {
		win::processMessages() ;
		Event ev1, ev2 ;
		while (w1.pollEvent(ev1)) {
			if (ev1.type == EventType::Close)
				w1.close() ;
			if (ev1.type == EventType::MouseMove)
				std::cout << "Window 1\t: {" << ev1.getMousePosition().X << ", " << ev1.getMousePosition().Y << "}\n" ;
		}
		t.delay(16) ;
	}
}