/*Tarea Corta 1
Autores:
Curso: Estructuras de Datos
*/

#include <iostream>
#include <string>
#include "Stack.h"
#include "ArrayStack.h"
#include "Node.h"
#include "LinkedStack.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

int ingresarTipoStack() {
	int Opcion;

	cout << "Porfavor seleccione el tipo de pila que desea usar:" << endl;
	cout << "Ingrese '1' para utilizar un ArrayStack" << endl;
	cout << "Ingrese '2' para utilizar un LinkedStack" << endl;
	cin >> Opcion;

	while (Opcion < 1 || Opcion > 2) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Valor introducido erroneo, intente otr vez" << endl;
		cout << "Ingrese '1' para utilizar un ArrayStack" << endl;
		cout << "Ingrese '2' para utilizar un LinkedStack" << endl;
		cin >> Opcion;
	}
	return Opcion;
}

void dividirOperacion(Stack<char>* operadores, Stack<int>* numeros, string Operacion) {
	for (int i = 0; i < Operacion.length(); i++) {
	
		if (isdigit(Operacion[i])) {
			numeros->push(Operacion[i]-'0');
		}
		else if (!isdigit(Operacion[i])) {
			operadores->push(Operacion[i]);
		}
		
		

		}
	}


int main() {
	string operacion;
	int opc = ingresarTipoStack();

	if (opc == 1) {
		Stack<char>* Operadores = new ArrayStack<char>(5);
		Stack<int>* Numeros = new ArrayStack<int>(5);
		cin.ignore();
		cout << "Ingrese una operación matematica: ";
		getline(cin, operacion);
		dividirOperacion(Operadores, Numeros, operacion);
		Operadores->print();
		Numeros->print();
		delete Operadores;
		delete Numeros;

	}
	else if (opc == 2) {
		Stack<char>* Operadores = new LinkedStack<char>();
		Stack<int>* Numeros = new LinkedStack<int>();
		cin.ignore();
		cout << "Ingrese una operación matematica: ";
		getline(cin, operacion);
		dividirOperacion(Operadores, Numeros, operacion);
		Operadores->print();
		Numeros->print();
		delete Operadores;
		delete Numeros;

	}

}
