#include <iostream>
#include "Stack.h"
#include "SLinkedList.h"
#include "HeaderNode.h"

using namespace std;

void askForEquation(string& equation);
void parseEquation(string equation);

int main(){
    
    Stack<int> intStack;
    Stack<char> charStack;
    string equation = " ";
    
    askForEquation(equation);
    parseEquation(equation);
    
    
    cout << equation << endl;
    
}

void askForEquation(string& equation){
    
    cout << "Enter an equation: \n";
    
    cin >> equation;
    
    
}

void parseEquation(string equation){

    

}
