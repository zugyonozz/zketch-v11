// #define ZWINDOW_DEBUG
// #define DEBUG_ALL

#include <iostream>
#include "../includes/zwindow.h"
#include "../includes/ztimer.h"
#include "../includes/zdrawer.h"

class win : public Window<win> {
public :
	Bitmap b ;

	win(cstr title, const ::Size& size) noexcept : Window(title, size), b(LoadBMP("sample.bmp")) {
		if (!b) 
			std::cout << "Gagal load bitmap!\n" ;
		else 
			std::cout << "Sukses load bitmap!\n" ;
	}

	void OnPaint(HDC hdc) const noexcept {
		drawBitmap(hdc, getClientBound(), b) ;
	}
	void OnClose() const noexcept {}
} ;

int main() {
	Timer t ;
	win w1("Window 1", Size{1200, 900}) ;
	w1.show() ;
	w1.centerOnScreen() ;

	while (!w1.shouldClose()) {
		win::processMessages() ;
		Event ev1, ev2 ;
		while (w1.pollEvent(ev1)) {
			if (ev1.type == EventType::Close)
				w1.close() ;
			if (ev1.type == EventType::MouseMove)
				std::cout << "Window 1\t: {" << ev1.getMousePosition().x << ", " << ev1.getMousePosition().y << "}\n" ;
		}
		t.delay(16) ;
	}
}