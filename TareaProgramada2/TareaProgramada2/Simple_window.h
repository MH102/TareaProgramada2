
#include "GUI.h"	// for Simple_window only (doesn't really belong in Window.h)

using namespace Graph_lib;

// Simple_window is basic scaffolding for ultra-simple interaction with graphics
// it provides one window with one "next" button for ultra-simple animation

struct Simple_window : Window {
	Simple_window(Point xy, int w, int h, const string& title)
		: Window(xy, w, h, title),
		button_pushed(false),
		next_button(Point(85, 40), 70, 20, "Aceptar", cb_next),
	error(Point(0,20),"¡Error!, no se ha abierto ningún archivo"){
		attach(next_button);
		attach(error);
	}

	void wait_for_button()
		// modified event loop
		// handle all events (as per default), but quit when button_pushed becomes true
		// this allows graphics without control inversion
	{
		while (!button_pushed) Fl::wait();
		button_pushed = false;
		Fl::redraw();
	}

	Button next_button;
	Text error;
private:
	bool button_pushed;

	static void cb_next(Address, Address addr) // callback for next_button
	//	{ reference_to<Simple_window>(addr).next(); }
	{
		static_cast<Simple_window*>(addr)->next();
	}

	void next() { button_pushed = true; }

};