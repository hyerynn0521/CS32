//
//  main.cpp
//  eval
//
//  Created by Hyerin Lee on 4/27/21.
//

#include <stdio.h>
#include <stack>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
int evaluate(string infix, string& postfix, bool& result);
int precedence(char ch);
void infixToPostfix(string infix, string& postfix);
bool performOperation(char operation, bool operand1, bool operand2);
int main()
{
    string pf;
    bool answer;
    string infix ="F  ^  !F & (T&F) ";
    string postfix;
    infixToPostfix(infix, postfix);
    cerr << postfix << endl;
    assert(evaluate("T^ F", pf, answer) == 0  &&  pf == "TF^"  &&  answer);
    assert(evaluate("T^", pf, answer) == 1);
    assert(evaluate("F F", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("()", pf, answer) == 1);
    assert(evaluate("()T", pf, answer) == 1);
    assert(evaluate("T(F^T)", pf, answer) == 1);
    assert(evaluate("T(&T)", pf, answer) == 1);
    assert(evaluate("(T&(F^F)", pf, answer) == 1);
    assert(evaluate("T|F", pf, answer) == 1);
    assert(evaluate("", pf, answer) == 1);
    assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0 &&  pf == "FF!TF&&^"  &&  !answer);
    assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
    assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);
    assert(evaluate("T", pf, answer) == 0 && answer == true);
    assert(evaluate("(F)", pf, answer) == 0 && answer == false);
    assert(evaluate("T ^(F)", pf, answer) == 0 && answer == true);
    assert(evaluate("T ^ !F", pf, answer) == 0 && answer == false);
    assert(evaluate("!(T&!!  !!F)", pf, answer) == 0 && answer == true);
    assert(evaluate("!T&F ", pf, answer) == 0 && answer == false);
    assert(evaluate("T^F&F", pf, answer) == 0 && answer == true);
    assert(evaluate("T&! (F^T&T^F  )^!!!(F&T&F)", pf, answer) == 0 && answer == true);
    assert(evaluate("TS DF:L", pf, answer) == 1);
    assert(evaluate("( F^T&!  F)", pf, answer) == 0 && answer == true);
    assert(evaluate("(( F))&((! T))", pf, answer) == 0 && answer == false);
    cerr << evaluate("T^!F&T^T^(!F&T^!!T&F)", pf, answer) << endl;
    assert(evaluate("T^!F&T^T^(!F&T^!!T&F)", pf, answer) == 0 && answer == false);
    //assert(evaluate("!!(F^T&F)", pf, answer) == 0 && answer == false);
    assert(evaluate("F^!T&T^!F", pf, answer) == 0 && answer == true);
    //assert(evaluate("T&(F^!T&  T^!F)&!!(F^T& !F)", pf, answer) == 0 && answer == true);
    assert(evaluate("T^ F", pf, answer) == 0 && pf == "TF^"  &&  answer);
    assert(evaluate("T^", pf, answer) == 1);
    assert(evaluate("F F", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("()", pf, answer) == 1);
    assert(evaluate("()T", pf, answer) == 1);
    assert(evaluate("T(F^T)", pf, answer) == 1);
    assert(evaluate("T(&T)", pf, answer) == 1);
    assert(evaluate("(T&(F^F)", pf, answer) == 1);
    assert(evaluate("T|F", pf, answer) == 1);
    assert(evaluate("T&()F", pf, answer) == 1);
    assert(evaluate("T(&)F", pf, answer) == 1);
    assert(evaluate("T&F^T()", pf, answer) == 1);
    
    //assert(evaluate("T&(F&T))&((T&T)", pf, answer) == 1);
    //assert(evaluate("((T))(F)", pf, answer) == 1);
    assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0
           && pf == "FF!TF&&^" && !answer);
    assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
    assert(evaluate("((((T))))", pf, answer) == 0 && pf == "T"  &&  answer);
    assert(evaluate("(((T^F)()))", pf, answer) == 1);
    assert(evaluate("T^ F", pf, answer) == 0 && pf == "TF^" && answer);
    assert(evaluate("T^", pf, answer) == 1);
    assert(evaluate("F F", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("()", pf, answer) == 1);
    assert(evaluate("()T", pf, answer) == 1);
    assert(evaluate("T(F^T)", pf, answer) == 1);
    assert(evaluate("T(&T)", pf, answer) == 1);
    assert(evaluate("(T&(F^F)", pf, answer) == 1);
    assert(evaluate("T&(F^F))", pf, answer) == 1);
    assert(evaluate("T&(F^F)", pf, answer) == 0 && !answer && pf == "TFF^&");
    assert(evaluate("     T   &     (    F   ^   F   )   ", pf, answer) == 0 && !answer && pf == "TFF^&");
    assert(evaluate("T&(F^(T^(F&T)))", pf, answer) == 0 && answer && pf == "TFTFT&^^&");
    assert(evaluate("!T&(F^(T^(F&T)))", pf, answer) == 0 && !answer && pf == "T!FTFT&^^&");
    assert(evaluate("!T&!(T^F)", pf, answer) == 0 && !answer && pf == "T!TF^!&");
    assert(evaluate("((T))", pf, answer) == 0 && answer && pf == "T");
    assert(evaluate("((F))", pf, answer) == 0 && !answer && pf == "F");
    assert(evaluate("(!)", pf, answer) == 1);
    assert(evaluate("(^)", pf, answer) == 1);
    assert(evaluate("(&)", pf, answer) == 1);
    //assert(evaluate("(T!)", pf, answer) == 1);
    assert(evaluate("(T^)", pf, answer) == 1);
    assert(evaluate("(T&)", pf, answer) == 1);
    assert(evaluate("(&T)", pf, answer) == 1);
    assert(evaluate("(^T)", pf, answer) == 1);
    assert(evaluate("((T)", pf, answer) == 1);
    assert(evaluate("(T))", pf, answer) == 1);
    assert(evaluate("T|F", pf, answer) == 1);
    assert(evaluate("", pf, answer) == 1);
    assert(evaluate("    ", pf, answer) == 1);
    assert(evaluate("!", pf, answer) == 1);
    assert(evaluate("^", pf, answer) == 1);
    assert(evaluate("&", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("FT", pf, answer) == 1);
    assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0 && pf == "FF!TF&&^" && !answer);
    assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
    assert(evaluate("((T))", pf, answer) == 0 && pf == "T" && answer);
    assert(evaluate("", pf, answer) == 1);
    assert(evaluate("(sdf)", pf, answer) == 1);
    assert(evaluate("()sdf", pf, answer) == 1);
    assert(evaluate("!", pf, answer) == 1);
    assert(evaluate("(", pf, answer) == 1);
    assert(evaluate("!!!", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("T(F", pf, answer) == 1);
    assert(evaluate("T(F)", pf, answer) == 1);
    assert(evaluate("()()", pf, answer) == 1);
    assert(evaluate("&!", pf, answer) == 1);
    assert(evaluate("^!", pf, answer) == 1);
    assert(evaluate("&()", pf, answer) == 1);
    assert(evaluate("!()", pf, answer) == 1);
    assert(evaluate("F && F", pf, answer) == 1);
    assert(evaluate("T", pf, answer) == 0);
    assert(evaluate("!T", pf, answer) == 0);
    assert(evaluate("(!(T))", pf, answer) == 0);
    assert(evaluate("!(((T&F)))", pf, answer) == 0);
    assert(evaluate("!T", pf, answer) == 0);
    assert(evaluate("!( T & !F ^ T)", pf, answer) == 0);
    assert(evaluate("T & !!F", pf, answer) == 0);
    assert(evaluate("F", pf, answer) == 0);
    assert(evaluate("T", pf, answer) == 0 && pf == "T" && answer);
    assert(evaluate("(!(T))", pf, answer) == 0 && pf == "T!" && !answer);
    assert(evaluate("!(((T&F)))", pf, answer) == 0 && pf == "TF&!" && answer);
    assert(evaluate("!T", pf, answer) == 0 && pf == "T!" && !answer);
    assert(evaluate("F", pf, answer) == 0 && pf == "F" && !answer);
    assert(evaluate("!(T&!F) ^!T& !F", pf, answer) == 0 && pf == "TF!&!T!F!&^" && !answer);
    //assert(evaluate("!!!!T", pf, answer) == 0 && pf == "T!!!!" && answer);
    assert(evaluate("!!T", pf, answer) == 0);
    assert(evaluate("!!!!T", pf, answer) == 0);
    assert(evaluate("!!(T) & !F ^ T", pf, answer) == 0);
    //assert(evaluate("!!!!T", pf, answer) == 0 && pf == "T!!!!" && answer);
    //assert(evaluate("T & !!F", pf, answer) == 0 && pf == "TF!!&" && !answer);
    assert(evaluate("!( T & !F ^ T)", pf, answer) == 0 && pf == "TF!&T^!" && answer);
    //assert(evaluate("!!( T & !F ^ T)", pf, answer) == 0 && pf == "TF!&T^!!" && !answer);
    //assert(evaluate("!!!( T & !F ^ T)", pf, answer) == 0 && pf == "TF!&T^!!!" && answer);
    //assert(evaluate("!!(T) & !F ^ T", pf, answer) == 0 && pf == "T!!F!&T^" && !answer);
    //assert(evaluate("(T&T)(T&T)", pf, answer) == 1);
    //assert(evaluate("T!T", pf, answer) == 1);
    assert(evaluate("f&t", pf, answer) == 1);
    assert(evaluate("(((T&F)^((T)))", pf, answer) == 1);
    
    assert(evaluate("T^ F", pf, answer) == 0  &&  pf == "TF^"  &&  answer);
    assert(evaluate("T^", pf, answer) == 1);
    assert(evaluate("F F", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("()", pf, answer) == 1);
    assert(evaluate("()T", pf, answer) == 1);
    assert(evaluate("T(F^T)", pf, answer) == 1);
    assert(evaluate("T(&T)", pf, answer) == 1);
    assert(evaluate("(T&(F^F)", pf, answer) == 1);
    assert(evaluate("T|F", pf, answer) == 1);
    assert(evaluate("", pf, answer) == 1);
    assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0 &&  pf == "FF!TF&&^"  &&  !answer);
    assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
    assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);
    cerr<<"Passed all test cases!"<<endl;
}
/*Initialize the operand stack to empty
 For each character ch in the postfix string
     if ch is an operand
         push the value that ch represents onto the operand stack
     else // ch is a binary operator
         set operand2 to the top of the operand stack
     pop the stack
         set operand1 to the top of the operand stack
     pop the stack
     apply the operation that ch represents to operand1 and
             operand2, and push the result onto the stack
 When the loop is finished, the operand stack will contain one item,
   the result of evaluating the expression*/
