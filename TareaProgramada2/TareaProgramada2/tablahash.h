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
	HashNode(string key, string nombre, string primerA, string segundoA,string fecha) :
		key(key), nombre(nombre), primerA(primerA),segundoA(segundoA),fecha(fecha){
	}

	string getKey() {
		return key;
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
	void imprimir() {
		cout << "Cedula: " << key << endl;
		cout << "Nombre: " << nombre << endl;
		cout << "Primer Apellido: " << primerA << endl;
		cout << "Segundo Apellido: " << segundoA << endl;
		cout << "Fecha: " << fecha << endl;
	}


private:
	// key-value pair
	string key;
	string nombre;
	string primerA;
	string segundoA;
	string fecha;
};

class HashMap{
public:
	HashMap() {
	}

	~HashMap() {
		// destroy all buckets one by one
		for (int i = 0; i < table.size(); i++) {
			delete(table.at(i));
		}
	}
	bool verificarLlave(string key) {
		for (int i = 0; i < table.size(); i++) {
			if (table.at(i)->getKey() == key) {
				return true;
			}
		}
		return false;
	}
	string get(string key) {
		string final = "";
		for (int i = 0; i < table.size();i++) {
			if (table.at(i)->getKey() == key) {
				final += table.at(i)->getKey() + ";";
				vector<string> vec = split(table.at(i)->getNombre(), ' ');
				for (int j = 0; j < vec.size(); i++) {
					final += vec.at(j) + ";";
				}
				final += table.at(i)->getPrimerA() +";";
				final += table.at(i)->getSegundoA() + ";";
				final += table.at(i)->getFecha();
				break;
			}
		}
		return final;
	}
	bool put(string valor) {
		vector<string> vec = split(valor, ';');
		if (verificarLlave(vec.at(0))) {
			return false;
		}
		HashNode * nuevo = new HashNode(vec.at(0), vec.at(1), vec.at(2), vec.at(3), vec.at(4));
		table.push_back(nuevo);
		return true;
	}
	bool replace(string valor) {
		vector<string> vec = split(valor, ';');
		for (int i = 0; i < table.size(); i++) {
			if (table.at(i)->getKey() == vec.at(0)) {
				HashNode * nuevo = new HashNode(vec.at(0), vec.at(1), vec.at(2), vec.at(3), vec.at(4));
				delete(table.at(i));
				table.at(i) = nuevo;
				return true;
			}
		}
		return false;
	}
	bool remove(string key) {
		for (int i = 0; i < table.size(); i++) {
			if (table.at(i)->getKey() == key) {
				table.erase(table.begin() + i);
				return true;
			}
		}
		return false;
	}
	void imprimir() {
		for (int i = 0; i < table.size(); i++) {
			cout << "----------------Hash Node " << i << "----------------" << endl;
			table.at(i)->imprimir();
		}
	}
private:
	vector<HashNode*> table;
};