#pragma once
#include "GUI.h"
#include "tablahash.h"
#include "VConsulta.h"
#include"VInsertar.h"
#include "VEliminar.h"
#include "VModificar.h"
#include <fstream>
using namespace Graph_lib;
struct Ventana :
	public Window
{
	void abrir(bool test=false) {
		if (test) {
			abierto = true;
			set_label("Menu Principal: " + split(path, '\\').back());
			salida.put("Se ha abierto el archivo");
			return;
		}
		tablaHash.~HashMap();
		Fl_Native_File_Chooser fnfc;
		fnfc.title("Seleccione el archivo");
		fnfc.type(Fl_Native_File_Chooser::BROWSE_FILE);
		fnfc.filter("csv\t*.csv\n");
		fnfc.directory("/var/tmp");           // default directory to use
		// Show native chooser
		switch (fnfc.show()) {
		case -1: printf("ERROR: %s\n", fnfc.errmsg());    break;  // ERROR
		case  1: printf("CANCEL\n");                      break;  // CANCEL
		default: 
			path = fnfc.filename();
			if (split(path,'.').at(1) != "csv") {
				salida.put("Tipo de archivo invalido");
				return;
			}
			ifstream archivo;
			archivo.open(path);
			if (archivo.fail()) {
				return	;
			}
			string info;
			while (getline(archivo, info)) {
				tablaHash.put(info);
			}
			archivo.close();
			abierto = true;
			set_label("Menu Principal: " + split(path, '\\').back());
			salida.put("Se ha abierto el archivo");
			break;  // FILE CHOSEN
		}

	}
	void guardar() {
		if (!abierto) {
			guardarcm();
			return;
		}
		else {
			ofstream archivoO;
			archivoO.open(path);
			if (archivoO.fail()) {
				return;
			}
			for (int i = 0; i < tablaHash.getSize(); i++) {
				HashNode * a = tablaHash.getTabla()[i];
				while (a != NULL) {
					archivoO << a->getValor() << endl;
					a = a->getNext();
				}
			}
			archivoO.close();
			salida.put("Se ha guardado el archivo");
		}
	}
	void salir() {
		exit(0);
	}

	void consulta() {
		salida.put("");
		VConsulta vcon(Point(200, 200), 500, 500, "Consulta",tablaHash);
		vcon.wait_for_button();
	}
	void inserta() {
		salida.put("");
		VInsertar vinsert(Point(200, 200), 500, 400, "Insertar", tablaHash);
		vinsert.wait_for_button();
	}
	void elimina() {
		salida.put("");
		VEliminar velimina(Point(200, 200), 500, 400, "Eliminar", tablaHash);
		velimina.wait_for_button();
	}
	void modifica() {
		salida.put("");
		VModificar vModifica(Point(200, 200), 500, 400, "Modificar", tablaHash);
		vModifica.wait_for_button();
	}
	void guardarcm() {

		Fl_Native_File_Chooser fnfc;
		fnfc.title("Guardar archivo como");
		fnfc.type(Fl_Native_File_Chooser::BROWSE_SAVE_FILE);
		fnfc.filter("CSV\t*.csv\n");
		fnfc.directory("/var/tmp");           // default directory to use
		// Show native chooser
		switch (fnfc.show()) {
		case -1: printf("ERROR: %s\n", fnfc.errmsg());    break;  // ERROR
		case  1: break;  // CANCEL
		default: 
			ofstream archivoO;
			string paths = fnfc.filename();
			if (split(paths, '.').size() < 2) {
				archivoO.open(paths + ".csv");
				if (!abierto) {
					path = paths + ".csv";
					abrir(true);
				}
			}
			else {
				archivoO.open(paths);
				if (!abierto) {
					path = paths;
					abrir(true);
				}
			}
			if (archivoO.fail()) {
				return;
			}
			for (int i = 0; i < tablaHash.getSize(); i++) {
				HashNode * a = tablaHash.getTabla()[i];
				while (a != NULL) {
					archivoO << a->getValor() << endl;
					a = a->getNext();
				}
			}
			archivoO.close();
			salida.put("Se ha guardado el archivo");
			break;
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
	static void modificar_cb(Address, Address addr) {
		static_cast<Ventana*>(addr)->modifica();
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
	string path;
	bool abierto=false;
	Out_box salida;
	Ventana(Point xy, int w, int h, const string& title)
		: Window(xy, w, h, title),
		button_pushed(false),
		abrirBtn(Point(10, 50), 70, 20, "Abrir..", abrir_cb),
		guardarBtn(Point(10, 50), 70, 20, "Guardar", guardar_cb),
		guardarComoBtn(Point(10, 50), 100, 20, "Guardar como...", guardarcm_cb),
		salirBtn(Point(10, 50), 70, 20, "Salir", salir_cb),
		archivoM(Point(150, 200), 105, 20, Menu::vertical, "Archivo"),
		consultarBtn(Point(10, 50), 70, 20, "Consultar", consultar_cb),
		insertarBtn(Point(10, 50), 70, 20, "Insertar", insertar_cb),
		eliminarBtn(Point(10, 50), 70, 20, "Eliminar", eliminar_cb),
		modificarBtn(Point(10, 50), 70, 20, "Modificar", modificar_cb),
		personasM(Point(300, 200), 105, 20, Menu::vertical, "Personas"),
		salida(Point(150, 378), 250, 20, "")
	{
		archivoM.attach(abrirBtn);
		archivoM.attach(guardarBtn);
		archivoM.attach(guardarComoBtn);
		archivoM.attach(salirBtn);
		attach(archivoM);
		attach(salida);
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

