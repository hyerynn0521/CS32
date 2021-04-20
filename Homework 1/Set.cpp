//
//  Set.cpp
//  Homework 1
//
//  Created by Hyerin Lee on 4/12/21.
//

#include <stdio.h>
#include "Set.h"

Set::Set(){
    m_Size = 0;
}

bool Set::empty() const{ //DONE
    if(m_Size == 0){
        return true;
    }
    return false;
}

int Set::size() const{ //DONE
    
    return m_Size;
}
bool Set::insert(const ItemType& value){ //DONE
    if(m_Size >= DEFAULT_MAX_ITEMS){
        return false;
    }
    for (int i = 0; i<m_Size; i++){
        if(value == m_Array[i]){
            return false;
        }
    }
    
        m_Size++;
    
    m_Array[m_Size - 1] = value;
    return true;
}

bool Set::erase(const ItemType& value){ //DONE
    if(m_Size <= 0){
        return false;
    }
    int index = 0;
    for(int i = 0; i<m_Size; i++){
        if(m_Array[i] == value){
            index = i;
            for(int j = index; j<m_Size; j++){
                if(j < DEFAULT_MAX_ITEMS - 1){
                    m_Array[j] = m_Array[j+1];
                }
            }
            m_Size--;
            return true;
            
        }
        
    }
    return false;
}

bool Set::contains(const ItemType& value) const{ //DONE
    for(int i = 0; i<m_Size; i++){
        if(m_Array[i] == value){
            return true;
        }
    }
    return false;
}

bool Set::get(int i, ItemType& value) const{ //DONE
    if(i<0 || i>=m_Size){
        return false;
    }
    ItemType currItem;
    int count;
    for(int j = 0; j<m_Size; j++){
        count = 0;
        currItem = m_Array[j];
        for(int k = 0; k<m_Size; k++){
            if(currItem < m_Array[k]){
                count ++;
                
            }
            if(k == m_Size - 1 && count == i){
                value = currItem;
                return true;
            }
            
            
        }
       // if(i == 0 && count == 0){
         //   value = currItem;
           // return true;
        //}
    }
    return false;
}
void Set::swap(Set& other){
    
    std::swap(other.m_Array, m_Array);
    std::swap(other.m_Size, m_Size);
    
}


