//
//  Hive.cpp
//  Midterm 1
//
//  Created by Hyerin Lee on 4/22/21.
//

#include "Hive.h"
Hive::Hive(int b)
  {
    m_num = new Num(b);
    m_bb = 2 * b;
    m_bees = &m_bb;
  }
Hive::~Hive(){
    delete m_num;
    m_num = nullptr;
}
Hive::Hive(const Hive& other){
    m_num = new Num(other.m_bb/2);
    m_bb = other.m_bb;
    m_bees = &m_bb;
}