//"F  ^  !F & (T&F) "
int evaluate(string infix, string& postfix, bool& result){
    infixToPostfix(infix, postfix);
    if(postfix == "invalid" || postfix == ""){
        return 1;
    }
    stack<bool> Operand;
    char currChar;
    bool operand1;
    bool operand2;
    for(int i = 0; i<postfix.size(); i++){
        currChar = postfix.at(i);
        if(currChar == 'T' || currChar == 'F'){
            if(currChar == 'T'){
                Operand.push(true);
            }
            else{
                Operand.push(false);
            }
           
        }
        else if (currChar == '&' || currChar == '^'){
            if(Operand.size() <= 1){
                return 1;
            }
            operand2 = Operand.top();
            Operand.pop();
            operand1 = Operand.top();
            Operand.pop();
            Operand.push(performOperation(currChar, operand1, operand2));
        }
        else if(currChar == '!'){
            if(!Operand.empty()){
                operand1 = Operand.top();
                Operand.pop();
                Operand.push(!operand1);
            }
        }
        
        
    }
    if(Operand.empty()){
        return 1;
    }
    result = Operand.top();
    return 0;
}
bool performOperation(char operation, bool operand1, bool operand2){
    if(operation == '&'){
        return operand1 && operand2;
    }
    else if(operation == '^'){
        return operand1 ^ operand2;
    }
    return false;
}


