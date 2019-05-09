#pragma once
#include "GUI.h"
#include "Ventana.h"
using namespace Graph_lib;
struct VEliminar :
	public Window
{
	void consulta() {
		nombre.clean();
		primerApellido.clean();
		segundoApellido.clean();
		nacimiento.clean();
		string cedu = cedula.get_string();
		
		if (cedu.size() != 9) {
			salida.put("Por favor ingrese una cedula valida (9 digitos)");
			return;
		}
		if (!validarNumStoi(cedu)) {
			salida.put("Por favor ingrese una cedula valida (Solo numeros)");
			return;
		}
		if (!tabla.verificarCedula(cedu)) {
			salida.put("El registro no existe");
			return;
		}
		string colisiones = tabla.get(cedu);
		vector<string> vec = split(colisiones, ';');
		cedula.put(vec.at(0));
		nombre.put(vec.at(1));
		primerApellido.put(vec.at(2));
		segundoApellido.put(vec.at(3));
		nacimiento.put(vec.at(4));
		salida.put("Colisiones encontradas: " + vec.at(5));
		
	}
	void eliminar() {
		string colisiones = tabla.remove(cedula.get_string());
		if (colisiones == "-1") {
			salida.put( "Registro no existe");
			return;
			
		}
		salida.put("Registro eliminado con " + colisiones + " colisiones");
		
	}
	void cancelar() {
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
		static_cast<VEliminar*>(addr)->consulta();
	}
	static void eliminar_cb(Address, Address addr) {
		static_cast<VEliminar*>(addr)->eliminar();
	}
	static void cancelar_cb(Address, Address addr) {
		static_cast<VEliminar*>(addr)->cancelar();
	}
	static void limpiar_cb(Address, Address addr) {
		static_cast<VEliminar*>(addr)->limpiar();
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
	Button Btnconsultar;
	Button eliminarBtn;
	Button limpiarBtn;
	Button cancelarBtn;
	VEliminar(Point xy, int w, int h, const string& title, HashMap& tablaHash)
		: Window(xy, w, h, title),
		button_pushed(false),
		Btnconsultar(Point(370, 100), 70, 20, "Consultar", consulta_cb),
		eliminarBtn(Point(170, 275), 70, 20, "Eliminar", eliminar_cb),
		limpiarBtn(Point(270, 275), 70, 20, "Limpiar", limpiar_cb),
		cancelarBtn(Point(370, 275), 70, 20, "Cancelar", cancelar_cb),
		cedula(Point(170, 100), 170, 20, "Cedula\t\t\t\t "),
		nombre(Point(170, 130), 170, 20, "Nombre\t\t\t\t"),
		primerApellido(Point(170, 160), 170, 20, "Primer Apellido\t\t     "),
		segundoApellido(Point(170, 190), 170, 20, "Segundo Apellido\t  "),
		nacimiento(Point(170, 220), 170, 20, "Fecha de nacimiento\t"),
		tabla(tablaHash),
		salida(Point(0, 378), 500, 20, "")
	{
		attach(cedula);
		attach(nombre);
		attach(primerApellido);
		attach(segundoApellido);
		attach(nacimiento);
		attach(Btnconsultar);
		attach(eliminarBtn);
		attach(limpiarBtn);
		attach(cancelarBtn);
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