#pragma once
#include "GUI.h"
#include "tablahash.h"
#include "VConsulta.h"
#include"VInsertar.h"
#include "VEliminar.h"
#include <fstream>
using namespace Graph_lib;
struct Ventana :
	public Window
{
	void abrir() {

		Fl_Native_File_Chooser fnfc;
		fnfc.title("Seleccione el archivo");
		fnfc.type(Fl_Native_File_Chooser::BROWSE_FILE);
		fnfc.filter("Text\t*.txt\n"
			"C Files\t*.{cxx,h,c}");
		fnfc.directory("/var/tmp");           // default directory to use
		// Show native chooser
		switch (fnfc.show()) {
		case -1: printf("ERROR: %s\n", fnfc.errmsg());    break;  // ERROR
		case  1: printf("CANCEL\n");                      break;  // CANCEL
		default: printf("PICKED: %s\n", fnfc.filename()); break;  // FILE CHOSEN
		}
		ifstream archivo;
		archivo.open(fnfc.filename());
		if (archivo.fail()) {
			cout << "Error";
		}
		string info;
		while (getline(archivo, info)) {
			tablaHash.put(info);
		}
		archivo.close();
		cout << "exito";

	}
	void guardar() {

	}
	void salir() {
		exit(0);
	}

	void consulta() {

		VConsulta vcon(Point(200, 200), 500, 500, "Consulta",tablaHash);
		vcon.wait_for_button();
	}
	void inserta() {

		VInsertar vinsert(Point(200, 200), 500, 400, "Consulta", tablaHash);
		vinsert.wait_for_button();
	}
	void elimina() {
		VEliminar velimina(Point(200, 200), 500, 400, "Eliminar", tablaHash);
		velimina.wait_for_button();
	}
	void guardarcm() {

		Fl_Native_File_Chooser fnfc;
		fnfc.title("Guardar archivo como");
		fnfc.type(Fl_Native_File_Chooser::BROWSE_SAVE_FILE);
		fnfc.filter("Text\t*.txt\n"
			"C Files\t*.{cxx,h,c}");
		fnfc.directory("/var/tmp");           // default directory to use
		// Show native chooser
		switch (fnfc.show()) {
		case -1: printf("ERROR: %s\n", fnfc.errmsg());    break;  // ERROR
		case  1: printf("CANCEL\n");                      break;  // CANCEL
		default: printf("PICKED: %s\n", fnfc.filename()); break;  // FILE CHOSEN
		}
	}
	static void abrir_cb(Address, Address addr) {
		static_cast<Ventana*>(addr)->abrir();
	}
	static void guardar_cb(Address, Address addr) {
		static_cast<Ventana*>(addr)->guardar();
	}
	static void guardarcm_cb(Address, Address addr) {
		static_cast<Ventana*>(addr)->guardarcm();
	}
	static void salir_cb(Address, Address addr) {
		static_cast<Ventana*>(addr)->salir();
	}
	static void consultar_cb(Address, Address addr) {
		static_cast<Ventana*>(addr)->consulta();
	}
	static void insertar_cb(Address, Address addr) {
		static_cast<Ventana*>(addr)->inserta();
	}
	static void eliminar_cb(Address, Address addr) {
		static_cast<Ventana*>(addr)->elimina();
	}
	bool button_pushed;
	HashMap tablaHash;
public:
	Button abrirBtn;
	Button guardarBtn;
	Button guardarComoBtn;
	Button salirBtn;
	Button consultarBtn;
	Button insertarBtn;
	Button eliminarBtn;
	Button modificarBtn;
	Menu archivoM;
	Menu personasM;
	Ventana(Point xy, int w, int h, const string& title)
		: Window(xy, w, h, title),
		button_pushed(false),
		abrirBtn(Point(10, 50), 70, 20, "Abrir..", abrir_cb),
		guardarBtn(Point(10, 50), 70, 20, "Guardar",guardar_cb),
		guardarComoBtn(Point(10, 50), 100, 20, "Guardar como...", guardarcm_cb),
		salirBtn(Point(10, 50), 70, 20, "Salir", salir_cb),
		archivoM(Point(150, 200), 105, 20, Menu::vertical, "Archivo"),
		consultarBtn(Point(10,50),70,20,"Consultar",consultar_cb),
		insertarBtn(Point(10, 50), 70, 20, "Insertar", insertar_cb),
		eliminarBtn(Point(10, 50), 70, 20, "Eliminar", eliminar_cb),
		modificarBtn(Point(10, 50), 70, 20, "Modificar", salir_cb),
		personasM(Point(300, 200), 105, 20, Menu::vertical, "Personas")
		
		{
		archivoM.attach(abrirBtn);
		archivoM.attach(guardarBtn);
		archivoM.attach(guardarComoBtn);
		archivoM.attach(salirBtn);
		attach(archivoM);
		personasM.attach(consultarBtn);
		personasM.attach(insertarBtn);
		personasM.attach(eliminarBtn);
		personasM.attach(modificarBtn);
		attach(personasM);
		
		
		
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

