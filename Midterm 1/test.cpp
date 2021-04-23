//
//  test.cpp
//  Midterm 1
//
//  Created by Hyerin Lee on 4/22/21.
//

#include "test.h"
#include <string>
#include<iostream>
StringList::StringList(std::string text)
{
    //  For example, StringList s("heap"); creates s containing
    //  a list with values  'h'  'e'  'a'  'p'
  head = nullptr;
  for (int k = text.size(); k > 0; k--)
    head = new Node(text[k-1], head);
}
void StringList::eraseEvens(){
    if(head == nullptr){
        return;
    }
    int counter = 1;
    Node *q = nullptr;
    Node *p = head;
    while(p != nullptr){
        
        if(counter%2 == 0){
            q->next = p->next;
            delete p;
            p = p->next;
            
        }
        else if(counter%2 != 0){
            q = p;
            p = p->next;
            
            
        }
        counter++;
        
        
        
    }
    if(counter%2 == 0){
        delete p;
        p = nullptr;
    }
}
StringList::~StringList(){
    Node *temp;
     while(head != nullptr) {
     temp = head;
     head = head->next;
     delete temp;
         std::cout << "deleted" << std::endl;
     }
}
void StringList::print(){
    Node *p;
    for(p = head; p != nullptr; p = p->next){
        std::cout << p->value;
    }
    
    
}
