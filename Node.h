#ifndef Node_h
#define Node_h

#include <stdio.h>

#ifndef NODE_H
#define NODE_H

template <class T>
struct Node {
public:
    T* data;
    Node<T>* next;
    
    Node();
    Node(T& data);
};

template <class T>
Node<T>::Node() {
    this->data = nullptr;
    this->next = nullptr;
}

template <class T>
Node<T>::Node(T& data) {
    this->data = &data;
    this->next = nullptr;
}

#endif NODE_H

#endif /* Node_hpp */
