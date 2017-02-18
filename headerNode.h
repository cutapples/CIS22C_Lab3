#ifndef HeaderNode_h
#define HeaderNode_h

#include <stdio.h>

#ifndef HEADERNODE_H
#define HEADERNODE_H

template <class T>
class HeaderNode {
public:
    Node<T>* front;
    Node<T>* back;
    int count;
    
    HeaderNode();
};

template <class T>
HeaderNode<T>::HeaderNode() {
    this->front = nullptr;
    this->back = nullptr;
    this->count = 0;
}

#endif HEADERNODE_H


#endif /* HeaderNode_hpp */