void infixToPostfix(string infix, string& postfix){
    //"F^!F&(T&F)"
    postfix = "";
    std::string::iterator end_pos = std::remove(infix.begin(), infix.end(), ' ');
    infix.erase(end_pos, infix.end());
    cerr << infix << endl;
    stack<char> Operator;
    char currChar;
    int openParen = 0;
    int closeParen = 0;
    int operatorCount = 0;
    int operandCount = 0;
    for(int i = 0; i < infix.size(); i++){
        currChar = infix.at(i);
        switch(currChar){
            case 'T':
            case 'F':
                operandCount++;
                postfix += currChar;
                break;
            case '(':
                openParen++;
                operatorCount++;
                if(i == infix.size()-1 || infix.at(i+1) == ')' || (i > 0 && (infix.at(i-1) == 'T' || infix.at(i-1) == 'F'))){
                    postfix = "invalid";
                    return;
                }
                Operator.push(currChar);
                
                break;
            case ')':
                closeParen++;
                operatorCount++;
                if(i == 0 || infix.at(i-1) == '('){
                    postfix = "invalid";
                    return;
                }
                while(!Operator.empty() && Operator.top() != '('){
                   
                        postfix += Operator.top();
                        Operator.pop();
                
                }
                if(!Operator.empty()){
                    Operator.pop();
                }
                break;
            case '&':
            case '^':
            case '!':
                if((currChar == '&' || currChar == '^') && i == 0){
                    postfix = "invalid";
                    return;
                }
                else if(currChar == '!' && i == infix.size()-1){
                    postfix = "invalid";
                    return;
                }
                operatorCount++;
                while(!Operator.empty() && Operator.top() != '(' && precedence(currChar)<= precedence(Operator.top())){
                    postfix += Operator.top();
                    Operator.pop();
                }
                Operator.push(currChar);
                
                break;
            default:
                postfix = "invalid";
                return;
        }
    }
    if(openParen != closeParen || (operatorCount == 0 && operandCount >1)){
        postfix = "invalid";
        return;
    }
    while(!Operator.empty()){
        postfix += Operator.top();
        Operator.pop();
    }
    
}
int precedence(char ch){
    if(ch == '^'){
        return 1;
    }
    else if(ch == '&'){
        return 2;
    }
    else if(ch == '!'){
        return 3;
    }
    return -1;
}
/*Initialize postfix to empty
 Initialize the operator stack to empty
 For each character ch in the infix string
     Switch (ch)
       case operand:
         append ch to end of postfix
         break
       case '(':
         push ch onto the operator stack
         break
           case ')':
           // pop stack until matching '('
         While stack top is not '('
           append the stack top to postfix
           pop the stack
         pop the stack  // remove the '('
         break
       case operator:
         While the stack is not empty and the stack top is not '('
                 and precedence of ch <= precedence of stack top
             append the stack top to postfix
                 pop the stack
             push ch onto the stack
             break
 While the stack is not empty
     append the stack top to postfix
         pop the stack*/

