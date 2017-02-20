#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"
#include "HeaderNode.h"
using namespace std;


template <class T>
class SLinkedList {
protected:
	HeaderNode<T>* list;

public:
	SLinkedList();

	void addFront(T data);
	void addBack(T data);

	void removeFront();
	void removeBack();

	void addInOrder(T data);
	void removeNode(T data);

	bool search(T data);

	int returnCount();
	void emptyList();

	~SLinkedList();
};

template <class T>
SLinkedList<T>::SLinkedList() {
	this->list = new HeaderNode<T>();
}

template <class T>
void SLinkedList<T>::addFront(T data) {
	Node<T>* newNode = new Node<T>(data);
	if (this->list->count == 0) {
		this->list->front = newNode;
		this->list->back = newNode;
		this->list->count++;
	}
	else {
		newNode->next = this->list->front;
		this->list->front = newNode;
		this->list->count++;
	}
}

template <class T>
void SLinkedList<T>::addBack(T data) {
	if (this->list->count == 0) {
		this->addFront(data);
	}
	else {
		Node<T>* newNode = new Node<T>(data);
		this->list->back->next = newNode;
		this->list->back = newNode;
		this->list->count++;
	}
}

template <class T>
void SLinkedList<T>::removeFront() {
	if (this->list->count > 1) {
		Node<T>* tempPtr = this->list->front;
		this->list->front = tempPtr->next;
		delete tempPtr;
		this->list->count--;
	}
	else if (this->list->count == 1) {
		Node<T>* tempPtr = this->list->front;
		this->list->front = nullptr;
		this->list->back = nullptr;
		delete tempPtr;
		this->list->count--;
	}
	else {
		throw - 1;
	}
}

template <class T>
void SLinkedList<T>::removeBack() {
	if (this->list->count > 1) {
		Node<T>* tempPtr = this->list->back;
		Node<T>* prevPtr = this->list->front;
		while (prevPtr->next != tempPtr) {
			prevPtr = prevPtr->next;
		}
		prevPtr->next = nullptr;
		this->list->back = prevPtr;
		delete tempPtr;
		this->list->count--;
	}
	else if (this->list->count == 1) {
		Node<T>* tempPtr = this->list->back;
		this->list->front = nullptr;
		this->list->back = nullptr;
		delete tempPtr;
		this->list->count--;
	}
	else {
		throw - 1;
	}
}

template <class T>
void SLinkedList<T>::addInOrder(T data) {
	Node<T>* prevPtr = this->list->front;
	if (prevPtr == nullptr || data < prevPtr->data) {
		this->addFront(data);
	}
	else {
		while ((prevPtr->next != nullptr) && (data < prevPtr->next->data)) {
			prevPtr = prevPtr->next;
		}
		Node<T>* newNode = new Node<T>(data);
		if (prevPtr->next == nullptr) {
			prevPtr->next = newNode;
			this->list->back = newNode;
			this->list->count++;
		}
		else {
			newNode->next = prevPtr->next;
			prevPtr->next = newNode;
			this->list->count++;
		}
	}
}

template <class T>
void SLinkedList<T>::removeNode(T data) {
	Node<T>* prevPtr = this->list->front;
	if (prevPtr->data == data) {
		this->deleteFront();
		return;
	}
	while ((prevPtr->next != nullptr) && (prevPtr->next->data != data)) {
		prevPtr = prevPtr->next;
	}
	if (prevPtr->next == nullptr) {
		return;
	}
	else if (prevPtr->next->data == data) {
		Node<T>* tempPtr = prevPtr->next;
		prevPtr->next = tempPtr->next;
		delete tempPtr;
		this->list->count--;
	}
}

template <class T>
bool SLinkedList<T>::search(T data) {
	Node<T>* tempPtr = this->list->front;
	if (tempPtr->data == data) {
		return true;
	}
	while (tempPtr->next != nullptr) {
		if (tempPtr->data == data) {
			return true;
		}
		else {
			tempPtr = tempPtr->next;
		}
	}
	return false;
}

template <class T>
int SLinkedList<T>::returnCount() {
	return this->list->count;
}

template <class T>
void SLinkedList<T>::emptyList() {
	while (this->list->count > 0) {
		removeFront();
	}
}

template <class T>
SLinkedList<T>::~SLinkedList() {
	emptyList();
	delete this->list;
}

#endif LINKEDLIST_H
