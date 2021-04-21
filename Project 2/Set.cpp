//
//  Set.cpp
//  Project 2
//
//  Created by Hyerin Lee on 4/17/21.
//
#include "Set.h"
#include <iostream>

Set::Set(){
    m_size = 0;
    m_head = new Node; // create dummy node
    m_head->prev = m_head; // prev and next pointer points to itself
    m_head->next = m_head;
}
Set::Set(const Set & other){
    m_size = other.m_size;
    m_head = new Node; // create dummy node
    
    Node * p;
    Node * n;
    n = m_head; //pointer to track the set that's being created
    for(p = other.m_head; p->next != other.m_head; p = p->next){
        n->next = new Node; //creates new node after the last node
        n->next->value = p->next->value; // sets value of the new node
        n->next->prev = n; // new node's prev pointer points to what was previously the tail
        m_head->prev = n->next; // new node becomes the tail
        n->next->next = m_head; // next pointer of the new tail is head
        
        n = n->next;//advance n to the next element to keep up with p
    }
    n->next = m_head; // sets the next pointer for the last element
    m_head->prev = n; // tail becomes the last node
    
}
Set::~Set(){
    Node *p = m_head->prev; // tail
    int count = 0;
    while(p != m_head){
        count++;
        p->next = m_head->next; // second element becomes head
        delete m_head;
        m_head = p->next; // advance head pointer to next element
        
    }
    delete m_head;

    m_head = nullptr; //made nullptr so it's not left hanging
}
Set& Set::operator=(const Set& other){
    
    
    if(this != &other){
        Set temp(other); // create temporary set from other
        swap(temp);
    }
    
    return *this;
}

bool Set::insert(const ItemType& value){
    Node *p;
    for(p = m_head; p->next != m_head; p = p->next){
        if(p->next->value == value){ // if value exists
            return false;
        }
    }
    Node *n = m_head->prev; //pointer to tail
    n->next = new Node; //create new node after tail
    n->next->value = value; // assign value
    m_head->prev = m_head->prev->next; // new node becomes the tail
    m_head->prev->next = m_head; // new tail's next pointer points to head
    m_head->prev->prev = n; // prev pointer of tail is the old tail
    m_size++;
    return true;
}

bool Set::erase(const ItemType& value){
    if(m_size == 0){
        return false;
    }
    Node *p;
    for(p = m_head; p->next != m_head; p = p->next){
        if(p->next->value == value){ // if value is found
            Node * toBeDeleted = p->next;
            p->next = toBeDeleted->next; //adjust next pointer to skip toBeDeleted node
            toBeDeleted->next->prev = toBeDeleted->prev; // adjust prev pointer to skip toBeDelete node
            delete toBeDeleted;
            m_size--;
            return true;
        }
    }
    return false;
}

bool Set::contains(const ItemType& value) const{
    Node *p;
    for(p = m_head; p->next != m_head; p = p->next){
        if(p->next->value == value){
            return true;
        }
    }
    
    return false;
}

bool Set::get(int i, ItemType& value) const{ //DONE
    if(i<0 || i>=m_size){ // if i is an invalid value
        return false;
    }
    ItemType currItem;
    int count;
    for(Node *j = m_head; j->next != m_head; j = j->next){
        count = 0;
        currItem = j->next->value;
        for(Node *k = m_head; k->next != m_head; k = k->next){
            if(currItem < k->next->value){ // compare current value with every other value in the list
                count ++;
                
            }
            if(k->next->next == m_head && count == i){
                //if at the end of the loop current value is exactly less than i items
                value = currItem;
                return true;
            }
            
            
        }
      
    }
    return false;
}
void Set::swap(Set& other){
    std::swap(m_size, other.m_size);
    std::swap(m_head, other.m_head);
}

void unite(const Set& s1, const Set& s2, Set& result){
    Set copy; // create a copy to assign later to result
    ItemType current;
    for(int i = 0; i<s1.size(); i++){ //get every value in the list
        s1.get(i, current);
        copy.insert(current);
    }
    for(int j = 0; j<s2.size(); j++){
        s2.get(j, current);
        copy.insert(current);
    }
    //result becomes the copy set
    result = copy;
}

void difference(const Set& s1, const Set& s2, Set& result){
    Set copy;
    ItemType current1;
    for(int i = 0; i<s1.size(); i++){
        s1.get(i, current1); // get each element of the set
        if(!s2.contains(current1)){ // if current value is only in s1
            copy.insert(current1);
        }
        
        
    }
    ItemType current2;
    for(int j = 0; j<s2.size(); j++){
        s2.get(j, current2); // get each element of the set
        if(!s1.contains(current2)){ // if current value is only in s2
            copy.insert(current2);
        }
        
    }
    result = copy;
    
}
