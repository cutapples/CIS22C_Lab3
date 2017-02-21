#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include "SLinkedList.h"
#include "HeaderNode.h"
using namespace std;

template <class T>
class Queue : protected SLinkedList<T> {
public:
    
    void enqueue(T data);
    void dequeue(T& data);
    void dequeue();
    T front();
    bool isEmpty();
    void emptyQueue();
};

template <class T>
void Queue<T>::enqueue(T data) {
    this->addBack(data);
}

template <class T>
void Queue<T>::dequeue(T& data) {
    data = this->list->front->data;
    this->removeFront();
}

template <class T>
void Queue<T>::dequeue() {
    this->removeFront();
}

template <class T>
T Queue<T>::front() {
    //data = this->list->front->data;
    return this->list->front->data;
}

template <class T>
bool Queue<T>::isEmpty() {
    return (this->list->count == 0);
}

template<class T>
void Queue<T>::emptyQueue() {
    this->emptyList();
}

#endif QUEUE_H
