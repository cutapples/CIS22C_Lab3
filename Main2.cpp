#include <iostream>
#include <string>
#include <math.h>
#include "Stack.h"
#include "Queue.h"

using namespace std;

void infixToPostfix(Queue<char>&, Queue<char>&, Stack<char>&);
double evaluatePostfix(Queue<char>&, Stack<double>&);

bool checkInput(Queue<char>&);
bool isOperand(char);
bool isOperator(char);
bool validInput(char, char);
int operatorPrecedence(char);

int main() {
    
    Queue<char> userQueue;
    Queue<char> postfixQueue;
    
    Stack<char> operatorStack;
    Stack<double> calculatingStack;
    
    double finalAnswer=0.0;
    
    string userExp;
    
    bool invalidInput = false;
    
    //Getting User Input
    do {
        std::cout << "====================Input Phase====================" << std::endl
        << "Please input an expression in infix notation" << std::endl
        << "Only use positive integers between 0 and 9" << std::endl
        << "Only use valid operands (+, -, *, /, ^, (, ))" << std::endl
        << "Current Expression: ";
        
        getline(cin, userExp);
        
        
        
        userExp.append("#");
        for (string::iterator i = userExp.begin(); i != userExp.end(); ++i) {
            if (*i != ' ') {
                userQueue.enqueue(*i);
            }
        }
        
       // system("cls");
        
        //Checking validity of the user's expression
        try {
            invalidInput = checkInput(userQueue);
        }
        catch(string error) {
            cout << "Your expression: ";
            while (!userQueue.isEmpty()) {
                char temp;
                postfixQueue.dequeue(temp);
                cout << temp;
            }
            cout << endl << error << endl << endl;
            invalidInput = false;
        }
        
    } while (!invalidInput);
    
    //Infix to Postfix
    infixToPostfix(userQueue, postfixQueue, operatorStack);
    
       //Postfix Evaluation
   finalAnswer = evaluatePostfix(postfixQueue, calculatingStack);
    
    
    //Display Results
    while (!postfixQueue.isEmpty()) {
        char temp;
        postfixQueue.dequeue(temp);
        cout << temp;
        
    }
    
    cout << finalAnswer << endl;
    
    
    
    
    cout << endl;
    
    
    return 0;
}

bool checkInput(Queue<char>& userQueue) {
    char currentInput, prevInput;
    int pBalance = 0;
    
    //Test first character
    userQueue.dequeue(currentInput);
    if (isOperand(currentInput) || currentInput == '(') {
        if (currentInput == '(') {
            pBalance++;
        }
        userQueue.enqueue(currentInput);
        prevInput = currentInput;
    }
    else {
        string x = "Invalid First Character";
        throw x;
    }
    
    //Test the rest of the input
    userQueue.dequeue(currentInput);
    while (currentInput != '#') {
        if (validInput(currentInput, prevInput)) {
            if (currentInput == '(') {
                pBalance++;
            }
            else if (currentInput == ')') {
                pBalance--;
                if (pBalance < 0) {
                    string x = "Uneven Parenthesis";
                    throw x;
                }
            }
            userQueue.enqueue(currentInput);
            prevInput = currentInput;
        }
        else {
            string x = "Invalid sequence of operands or operators";
            throw x;
        }
        userQueue.dequeue(currentInput);
    }
    userQueue.enqueue(currentInput);
    if (pBalance == 0) {
        return true;
    }
    else {
        string x = "Uneven Parenthesis";
        throw x;
    }
}

//Tests if c is a valid operand (0-9)
bool isOperand(char c) {
    return (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9');
}

//Tests if c is a valid operator (+, -, *, /, ^, or ')')
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == ')');
}

//Tests if c, the current input, is valid given p, the previous input)
bool validInput(char c, char p) {
    return ((isOperand(c) && isOperator(p)) ||
            (isOperator(c) && isOperand(p)) ||
            (c == '(' && isOperator(p)) ||
            (c == '0' && p != '/') ||
            (isOperand(c) && p == '(') ||
            (c == '(' && p == '(') ||
            (isOperator(c) && p == ')')
            );
}

int operatorPrecedence(char c) {
    if (c == '0') return -1;
    else if (c == '(') return 0;
    else if (c == '+' || c == '-') return 1;
    else if (c == '*' || c == '/') return 2;
    else if (c == '^') return 3;
    else return -1;
}

