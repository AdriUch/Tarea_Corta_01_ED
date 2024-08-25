/*Tarea Corta 1
Autores: Carmen Hidalgo Paz & Adrian Ugalde Chaves
Curso: Estructuras de Datos
*/

#include <iostream>
#include <string>
#include <cmath>
#include <limits>
#include "Stack.h"
#include "ArrayStack.h"
#include "Node.h"
#include "LinkedStack.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;
using std::invalid_argument;
using std::runtime_error;

// Función para obtener la precedencia del operador
int precedencia(char op) {
    switch (op) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}

// Función para procesar una operación
void procesarOperacion(Stack<char>* operadores, Stack<double>* numeros) {
    if (numeros->getSize() < 2 || operadores->isEmpty()) {
        throw runtime_error("No hay suficientes operandos u operadores.");
    }

    double B = numeros->pop();
    double A = numeros->pop();
    char op = operadores->pop();

    double resultado;
    switch (op) {
    case '+':
        resultado = A + B;
        break;
    case '-':
        resultado = A - B;
        break;
    case '*':
        resultado = A * B;
        break;
    case '/':
        if (B == 0) {
            throw runtime_error("División por cero.");
        }
        resultado = A / B;
        break;
    case '^':
        resultado = pow(A, B);
        break;
    default:
        throw invalid_argument("Operador no válido.");
    }

    numeros->push(resultado);
}
//Funcion que remueve los espacios del string
string removerEspacios(string operacion) {
    string resultado;

    for (int i = 0; i < operacion.length(); ++i) {
        char caracter = operacion[i];

        if (caracter != ' ') {
            resultado += caracter;
        }
    }
    return resultado;
}

// Función para evaluar una expresión infija
void dividirOperacion(Stack<char>* operadores, Stack<double>* numeros, const string& expresion) {
    double numero = 0;
    double decimal = 1;
    bool guardarNum = false;
    bool numDecimal = false;

    for (size_t i = 0; i < expresion.length(); i++) {
        if (isdigit(expresion[i])) {
            if (numDecimal) {
                decimal *= 0.1;
                numero += (expresion[i] - '0') * decimal;
            }
            else {
                numero = numero * 10 + (expresion[i] - '0');
            }
            guardarNum = true;
        }
        else if (expresion[i] == '.') {
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

            if (expresion[i] == '(') {
                operadores->push(expresion[i]);
            }
            else if (expresion[i] == ')') {
                while (!operadores->isEmpty() && operadores->topValue() != '(') {
                    procesarOperacion(operadores, numeros);
                }
                if (operadores->isEmpty()) {
                    throw runtime_error("Paréntesis desbalanceados.");
                }
                operadores->pop(); // Elimina '(' de la pila
            }
            else { // Es un operador
                while (!operadores->isEmpty() && operadores->topValue() != '(' &&
                    precedencia(operadores->topValue()) >= precedencia(expresion[i])) {
                    procesarOperacion(operadores, numeros);
                }
                operadores->push(expresion[i]);
            }
        }
    }

    if (guardarNum) {
        numeros->push(numero);
    }

    while (!operadores->isEmpty()) {
        if (operadores->topValue() == '(') {
            throw runtime_error("Paréntesis desbalanceados.");
        }
        procesarOperacion(operadores, numeros);
    }
}

int ingresarTipoStack() {
    int Opcion;

    cout << "Por favor seleccione el tipo de pila que desea usar:" << endl;
    cout << "Ingrese '1' para utilizar un ArrayStack" << endl;
    cout << "Ingrese '2' para utilizar un LinkedStack" << endl;
    cin >> Opcion;

    while (Opcion < 1 || Opcion > 2) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Valor introducido erroneo, intente otra vez" << endl;
        cout << "Ingrese '1' para utilizar un ArrayStack" << endl;
        cout << "Ingrese '2' para utilizar un LinkedStack" << endl;
        cin >> Opcion;
    }
    return Opcion;
}

int main() {
    string operacion;
    int opc = ingresarTipoStack();

    if (opc == 1) {
        Stack<char>* Operadores = new ArrayStack<char>();
        Stack<double>* Numeros = new ArrayStack<double>();
        cin.ignore();
        cout << "Ingrese una operación matemática: ";
        getline(cin, operacion);
        dividirOperacion(Operadores, Numeros, removerEspacios(operacion));
        cout << "Resultado: " << Numeros->topValue() << endl;
        delete Operadores;
        delete Numeros;
    }
    else if (opc == 2) {
        Stack<char>* Operadores = new LinkedStack<char>();
        Stack<double>* Numeros = new LinkedStack<double>();
        cin.ignore();
        cout << "Ingrese una operación matemática: ";
        getline(cin, operacion);
        dividirOperacion(Operadores, Numeros, removerEspacios(operacion));
        cout << "Resultado: " << Numeros->topValue() << endl;
        delete Operadores;
        delete Numeros;
    }

    return 0;
}
