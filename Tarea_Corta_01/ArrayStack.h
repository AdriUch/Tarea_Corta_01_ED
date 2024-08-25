#pragma 
#define DEFAULT_MAX 5

#include <stdexcept>
#include <iostream>
#include "Stack.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class ArrayStack : public Stack <E>{
private:
	E* elements;
	int max;
	int top;

	void updateArray() {
		E* new_Elements = new E[max * 2];
		std::copy(elements, elements + top, new_Elements);
		delete[] elements;
		elements = new_Elements;
		max = max * 2;
	}

public:
	ArrayStack(int max = DEFAULT_MAX) {
		if (max < 1) {throw runtime_error("Invalid max size.");}
		elements = new E[max];
		this->max = max;
		top = 0;}

	~ArrayStack() {
		delete[] elements;}

	void push(E element) {
		if (top == max) {
			updateArray();
		}
		elements[top] = element;
		top++;}

	E pop() {
		if (top == 0) {
			throw runtime_error("Stack is empty");}
		top--;
		return elements[top];}

	E topValue() {
		if (top == 0) {
			throw runtime_error("Stack is empty");}
		return elements[top-1];}

	void clear() {
		top =  0;
 }

	bool isEmpty() {
		return top == 0;}

	int getSize() {
		return top;}

	void print() {
		cout << "[";
		for (int i = top - 1; i >= 0; i--) {
			cout << elements[i] << " ";}
		cout << "]" << endl;
	}
};
