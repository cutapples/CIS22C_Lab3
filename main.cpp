#include <iostream>
#include "Stack.h"
#include "SLinkedList.h"
#include "HeaderNode.h"
#include "Queue.h"

using namespace std;

void askForEquation(string& equation);
void fillQueue(string equation);

int main(){
    
   
    //Queue<char> userQueue;
    string equation = " ";
    
    askForEquation(equation);
    fillQueue(equation);
    
    
    cout << equation << endl;
    
}

void askForEquation(string& equation){
   
    
    cout << "Enter an equation: \n";
    
    cin >> equation;
    
    
}

void fillQueue(string equation){
    
    Queue<char> userQueue;
    Stack<int> intStack;
    Stack<char> charStack;

    for(int i = 0; i <= sizeof(equation); i++){
        
        userQueue.enqueue(equation[i]);
        
    }
    
}
