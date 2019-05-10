#pragma once
#include "GUI.h"
#include "Ventana.h"
using namespace Graph_lib;
int validarFecha(int dd, int mm, int yy)
{

	if (yy < 0)
		return 1;

	if (mm < 0 || mm > 12)
		return 1;

	if (mm == 2)
	{
		if (yy % 4 == 0)
		{
			if (dd > 29 || dd < 0)
				return 1;
		}
		else
		{
			if (dd > 28 || dd < 0)
				return 1;
		}
	}
	else if (mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8 || mm == 10 || mm == 12)
	{
		if (dd > 31 || dd < 0)
			return 1;
	}
	else
	{
		if (dd > 30 || dd < 0)
			return 1;
	}

	return 0;
}
bool validarNumStoi(string tira) {
	for (int i = 0; i < tira.size(); i++) {
		if (tira.at(i) != '0' && tira.at(i) != '1' && tira.at(i) != '2' && tira.at(i) != '3' && tira.at(i) != '4' && tira.at(i) != '5' && tira.at(i) != '6' && tira.at(i) != '7' && tira.at(i) != '8' && tira.at(i) != '9') {
			return false;
		}
	}
	return true;
}
struct VOperacion :
	public Window
{
	void consulta() {
		
		if (tpconsulta == "Modificar") {
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
		else if (tpconsulta == "Consulta") {
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
			salida.put("Colisiones encontradas: " + vec.at(5));

		}
		else if (tpconsulta == "Insertar") {
			
		}
		else {
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
			consultado = true;
		}

	}
	void eliminar() {
		if (!consultado) {
			salida.put("Por favor consulte una cedula");
			return;
		}
		consultado = false;
		string colisiones = tabla.remove(cedula.get_string());
		limpiar();
		if (colisiones == "-1") {
			salida.put("Registro no existe");
			return;

		}
		salida.put("Registro eliminado con " + colisiones + " colisiones");
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
	void insertar() {
		if (cedula.get_string().size() != 9) {
			salida.put("Por favor ingrese una cedula valida (9 digitos)");
			return;
		}
		if (!validarNumStoi(cedula.get_string())) {
			salida.put("Por favor ingrese una cedula valida (Solo numeros)");
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
			salida.put("Por favor ingrese una fecha valida (dd/mm/yyyy)");
			return;
		}
		for (int i = 0; i < vec.size(); i++) {
			if (!validarNumStoi(vec.at(i))) {
				salida.put("Por favor ingrese una fecha valida (dd/mm/yyyy)");
				return;
			}
		}
		if (validarFecha(stoi(vec.at(0)), stoi(vec.at(1)), stoi(vec.at(2)))) {
			salida.put("Por favor ingrese una fecha valida");
			return;
		}
		string valor = cedula.get_string() + ";" + nombre.get_string() + ";" + primerApellido.get_string() + ";" + segundoApellido.get_string() + ";" + nacimiento.get_string();
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
		static_cast<VOperacion*>(addr)->consulta();
	}
	static void limpiar_cb(Address, Address addr) {
		static_cast<VOperacion*>(addr)->limpiar();
	}
	static void modificar_cb(Address, Address addr) {
		static_cast<VOperacion*>(addr)->modificar();
	}
	static void cancelar_cb(Address, Address addr) {
		static_cast<VOperacion*>(addr)->cancelar();
	}
	static void eliminar_cb(Address, Address addr) {
		static_cast<VOperacion*>(addr)->eliminar();
	}

	static void insertar_cb(Address, Address addr) {
		static_cast<VOperacion*>(addr)->insertar();
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
	bool consultado = false;
public:
	Button Btnconsultar;
	Button BtnInsertar;
	Button modificarBtn;
	Button limpiarBtn;
	Button eliminarBtn;
	Button cancelarBtn;
	string tpconsulta;
	VOperacion(Point xy, int w, int h, const string& title, HashMap& tablaHash)
		: Window(xy, w, h, title),
		button_pushed(false),
		Btnconsultar(Point(370, 100), 70, 20, "Consultar", consulta_cb),
		BtnInsertar(Point(170, 275), 70, 20, "Insertar", insertar_cb),
		modificarBtn(Point(170, 275), 70, 20, "Modificar", modificar_cb),
		limpiarBtn(Point(270, 275), 70, 20, "Limpiar", limpiar_cb),
		cancelarBtn(Point(370, 275), 70, 20, "Cancelar", cancelar_cb),
		cedula(Point(170, 100), 170, 20, "Cedula\t\t\t\t "),
		nombre(Point(170, 130), 170, 20, "Nombre\t\t\t\t"),
		primerApellido(Point(170, 160), 170, 20, "Primer Apellido\t\t     "),
		segundoApellido(Point(170, 190), 170, 20, "Segundo Apellido\t  "),
		nacimiento(Point(170, 220), 170, 20, "Fecha de nacimiento\t"),
		eliminarBtn(Point(170, 275), 70, 20, "Eliminar", eliminar_cb),
		tabla(tablaHash),
		salida(Point(0, 378), 500, 20, "")
	{
		
		if (title == "Modificar") {
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
			tpconsulta = title;
		}
		else if (title=="Consulta"){
			attach(cedula);
			attach(nombre);
			attach(primerApellido);
			attach(segundoApellido);
			attach(nacimiento);
			attach(Btnconsultar);
			attach(salida);
			attach(limpiarBtn);
			attach(cancelarBtn);
			nombre.deactivate();
			primerApellido.deactivate();
			segundoApellido.deactivate();
			nacimiento.deactivate();
			tpconsulta = title;
		
		}
		else if (title == "Insertar") {
			attach(cedula);
			attach(nombre);
			attach(primerApellido);
			attach(segundoApellido);
			attach(nacimiento);
			attach(BtnInsertar);
			attach(limpiarBtn);
			attach(cancelarBtn);
			attach(salida);
			tpconsulta = title;
		}
		else {

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
			tpconsulta = title;
		}




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
