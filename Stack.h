#ifndef STACK_H
#define STACK_H
#include <iostream>
#include "SLinkedList.h"
#include "HeaderNode.h"
using namespace std;

template <class T>
class Stack : protected SLinkedList<T> {
public:

	void push(T data);
	void pop(T& data);
	void pop();
	void top(T& data);
	bool isEmpty();
	void emptyStack();
};

template <class T>
void Stack<T>::push(T data) {
	this->addFront(data);
}

template <class T>
void Stack<T>::pop(T& data) {
	data = this->list->front->data;
	this->removeFront();
}

template <class T>
void Stack<T>::pop() {
	this->removeFront();
}

template <class T>
void Stack<T>::top(T& data) {
	data = this->list->front->data;
}

template <class T>
bool Stack<T>::isEmpty() {
	return (this->list->count == 0);
}

template<class T>
void Stack<T>::emptyStack() {
	this->emptyList();
}
#endif STACK_H
