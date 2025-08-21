#define ZKETCH_DEBUG
#include "ztexture.h"
#include "zwindow.h"
#include "zinput.h"
#include "ztimer.h"

using namespace zketch ;

struct Node {
	int val = 0 ;
	Node* next = nullptr ;

	Node(int val) noexcept : val(val) {}
} ;

struct List {
	Node* head = nullptr ;

	List(const List&) = delete ;

    List& operator=(const List&) = delete ;

	List() noexcept = default ;

	List(int val) noexcept {
		head = new Node(val) ;
	}

	List& Add(int val) noexcept {
		Node* newNode = new Node(val) ;
		if (!head) {
			head = newNode ;
			return *this ;
		}
		Node* tmp = head ;
		while(tmp->next) 
			tmp = tmp->next ;
		tmp->next = newNode ;
		return *this ;
	}

	~List() noexcept {
		while(head) {
			Node* tmp = head ;
			head = head->next ;
			delete tmp ;
		}
	}
} ;

class Demo : public Window<Demo> {
private :
	Renderer renderer ;
	Canvas canvas ;
	bool redraw = false ;

public :
	Demo(cstr AppTitle, const Point& size) noexcept : Window<Demo>(AppTitle, size) {}

	void drawUI() {
		if (renderer.Begin(canvas)) {
			// background
			renderer.FillRect(get_client_bounds(), Color::Black()) ;

			// navbar container
			Quad Rect = get_client_bounds() ;
			Rect.setSize({Rect.w, Rect.h / 8}) ;
			renderer.FillRect(Rect , Color::Magenta()) ;
		}
		renderer.End() ;
		redraw = false ;
	}

	void OnResize(const Point& newSize) {
		zlog::info("OnResize Called!\n") ;
		if (!canvas.isValid())
			canvas.Create(newSize) ;
		redraw = true ;
	}

	void OnPaint(HDC hdc) noexcept {
		if (redraw || !canvas.isValid())
			drawUI() ;
		if (canvas.isValid())
			canvas.Present(hdc) ;
		else 
            zlog::warning("Canvas not valid in OnPaint\n") ;
	}

} ;

int main() {
	Demo app("Zketch Demo", {1280, 960}) ;

	app.show() ;
	app.center_on_screen() ;

	Timer timer ;
	InputManager input ;

	while (app.is_valid() && !app.should_close()) {
		timer.start() ;
		Demo::process_messages() ;

		Event e ;

		while (app.poll_event(e)) {
			switch (e.type) {
				case EventType::Close :
				case EventType::Quit :
					app.close() ;
					break ;
				case EventType::KeyDown :
					input.setKeyDown(e.key.keyCode) ;
					if (input.isKeyDown('W'))
						zlog::info("W - pressed\n") ;
					break ;
				case EventType::Resize :
					app.OnResize(app.get_client_size()) ;
				default : 
					break ;
			}

			timer.delay(16) ;
		}
	}


	return 0 ;
}