//
//  AccountSet.cpp
//  Homework 1
//
//  Created by Hyerin Lee on 4/12/21.
//

#include "AccountSet.h"
#include <iostream>
AccountSet::AccountSet(){
    
}
bool AccountSet::add(ItemType acctNum){
    return m_AccountSet.insert(acctNum);
}

int AccountSet::size() const{
    return m_AccountSet.size();
}

void AccountSet::print() const{
    ItemType value;
    for (int i = 0; i<m_AccountSet.size(); i ++) {
        m_AccountSet.get(i, value);
        std::cout << i << " " << value << std::endl;
    }
}
