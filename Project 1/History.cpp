//
//  History.cpp
//  Project 1
//
//  Created by Hyerin Lee on 4/5/21.
//
#include <stdio.h>
#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
using namespace std;
#include "History.h"

History::History(int nRows, int nCols){
    m_Rows = nRows;
    m_Cols = nCols;
    for (int r = 0; r < m_Rows; r++)
        for (int c = 0; c < m_Cols; c++)
            m_History[r][c] = '.';
}
bool History::record(int r, int c){
    if(r<1 || c <1 || r > m_Rows || c > m_Cols){
        return false;
    }
    if(m_History[r-1][c-1] == '.'){
        m_History[r-1][c-1] = 'A';
    }
    else if (m_History[r-1][c-1] != '.' && m_History[r-1][c-1] != 'Z'){
        m_History[r-1][c-1]++;
    }
    
    return true;
}
void History::display() const{
    clearScreen();
    for (int r = 0; r < m_Rows; r++)
    {
        for (int c = 0; c < m_Cols; c++)
            cout << m_History[r][c];
        cout << endl;
    }
    cout << endl;
    
}
