#pragma once
#include "GUI.h"
#include "Ventana.h"
using namespace Graph_lib;
struct VModificar :
	public Window
{
	void consulta() {
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
		cedula.deactivate();
		nombre.activate();
		primerApellido.activate();
		segundoApellido.activate();
		nacimiento.activate();
		activeCed = false;

	}
	void modificar() {
		if (activeCed) {
			salida.put("Por favor consulte una cedula");
			return;
		}
		if (nombre.get_string().size() == 0 || nombre.get_string().size() > 25) {
			salida.put("Por favor ingrese el nombre");
			return;
		}
		if (primerApellido.get_string().size() == 0 || primerApellido.get_string().size() > 25) {
			salida.put("Por favor ingrese el primer apellido");
			return;
		}
		if (segundoApellido.get_string().size() == 0 || segundoApellido.get_string().size() > 25) {
			salida.put("Por favor ingrese el segundo apellido");
			return;
		}
		if (nacimiento.get_string().size() == 0) {
			salida.put("Por favor ingrese la fecha de nacimiento");
			return;
		}
		if (nacimiento.get_string().size() != 10) {
			salida.put("Por favor ingrese una fecha valida (dd/mm/yyyy)");
			return;
		}
		vector<string> vec = split(nacimiento.get_string(), '/');
		if (vec.size() != 3) {
			salida.put("Por favor ingrese una fecha valida");
			return;
		}
		for (int i = 0;i < vec.size(); i++) {
			if (!validarNumStoi(vec.at(i))) {
				salida.put("Por favor ingrese una fecha valida");
				return;
			}
		}
		if (validarFecha(stoi(vec.at(0)), stoi(vec.at(1)), stoi(vec.at(2)))) {
			salida.put("Por favor ingrese una fecha valida");
			return;
		}
		string colisiones = tabla.replace(cedula.get_string() + ";" + nombre.get_string() + ";" + primerApellido.get_string() + ";" + segundoApellido.get_string() + ";" + nacimiento.get_string());
		salida.put("Actualizacion exitosa con " + colisiones + " colisiones");

	}
	void limpiar() {
		cedula.clean();
		nombre.clean();
		primerApellido.clean();
		segundoApellido.clean();
		nacimiento.clean();
		nombre.deactivate();
		primerApellido.deactivate();
		segundoApellido.deactivate();
		nacimiento.deactivate();
		cedula.activate();
		activeCed = true;
	}
	void cancelar() {
		button_pushed = true;

	}

	static void consulta_cb(Address, Address addr) {
		static_cast<VModificar*>(addr)->consulta();
	}
	static void limpiar_cb(Address, Address addr) {
		static_cast<VModificar*>(addr)->limpiar();
	}
	static void modificar_cb(Address, Address addr) {
		static_cast<VModificar*>(addr)->modificar();
	}
	static void cancelar_cb(Address, Address addr) {
		static_cast<VModificar*>(addr)->cancelar();
	}
	bool button_pushed;
	In_box cedula;
	In_box nombre;
	In_box primerApellido;
	In_box segundoApellido;
	In_box nacimiento;
	Out_box salida;
	bool activeCed=true;
	HashMap& tabla;
public:
	Button Btnconsultar;
	Button modificarBtn;
	Button limpiarBtn;
	Button cancelarBtn;
	VModificar(Point xy, int w, int h, const string& title, HashMap& tablaHash)
		: Window(xy, w, h, title),
		button_pushed(false),
		Btnconsultar(Point(370, 100), 70, 20, "Consultar", consulta_cb),
		modificarBtn(Point(170, 275), 70, 20, "Modificar", modificar_cb),
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
		attach(modificarBtn);
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
