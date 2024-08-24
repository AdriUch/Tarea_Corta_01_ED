#pragma once
template <typename E> 

class Node{
public:
	E element;
	Node<E>* next;

	Node(E element, Node<E>* next) {
		this->element = element;
		this->next = next;

	}
};

