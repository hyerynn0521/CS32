//
//  Scaffold.cpp
//  Project 3
//
//  Created by Hyerin Lee on 5/10/21.
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include <stack>
#include "provided.h"
#include "support.h"
using namespace std;

class ScaffoldImpl
{
  public:
    ScaffoldImpl(int nColumns, int nLevels);
    int cols() const;
    int levels() const;
    int numberEmpty() const;
    int checkerAt(int column, int level) const;
    void display() const;
    bool makeMove(int column, int color);
    int undoMove();

private:
    vector<vector<char>> m_scaffold;
    stack<int> m_history;
    int m_nColumns;
    int m_nLevels;
};

ScaffoldImpl::ScaffoldImpl(int nColumns, int nLevels)
{
    if(nColumns <= 0 || nLevels <= 0){
        cerr << "Invalid column or level value!" << endl;
        exit(0);
    }
    m_nColumns = nColumns;
    m_nLevels = nLevels;
    for(int level = 0; level <= m_nLevels; level++){
        //create new vector for each level
        vector<char> sublevel;
        for(int col = 0; col <= 2*m_nColumns; col++){
            //if bottom of the scaffold is reached, build the floor of + and -
            if(level == m_nLevels){
                if(col%2 == 0){
                    sublevel.push_back('+');
                }
                else{
                    sublevel.push_back('-');
                }
            }
            
            else{
                if(col%2 == 0){
                    sublevel.push_back('|');
                }
                else{
                    sublevel.push_back(' ');
                }
            }
        }
        m_scaffold.push_back(sublevel);
    }
    
}

int ScaffoldImpl::cols() const
{
    return m_nColumns;
}

int ScaffoldImpl::levels() const
{
    return m_nLevels;
}

int ScaffoldImpl::numberEmpty() const
{
    char currChar;
    int empty = 0;
    //loop over a vector to count number of empty slots
    
    for(int level = 0; level < m_nLevels; level++){
        for(int col = 1; col < 2 * m_nColumns + 1; col += 2){
            currChar = m_scaffold.at(level).at(col);
            if(currChar == ' '){
                empty++;
            }
        }
    }
    return empty;
}

int ScaffoldImpl::checkerAt(int column, int level) const
{
    //if invalid column or level
    if(column > m_nColumns || column <= 0 || level > m_nLevels || level <= 0){
        return VACANT;
    }
    //convert level in terms of vector index
    int convertedLevel = abs(m_nLevels - level);
    char currChar = m_scaffold.at(convertedLevel).at(2*column - 1);
    if(currChar == 'R'){
        return RED;
    }
    else if(currChar == 'B'){
        return BLACK;
    }
    return VACANT; 
}

void ScaffoldImpl::display() const
{
    //display the scaffold by looping through and cout-ing each character
    char currChar;
    for(int level = 0; level <= m_nLevels; level ++){
        for(int col = 0; col <= 2 * m_nColumns; col ++){
            currChar = m_scaffold.at(level).at(col);
            cout << currChar;
        }
        cout << endl;
    }
}

bool ScaffoldImpl::makeMove(int column, int color)
{
    if(column < 0 || column > m_nColumns || (color != RED && color != BLACK)){
        return false;
    }
    //convert user's column to index in vector
    int columnConvert = 2 * column - 1;

    //add history
    m_history.push(column);
    int i = 0;
    char currChar = m_scaffold.at(0).at(columnConvert);
    //if top of the column is filled
    if(currChar != ' '){
        return false;
    }
    //store the position of top checker at that column
    for(i = 0; i < m_nLevels; i ++){
        currChar = m_scaffold.at(i).at(columnConvert);
        if(currChar != ' '){
            break;
        }
        
    }
    //make a move on top of the position of current top checker
    if(color == RED)
        m_scaffold.at(i-1).at(columnConvert) = 'R';
    else if(color == BLACK)
        m_scaffold.at(i-1).at(columnConvert) = 'B';
    
    return true;
}

int ScaffoldImpl::undoMove()
{
    //if there is no move to undo
    if(m_history.empty()){
        return 0;
    }
    //convert column of the most recent move in terms of index of vector
    int columnConvert = 2 * m_history.top() - 1;
    int i = 0;
    char currChar = m_scaffold.at(0).at(columnConvert);
    //store the level of topmost checker at the column where the most recent move was made
    for(i = 0; i < m_nLevels; i++){
        currChar = m_scaffold.at(i).at(columnConvert);
        if(currChar == 'R' || currChar == 'B'){
            break;
        }
    }
    //empty the checker at the stored position
    m_scaffold.at(i).at(columnConvert) = ' ';
    int top = m_history.top();
    m_history.pop();
    return top; 
}


//******************** Scaffold functions *******************************

//  These functions simply delegate to ScaffoldImpl's functions.
//  You probably don't want to change any of this code.

Scaffold::Scaffold(int nColumns, int nLevels)
{
    m_impl = new ScaffoldImpl(nColumns, nLevels);
}
 
Scaffold::~Scaffold()
{
    delete m_impl;
}
 
Scaffold::Scaffold(const Scaffold& other)
{
    m_impl = new ScaffoldImpl(*other.m_impl);
}
 
Scaffold& Scaffold::operator=(const Scaffold& rhs)
{
    if (this != &rhs)
    {
        Scaffold temp(rhs);
        swap(m_impl, temp.m_impl);
    }
    return *this;
}
 
int Scaffold::cols() const
{
    return m_impl->cols();
}

int Scaffold::levels() const
{
    return m_impl->levels();
}

int Scaffold::numberEmpty() const
{
    return m_impl->numberEmpty();
}

int Scaffold::checkerAt(int column, int level) const
{
    return m_impl->checkerAt(column, level);
}
 
void Scaffold::display() const
{
    m_impl->display();
}
 
bool Scaffold::makeMove(int column, int color)
{
    return m_impl->makeMove(column, color);
}
 
int Scaffold::undoMove()
{
    return m_impl->undoMove();
}


