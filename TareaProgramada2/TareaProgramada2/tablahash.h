#include <string>
#include <vector>
#include <iostream>
using namespace std;
vector<string> split(string cadena, char divisor) {
	vector<string> vec;
	string palabra;
	for (int i = 0; i < cadena.size(); ++i) {
		if (cadena[i] == divisor) {
			vec.push_back(palabra);
			palabra = "";
		}
		else {
			palabra += cadena[i];
		}
	}
	vec.push_back(palabra);
	return vec;
}
class HashNode {
public:
	HashNode(int key,string cedula, string nombre, string primerA, string segundoA,string fecha) :
		key(key), cedula(cedula), nombre(nombre), primerA(primerA),segundoA(segundoA),fecha(fecha),next(NULL){
	}

	int getKey() {
		return key;
	}
	string getCedula() {
		return cedula;
	}
	string getNombre() {
		return nombre;
	}
	string getPrimerA() {
		return primerA;
	}
	string getSegundoA() {
		return segundoA;
	}
	string getFecha() {
		return fecha;
	}
	string getValor() {
		string text = cedula + ";" + nombre + ";" + primerA + ";" + segundoA + ";" + fecha;
		return text;
	}
	void replaceVal(HashNode rep) {
		cedula = rep.cedula;
		nombre = rep.nombre;
		primerA = rep.primerA;
		segundoA = rep.segundoA;
		fecha = rep.fecha;
	}
	HashNode * getNext() {
		return next;
	}
	void setNext(HashNode * nuevo) {
		next = nuevo;
	}
	void imprimir() {
		cout << "Cedula: " << cedula << endl;
		cout << "Nombre: " << nombre << endl;
		cout << "Primer Apellido: " << primerA << endl;
		cout << "Segundo Apellido: " << segundoA << endl;
		cout << "Fecha: " << fecha << endl;
	}


private:
	// key-value pair
	int key;
	string cedula;
	string nombre;
	string primerA;
	string segundoA;
	string fecha;
	HashNode * next;
	friend class HashMap;
};

class HashMap{
public:
	HashMap() {
		table = new HashNode*[size];
		for (int i = 0; i < size;i++) {
			table[i] = 0;
		}
	}

	~HashMap() {
		// destroy all buckets one by one
		for (int i = 0; i < size; i++) {
			HashNode * a = table[i];
			while (a) {
				table[i] = a->next;
				delete(a);
				a = table[i];
			}
		}
	}
	bool verificarCedula(string cedula) {
		int key = hashFunc(cedula);
		HashNode * a = table[key];
		while (a && a->cedula != cedula) {
			a = a->next;
		}
		if (a == NULL) {
			return false;
		}
		return true;
	}
	string get(string cedula) {
		int key = hashFunc(cedula);
		HashNode * a = table[key];
		int colisiones = 0;
		while (cedula != a->cedula && a) {
			a = a->next;
			colisiones++;
		}
		if (!a) {
			return "false";
		}
		return a->getValor()+";"+to_string(colisiones);
	}
	string put(string valor) {
		vector<string> vec = split(valor, ';');
		if (verificarCedula(vec.at(0))) {
			return "-1";
		}
		int key = hashFunc(vec.at(0));
		HashNode * nuevo = new HashNode(key,vec.at(0), vec.at(1), vec.at(2), vec.at(3), vec.at(4));
		if (table[key] == NULL) {
			table[key] = nuevo;
			return to_string(key) + ";" + "0";
		}
		else {
			HashNode * a = table[key];
			int colisiones = 1;
			while (a->next) {
				a = a->next;
				colisiones++;
			}
			a->setNext(nuevo);
			cout << colisiones << endl;
			return to_string(key)+";"+to_string(colisiones);
		}
	}
	string replace(string valor) {
		vector<string> vec = split(valor, ';');
		if (verificarCedula(vec.at(0))) {
			int key = hashFunc(vec.at(0));
			int colisiones = 0;
			HashNode * a = table[key];
			HashNode nuevo(key,vec.at(0), vec.at(1), vec.at(2), vec.at(3), vec.at(4));
			while (a->cedula != vec.at(0)) {
				a = a->next;
			}
			a->replaceVal(nuevo);
			return to_string(colisiones);
		}
		return "-1";
	}
	string remove(string cedula) {
		if (verificarCedula(cedula)) {
			int key = hashFunc(cedula);
			HashNode * a = table[key];
			int colisiones = 0;
			HashNode * b = NULL;
			while (a) {
				if (a->cedula != cedula) {
					b = a;
					a = a->next;
					colisiones++;
				}
				else {
					if (b) {
						b->next = a->next;
						delete(a);
					}
					else {
						if (a->next) {
							table[key] = a->next;
						}
						else {
							table[key] = 0;
						}
						delete(a);
						
					}
					return to_string(colisiones);
				}
			}
		}
		return "-1";
	}
	void imprimir() {
		for (int i = 0; i < size; i++) {
			if (table[i]) {
				HashNode * a = table[i];
				if (a!=NULL) {
					cout << "----------------Key " << a->key << "----------------" << endl;
				}
				while (a!=NULL) {
					cout << "<< Info HashNode >>" << endl;
					a->imprimir();
					a = a->next;
					cout << "<< End HashNode >>" << endl << endl;
				}
			}
		}
	}
	HashNode** getTabla() {
		return table;
	}
	int getSize() {
		return size;
	}
	int hashFunc(string cedula) {
		int key = stoi(cedula) % 10;
		return key;
	}
private:
	int size = 10;
	HashNode** table;
};