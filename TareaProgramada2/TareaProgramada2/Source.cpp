#include "Ventana.h"
#include "tablahash.h"
#include <fstream>
ifstream archivo;
ofstream archivoO;
string path="data.txt";
HashMap  * tablaHash = new HashMap();

bool insertar(string valor) {
	if (tablaHash->verificarLlave(split(valor,';').at(0))) {
		return false;
	}
	archivoO.open(path, ios_base::app);
	archivoO << valor << endl;
	tablaHash->put(valor);
	archivoO.close();
	return true;
}
bool eliminar(string key) {
	if (!tablaHash->verificarLlave(key)) {
		return false;
	}
	archivo.open(path);
	archivoO.open("temp.txt");
	string linea;
	while (getline(archivo, linea)) {
		if (split(linea, ';').at(0) != key) {
			archivoO << linea << endl;
		}
	}
	tablaHash->remove(key);
	archivo.close();
	archivoO.close();
	remove(path.c_str());
	rename("temp.txt", path.c_str());
	return true;
}
bool modificar(string valor) {
	vector<string> vec = split(valor, ';');
	if (!tablaHash->verificarLlave(vec.at(0))) {
		return false;
	}
	tablaHash->replace(valor);
	archivo.open(path);
	archivoO.open("temp.txt");
	string linea;
	while (getline(archivo, linea)) {
		if (split(linea,';').at(0) != split(valor,';').at(0)) {
			archivoO << linea << endl;
		}
		else {
			archivoO << valor << endl;
		}
	}
	archivo.close();
	archivoO.close();
	remove(path.c_str());
	rename("temp.txt", path.c_str());
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
	archivo.open("data.txt");
	if (archivo.fail()) {
		return -1;
	}
	string info;
	while (getline(archivo, info)) {
		tablaHash->put(info);
	}
	archivo.close();
	eliminar("333333");
	tablaHash->imprimir();
	return 0;
}