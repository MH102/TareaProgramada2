#pragma once
#include "GUI.h"
using namespace Graph_lib;
struct Ventana :
	public Window
{
	void prueba() {
		cedula.deactivate();
	}

	 static void operation(Address, Address addr) {
		 static_cast<Ventana*>(addr)->prueba();
	}
	bool button_pushed;
	In_box cedula;
	In_box nombre;
	In_box primerApellido;
	In_box segundoApellido;
	In_box nacimiento;
public:
	Button operation_button;
	MenuBar bar;
	Ventana(Point xy, int w, int h, const string& title)
		: Window(xy, w, h, title),
		button_pushed(false),
		operation_button(Point(10,50), 70, 20, "Next", operation),
		cedula(Point(150, 100), 80, 20, "Cedula"),
		nombre(Point(150,130),100,20,"Nombre"),
		primerApellido(Point(150,160),100,20,"Primer Apellido"),
		segundoApellido(Point(150,190),100,20,"Segundo Apellido"),
		nacimiento(Point(150, 220), 100, 20, "Fecha de nacimiento"),
		bar(Point(0,0),600,30,"Archivo"){
		attach(cedula);
		attach(nombre);
		attach(primerApellido);
		attach(segundoApellido);
		attach(nacimiento);
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

