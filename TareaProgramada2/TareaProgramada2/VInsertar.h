#pragma once
#include "GUI.h"
#include "Ventana.h"
using namespace Graph_lib;
struct VInsertar :
	public Window
{
	void insertar() {
		string valor = cedula.get_string() +";"+nombre.get_string()+ ";" + primerApellido.get_string() + ";" + segundoApellido.get_string() + ";" + nacimiento.get_string();
		cout << valor;
		string resultado = tabla.put(valor);
		if (resultado == "-1") {
			salida.put("Insercion fallida");
		}
		else {
			string posicion = split(resultado, ';').at(0);
			string colisiones = split(resultado, ';').at(1);
			salida.put("Insercion exitosa en posicion " + posicion + " con " + colisiones + " colisiones");
		}

	}
	void limpiar() {
		cedula.clean();
		nombre.clean();
		primerApellido.clean();
		segundoApellido.clean();
		nacimiento.clean();
	}
	void cancelar() {
		button_pushed = true;
		
	}

	static void consulta_cb(Address, Address addr) {
		static_cast<VInsertar*>(addr)->insertar();
	}
	static void limpiar_cb(Address, Address addr) {
		static_cast<VInsertar*>(addr)->limpiar();
	}
	static void cancelar_cb(Address, Address addr) {
		static_cast<VInsertar*>(addr)->cancelar();
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
	Button BtnInsertar;
	Button limpiarBtn;
	Button cancelarBtn;
	VInsertar(Point xy, int w, int h, const string& title, HashMap& tablaHash)
		: Window(xy, w, h, title),
		button_pushed(false),
		BtnInsertar(Point(100, 275), 70, 20, "Insertar", consulta_cb),
		limpiarBtn(Point(200, 275), 70, 20, "Limpiar", limpiar_cb),
		cancelarBtn(Point(300, 275), 70, 20, "Cancelar", cancelar_cb),
		cedula(Point(150, 100), 80, 20, "Cedula"),
		nombre(Point(150, 130), 100, 20, "Nombre"),
		primerApellido(Point(150, 160), 100, 20, "Primer Apellido"),
		segundoApellido(Point(150, 190), 100, 20, "Segundo Apellido"),
		nacimiento(Point(150, 220), 100, 20, "Fecha de nacimiento"),
		tabla(tablaHash),
		salida(Point(0, 378), 500, 20, "")
	{
		attach(cedula);
		attach(nombre);
		attach(primerApellido);
		attach(segundoApellido);
		attach(nacimiento);
		attach(BtnInsertar);
		attach(limpiarBtn);
		attach(cancelarBtn);
		attach(salida);
		


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