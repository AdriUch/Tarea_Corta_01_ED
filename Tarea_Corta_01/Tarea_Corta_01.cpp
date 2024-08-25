/*Tarea Corta 1
Autores: Carmen Hidalgo Paz & Adrian Ugalde Chaves
Curso: Estructuras de Datos
Asignación: Tarea Corta 1 - Pilas
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
using std::exception;


bool error = false;     // Muestra si se encontró un error

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

    try {
        // Si solo queda un número en el stack (la respuesta)
        // Y todavía hay operadores, se detecta el error
        if (numeros->getSize() == 1 && operadores->getSize() > 0) {
            throw runtime_error("No hay suficientes operandos.");
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
                throw runtime_error("Division por cero.");
            }
            resultado = A / B;
            break;
        case '^':
            resultado = pow(A, B);
            break;
        default:
            throw invalid_argument("Operador no valido.");
        }

        numeros->push(resultado);
    }
    catch (const exception& errorDetectado) {
        operadores->clear();    // Se limpia la pila de operadores
        error = true;           // Se detecta que hay un error
        std::cerr << "Error: " << errorDetectado.what() << std::endl;
    }
}

//Funcion que remueve los espacios del string
string removerEspacios(string operacion) {
    string resultado;

    for (int i = 0; i < operacion.length(); ++i) {
        char caracter = operacion[i];

        if (caracter != ' ') {  // Se vuelve a escribir todo lo que no sea un espacio
            resultado = resultado + caracter;
        }
    }
    return resultado;
}

// Función para evaluar una expresión infija
void dividirOperacion(Stack<char>* operadores, Stack<double>* numeros, const string& expresion) {
    double numero = 0;          // El número resultante
    double decimal = 1;         // La parte decimal
    bool guardarNum = false;    // Se guarda el número en la pila
    bool numDecimal = false;    // Es un número con decimales

    for (size_t i = 0; i < expresion.length(); i++) {
        if (isdigit(expresion[i])) {
            if (numDecimal) {   // Si hay decimales
                decimal *= 0.1;
                numero += (expresion[i] - '0') * decimal;
            }
            else {              // La parte entera
                numero = numero * 10 + (expresion[i] - '0');
            }
            guardarNum = true;
        }
        else if (expresion[i] == '.') {
            numDecimal = true;
        }
        else {
            if (guardarNum) {   // Se guarda en la pila y se reinician los valores
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
                
                try {
                    if (operadores->isEmpty()) {
                        throw runtime_error("Parentesis desbalanceados.");
                    }
                    operadores->pop(); // Elimina '(' de la pila
                }
                catch (const runtime_error& errorDetectado) {
                    error = true;      // Se detecta un error
                    std::cerr << "Error: " << errorDetectado.what() << std::endl;
                }
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
        numeros->push(numero);         // Se guarda el número en la pila
    }

    try {
        while (!operadores->isEmpty()) {
            if (operadores->topValue() == '(') {
                throw runtime_error("Parentesis desbalanceados.");
            }
            procesarOperacion(operadores, numeros);
        }
    }
    catch (const runtime_error& errorDetectado) {
        operadores->clear();           // Se limpia el stack
        error = true;                  // Se detecta un error
        std::cerr << "Error: " << errorDetectado.what() << std::endl;
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
        // Se crean las pilas
        Stack<char>* Operadores = new ArrayStack<char>();
        Stack<double>* Numeros = new ArrayStack<double>();
        cin.ignore();
        // Se le pide al usuario que ingrese una operación
        cout << "Ingrese una operacion matematica: ";
        getline(cin, operacion);
        // Se divide la operación ingresado en una pila de números y
        // una pila de operadores
        dividirOperacion(Operadores, Numeros, removerEspacios(operacion));
        // Si no se encontró ningún error se imprime el resultado
        if (error == false) {
            cout << "Resultado: " << Numeros->topValue() << endl;
        }
        delete Operadores;
        delete Numeros;
    }
    else if (opc == 2) {
        // Se crean las pilas
        Stack<char>* Operadores = new LinkedStack<char>();
        Stack<double>* Numeros = new LinkedStack<double>();
        cin.ignore();
        // Se le pide al usuario que ingrese una operación
        cout << "Ingrese una operacion matematica: ";
        getline(cin, operacion);
        // Se divide la operación ingresado en una pila de números y
        // una pila de operadores
        dividirOperacion(Operadores, Numeros, removerEspacios(operacion));
        // Si no se encontró ningún error se imprime el resultado
        if (error == false) {
            cout << "Resultado: " << Numeros->topValue() << endl;
        }
        delete Operadores;
        delete Numeros;
    }

    return 0;
}
