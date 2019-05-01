#pragma once
#include "GUI.h"
using namespace Graph_lib;
struct Ventana :
	public Window
{
	void caca() {
		cedula.hide();
	}

	 static void operation(Address, Address addr) {
		 static_cast<Ventana*>(addr)->caca();
	}
	bool button_pushed;
	In_box cedula;
public:
	Button operation_button;
	MenuBar bar;
	Ventana(Point xy, int w, int h, const string& title)
		: Window(xy, w, h, title),
		button_pushed(false),
		operation_button(Point(10,50), 70, 20, "Next", operation),
		cedula(Point(100, 100), 50, 20, "Cedula"),
		bar(Point(0,0),600,30,"Archivo"){
		attach(cedula);
		attach(operation_button);
		attach(bar);
		
		
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
	
};

