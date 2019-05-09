#pragma once
#include "GUI.h"
#include "Ventana.h"
using namespace Graph_lib;
bool validarNumStoi(string tira) {
	for (int i = 0; i < tira.size(); i++) {
		if (tira.at(i) != '0' && tira.at(i) != '1' && tira.at(i) != '2' && tira.at(i) != '3' && tira.at(i) != '4' && tira.at(i) != '5' && tira.at(i) != '6' && tira.at(i) != '7' && tira.at(i) != '8' && tira.at(i) != '9') {
			return false;
		}
	}
	return true;
}
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
			salida.put("Por favor ingrese una cedula valida (9 digitos)");
			return;
		}
		if (!validarNumStoi(cedu)) {
			salida.put("Por favor ingrese una cedula valida (Solo numeros)");
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
		BtnConsulta(Point(370, 100), 70, 20, "Consultar", consulta_cb),
		limpiarBtn(Point(270, 275), 70, 20, "Limpiar", limpiar_cb),
		cancelarBtn(Point(370, 275), 70, 20, "Cancelar", cancelar_cb),
		cedula(Point(170, 100), 170, 20, "Cedula\t\t\t\t "),
		nombre(Point(170, 130), 170, 20, "Nombre\t\t\t\t"),
		primerApellido(Point(170, 160), 170, 20, "Primer Apellido\t\t     "),
		segundoApellido(Point(170, 190), 170, 20, "Segundo Apellido\t  "),
		nacimiento(Point(170, 220), 170, 20, "Fecha de nacimiento\t"),
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