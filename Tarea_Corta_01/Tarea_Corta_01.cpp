/*Tarea Corta 1
Autores: Carmen Hidalgo Paz &
Curso: Estructuras de Datos
*/

#include <iostream>
#include <string>
#include <stdio.h>
#include "Stack.h"
#include "ArrayStack.h"
#include "Node.h"
#include "LinkedStack.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;

int ingresarTipoStack() {
	int Opcion;

	cout << "Por favor seleccione el tipo de pila que desea usar:" << endl;
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

void dividirOperacion(Stack<char>* operadores, Stack<double>* numeros, string Operacion) {
		double numero = 0;
	double decimal = 1;
	bool guardarNum = false;
	bool numDecimal = false;
	const char caracter[] = { '+', '-', '*', '/', '^', '(', ')' }; // Crea un arreglo local con los operandos validos
	const int numCaracter = sizeof(caracter) / sizeof(caracter[0]); // Guarda el tamaño fijo del arreglo
	for (int i = 0; i < Operacion.length(); i++) {

		if (isdigit(Operacion[i])) {
			if (numDecimal) {
				decimal = decimal * 0.1;
				numero = numero + (Operacion[i] - '0') * decimal;
			}
			else {
				numero = numero * 10 + (Operacion[i] - '0');
			}
			guardarNum = true;
		}
		else if (Operacion[i] == '.') {
			numDecimal = true;
		}
		else {
			if (guardarNum) {
				numeros->push(numero);
				numero = 0;
				decimal = 1;
				guardarNum = false;
				numDecimal = false;
			}

			bool opValido = false;
			for (int j = 0; j < numCaracter; j++) {
				if (Operacion[i] == caracter[j]) {
					opValido = true;
					operadores->push(Operacion[i]);
					
					break; // Sale del bucle después de encontrar un operador válido
				}
			}
		}
	}

	if (guardarNum) {
		numeros->push(numero);
	}
}


int main() {
	string operacion;
	int opc = ingresarTipoStack();

	if (opc == 1) {
		Stack<char>* Operadores = new ArrayStack<char>();
		Stack<double>* Numeros = new ArrayStack<double>();
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
		Stack<double>* Numeros = new LinkedStack<double>();
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
