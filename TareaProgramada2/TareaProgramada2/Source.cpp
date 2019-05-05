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
	cout << "Insercion: " << resultado << endl;
	return true;
}
bool eliminar(string cedula) {
	if (!tablaHash->verificarCedula(cedula)) {
		return false;
	}
	string resultado = tablaHash->remove(cedula);
	cout << "Eliminacion: " << resultado << endl;
	return true;
}
bool modificar(string valor) {
	vector<string> vec = split(valor, ';');
	if (!tablaHash->verificarCedula(vec.at(0))) {
		return false;
	}
	string resultado = tablaHash->replace(valor);
	cout << "Modificacion: " << resultado << endl;
	return true;
}
bool consultar(string cedula) {
	string resultado = tablaHash->get(cedula);
	if (resultado == "false") {
		return false;
	}
	vector<string> vec = split(resultado, ';');
	string nombre = vec.at(1);
	string primerA = vec.at(2);
	string segundoA = vec.at(3);
	string fecha = vec.at(4);
	cout << "Consulta: " << resultado << endl;
	return true;
}
int main() {
	using namespace Graph_lib;
	abrir("data.txt");

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

	tablaHash->imprimir();
	return 0;
}