void infixToPostfix(Queue<char>& userQueue, Queue<char>& postfixQueue, Stack<char>& operatorStack) {
    char currentOutput;
    char prevOperator;
    
    userQueue.dequeue(currentOutput);
    while (currentOutput != '#') {
        if (isOperand(currentOutput)) {
            //Enqueue operands onto the postfixQueue
            postfixQueue.enqueue(currentOutput);
        }
        else {
            //Current Output is an operator
            //If the previous operator has lower precedence, put the current output onto the stack
            //If the previous operator has a higher precedence, pop the stack onto the queue until a higher precedence operator is reached
            //Special case for close parenthesis
            if (!operatorStack.isEmpty()) {
                operatorStack.top(prevOperator);
            }
            else {
                prevOperator = '0';
            }
            
            if (currentOutput == ')') {
                //Pop the stack until you reach the corresponding '('
                operatorStack.pop(prevOperator);
                while (prevOperator != '(') {
                    postfixQueue.enqueue(prevOperator);
                    operatorStack.pop(prevOperator);
                }
            }
            
            //If the precedence of the current operator is higher than the previous operator, push the current operator onto the stack
            else if (operatorPrecedence(prevOperator) < operatorPrecedence(currentOutput)) {
                operatorStack.push(currentOutput);
            }
            else {
                //The previous operator has the higher precedence, pop the stack onto the queue until a higher precedence is reached
                while (operatorPrecedence(prevOperator) >= operatorPrecedence(currentOutput)) {
                    operatorStack.pop(prevOperator);
                    postfixQueue.enqueue(prevOperator);
                    if (!operatorStack.isEmpty()) {
                        operatorStack.top(prevOperator);
                    }
                    else {
                        prevOperator = '0';
                    }
                }
                //Put the current output onto the newly emptied stack
                operatorStack.push(currentOutput);
            }
        }
        //Update the next currentOutput
        userQueue.dequeue(currentOutput);
    }
    //The userQueue is empty. Pop the rest of the operator stack onto the postfix Queue.
    while (!operatorStack.isEmpty()) {
        char temp;
        operatorStack.pop(temp);
        postfixQueue.enqueue(temp);
    }
}

double evaluatePostfix(Queue<char>&postfixQueue, Stack<double>& calculatingStack) {
    /*
     Dequeue postfixQueue onto a char variable
     If it's a number (use isOperand) convert it into a double and put it on the calculating stack
     Otherwise its an operator,
     Pop 2 numbers off of the calculating stack into double variables
     using either a switch or if statements, do operations to the 2 numbers depending on what the operator is (you can use pow(a, b) for exponents)
     Make sure to check for dividing by zero when you do division
     push the resulting double onto the calculating stack
     */

    char c;
    double num1, num2, result, finalAnswer = 0.0;

    //while(postfixQueue.front() != '#'){

        
    
    c = postfixQueue.front();
    
        if(c == '#'){
            
            calculatingStack.top(finalAnswer);
            
            cout << finalAnswer << endl;
           // break;
        }
        
        
    else if(isOperand(c)){
        int temp = c - '0';
        calculatingStack.push(temp);
    }
    
    
    else{
        if(c == '+'){
            calculatingStack.pop(num1);
            calculatingStack.pop(num2);
            
            result = num1 + num2;
            
            postfixQueue.dequeue();
            
            calculatingStack.push(result);
            
        }
        
        else if(c == '-'){
            calculatingStack.pop(num1);
            calculatingStack.pop(num2);
            result = num1 - num2;
            calculatingStack.push(result);
            
            
        }
        
        else if(c == '*'){
            calculatingStack.pop(num1);
            calculatingStack.pop(num2);
            result = num1 * num2;
            calculatingStack.push(result);
            
            
        }
        
        else if(c == '^'){
            calculatingStack.pop(num1);
            calculatingStack.pop(num2);
            result = pow(num1, num2);
            calculatingStack.push(result);
            
        }
        
        else if(c == '/'){
            calculatingStack.pop(num1);
            calculatingStack.pop(num2);
            
            
            if(num2 == 0){
                cout << "You can not divide by 0!!!\n";
            }
            
            else{
                result = num1 / num2;
                calculatingStack.push(result);
                //calculatingStack.top(finalAnswer);
                
            }
            
           calculatingStack.top(finalAnswer);
        }
        
    // }
            }
    
    return finalAnswer;
}
