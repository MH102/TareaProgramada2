#include "Ventana.h"

HashMap  * tablaHash = new HashMap();
/*
ofstream archivoO;
string path;

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
	for (int i = 0; i < tablaHash->getSize(); i++) {
		HashNode * a = tablaHash->getTabla()[i];
		while (a!=NULL) {
			archivoO << a->getValor() << endl;
			a = a->getNext();
		}
	}
}
void guardarTablaComo(string pathC) {
	archivoO.open(pathC);
	for (int i = 0; i < tablaHash->getSize(); i++) {
		HashNode * a = tablaHash->getTabla()[i];
		while (a) {
			archivoO << a->getValor() << endl;
			a = a->getNext();
		}
	}
}
bool insertar(string valor) {
	string resultado = tablaHash->put(valor);
	string mensaje;
	if (resultado == "-1") {
		mensaje = "Insercion fallida";
		return false;
	}
	string posicion = split(resultado, ';').at(0);
	string colisiones = split(resultado, ';').at(1);
	mensaje = "Insercion exitosa en posicion " + posicion + " con " + colisiones + "colisiones";
	cout << "Insercion: " << resultado << endl;
	return true;
}
bool eliminar(string cedula) {
	string colisiones = tablaHash->remove(cedula);
	string mensaje;
	if (colisiones == "-1") {
		mensaje = "Registro no existe";
		return false;
	}
	mensaje = "Registro eliminado con " + colisiones + " colisiones";
	cout << "Eliminacion: " << colisiones << endl;
	return true;
}
bool modificar(string valor) {
	vector<string> vec = split(valor, ';');
	string colisiones = tablaHash->replace(valor);
	string mensaje;
	if (colisiones == "-1") {
		mensaje = "Registro no existe";
		return false;
	}
	mensaje = "Actualizacion exitosa con " + colisiones + " colisiones";
	cout << "Modificacion: " << colisiones << endl;
	return true;
}
bool consultar(string cedula) {
	string colisiones = tablaHash->get(cedula);
	string mensaje;
	if (colisiones == "false") {
		mensaje = "Cedula no existe";
		return false;
	}
	vector<string> vec = split(colisiones, ';');
	string nombre = vec.at(1);
	string primerA = vec.at(2);
	string segundoA = vec.at(3);
	string fecha = vec.at(4);
	mensaje = "Colisiones encontradas: " + colisiones;
	cout << "Consulta: " << colisiones << endl;
	return true;
}*/
int main() {
	using namespace Graph_lib;
	/*abrir("data.txt");

	cout << path.size() << endl;

	insertar("333333;Ana Elena;Rivera;Solano;11/4/1999");
	insertar("444444;Ana Elena;Rivera;Solano;11/4/1999");
	modificar("111111;Ana Elena;Rivera;Solano;11/4/2010");
	insertar("211111;Ana Elena;Rivera;Solano;11/4/2010");
	insertar("311111;Ana Elena;Rivera;Solano;11/4/2010");
	eliminar("222222");
	guardarTablaComo("data2.txt");
	consultar("333333");
	tablaHash->imprimir();
	eliminar("211111");

	tablaHash->imprimir();*/
	Ventana win(Point(200, 200), 600, 500, "Simple Window");

	win.wait_for_button();
	return 0;
}