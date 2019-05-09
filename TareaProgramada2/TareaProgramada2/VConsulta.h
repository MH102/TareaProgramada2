#pragma once
#include "GUI.h"
#include "Ventana.h"
using namespace Graph_lib;
struct VConsulta :
	public Window
{
	void consul() {
		nombre.clean();
		primerApellido.clean();
		segundoApellido.clean();
		nacimiento.clean();
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
	void cancelar() {
		cedula.clean();
		nombre.clean();
		primerApellido.clean();
		segundoApellido.clean();
		nacimiento.clean();
		button_pushed = true;
	}
	void limpiar() {
		cedula.clean();
		nombre.clean();
		primerApellido.clean();
		segundoApellido.clean();
		nacimiento.clean();
	}
	static void consulta_cb(Address, Address addr) {
		static_cast<VConsulta*>(addr)->consul();
	}
	static void limpiar_cb(Address, Address addr) {
		static_cast<VConsulta*>(addr)->limpiar();
	}
	static void cancelar_cb(Address, Address addr) {
		static_cast<VConsulta*>(addr)->cancelar();
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
	Button limpiarBtn;
	Button cancelarBtn;
	VConsulta(Point xy, int w, int h, const string& title,HashMap& tablaHash)
		: Window(xy, w, h, title),
		button_pushed(false),
		BtnConsulta(Point(240, 100), 70, 20, "Consultar", consulta_cb),
		limpiarBtn(Point(200, 275), 70, 20, "Limpiar", limpiar_cb),
		cancelarBtn(Point(300, 275), 70, 20, "Cancelar", cancelar_cb),
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
		attach(limpiarBtn);
		attach(cancelarBtn);
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