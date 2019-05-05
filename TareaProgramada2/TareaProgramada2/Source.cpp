#include "Ventana.h"
#include "tablahash.h"
#include <fstream>
ifstream archivo;
ofstream archivoO;
string path;
HashMap  * tablaHash = new HashMap();


bool abrir(string a) {
	path = a;
	archivo.open(path);
	if (archivo.fail()) {
		return false;
	}
	string info;
	while (getline(archivo, info)) {
		tablaHash->put(info);
	}
	archivo.close();
	return true;
}
void guardarTabla() {
	archivoO.open(path);
	for (int i = 0; i < tablaHash->getTabla().size(); i++) {
		archivoO << tablaHash->getTabla().at(i)->getValor() << endl;
	}
}
void guardarTablaComo(string pathC) {
	archivoO.open(pathC);
	for (int i = 0; i < tablaHash->getTabla().size(); i++) {
		archivoO << tablaHash->getTabla().at(i)->getValor() << endl;
	}
}
bool insertar(string valor) {
	if (tablaHash->verificarLlave(split(valor,';').at(0))) {
		return false;
	}
	tablaHash->put(valor);
	return true;
}
bool eliminar(string key) {
	if (!tablaHash->verificarLlave(key)) {
		return false;
	}
	tablaHash->remove(key);
	return true;
}
bool modificar(string valor) {
	vector<string> vec = split(valor, ';');
	if (!tablaHash->verificarLlave(vec.at(0))) {
		return false;
	}
	tablaHash->replace(valor);
	return true;
}
bool consultar(string key) {
	string consulta = tablaHash->get(key);
	if (consulta == "") {
		return false;
	}
	vector<string> vec = split(consulta, ';');
	string nombre = vec.at(1);
	string primerA = vec.at(2);
	string segundoA = vec.at(3);
	string fecha = vec.at(4);
	return true;
}
int main() {
	using namespace Graph_lib;
	abrir("data.txt");
	/*
	insertar("333333;Ana Elena;Rivera;Solano;11/4/1999");
	insertar("444444;Ana Elena;Rivera;Solano;11/4/1999");
	modificar("111111;Ana Elena;Rivera;Solano;11/4/2010");
	guardarTablaComo("data2.txt");
	*/
	tablaHash->imprimir();
	return 0;
}