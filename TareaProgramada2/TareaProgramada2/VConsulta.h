#pragma once
#include "GUI.h"
#include "Ventana.h"
using namespace Graph_lib;
struct VConsulta :
	public Window
{
	void consul() {
		string cedu = cedula.get_string();
		if (cedu.size()!= 9) {
			salida.put("Cedula invalida");
			return;
		}
		if (!tabla.verificarCedula(cedu)) {
			salida.put("La cedula no existe");
			return;
		}
		string colisiones = tabla.get(cedu);
		vector<string> vec = split(colisiones, ';');
		cedula.put(vec.at(0));
		nombre.put(vec.at(1));
		primerApellido.put(vec.at(2));
		segundoApellido.put(vec.at(3));
		nacimiento.put(vec.at(4));
		salida.put( "Colisiones encontradas: "+vec.at(5));
		
	}

	static void consulta_cb(Address, Address addr) {
		static_cast<VConsulta*>(addr)->consul();
	}
	bool button_pushed;
	In_box cedula;
	In_box nombre;
	In_box primerApellido;
	In_box segundoApellido;
	In_box nacimiento;
	Out_box salida;
	HashMap& tabla;
public:
	Button BtnConsulta;
	VConsulta(Point xy, int w, int h, const string& title,HashMap& tablaHash)
		: Window(xy, w, h, title),
		button_pushed(false),
		BtnConsulta(Point(240, 100), 70, 20, "Consultar", consulta_cb),
		cedula(Point(150, 100), 80, 20, "Cedula"),
		nombre(Point(150, 130), 100, 20, "Nombre"),
		primerApellido(Point(150, 160), 100, 20, "Primer Apellido"),
		segundoApellido(Point(150, 190), 100, 20, "Segundo Apellido"),
		nacimiento(Point(150, 220), 100, 20, "Fecha de nacimiento"),
		tabla(tablaHash),
		salida(Point(0, 478), 500, 20, "")
		 {
		attach(cedula);
		attach(nombre);
		attach(primerApellido);
		attach(segundoApellido);
		attach(nacimiento);
		attach(BtnConsulta);
		attach(salida);
		nombre.deactivate();
		primerApellido.deactivate();
		segundoApellido.deactivate();
		nacimiento.deactivate();


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