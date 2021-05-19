//
//  Game.cpp
//  Project 3
//
//  Created by Hyerin Lee on 5/10/21.
//

// Game.cpp

#include "provided.h"
#include "support.h"
#include <iostream>
using namespace std;
class GameImpl
{
  public:
    GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black);
    bool completed(int& winner) const;
    bool takeTurn();
    void play();
    int checkerAt(int c, int r) const;
private:
    Player* m_red;
    Player* m_black;
    Scaffold m_scaffold;
    
    int m_win;
    
};

GameImpl::GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black): m_red(red), m_black(black), m_scaffold(nColumns, nLevels)
{
    if(N < 1)
        exit(0);
    m_win = N;
}

bool GameImpl::completed(int& winner) const
{
    Scaffold s = m_scaffold;
    int recentMove = s.undoMove(); // store most recent move to only check that checker
    for(int i = m_scaffold.levels(); i > 0; i--){ // loop to find the top checker in the most recent column
        int color = m_scaffold.checkerAt(recentMove, i);
        //if the top checker at the column is found(meaning it was the most recent move)
        if(color != VACANT){
            //from that position, check in diagonal, sideways, and up down direction to see if game ended
            if(checkDown(m_scaffold, recentMove, i, color) >= m_win
               || checkLeft(m_scaffold, recentMove, i, color)+checkRight(m_scaffold, recentMove, i, color) - 1>= m_win
               || checkDownRight(m_scaffold, recentMove, i, color)+ checkUpLeft(m_scaffold,recentMove, i, color) - 1 >= m_win
               || checkUpRight(m_scaffold, recentMove, i, color) +checkDownLeft(m_scaffold, recentMove, i, color) - 1 >= m_win){
                winner = color;
                return true;
            }
            //if no winner but board is full, tie game
            else if(m_scaffold.numberEmpty() == 0){
                winner = TIE_GAME;
                return true;
            }
            break;
        }
    }
    return false;
}

bool GameImpl::takeTurn()
{
    int winner = TIE_GAME;
    //if game has ended, return false
    if(completed(winner))
        return false;
    int turn = 1;
    int move;
    int whoseTurn = RED;
    while(!completed(winner)){
        //keep track of turn with a turn int variable
        if(turn%2 == 0){
            whoseTurn = BLACK;
            move = m_black->chooseMove(m_scaffold, m_win, BLACK);
        }
        else {
            whoseTurn = RED;
            move = m_red->chooseMove(m_scaffold, m_win, RED);
        }
        m_scaffold.makeMove(move, whoseTurn);
        //display the scaffold after move has been made
        cout << endl;
        m_scaffold.display();
        turn++;
        //lets user press enter to see the progress of the game
        cout << "Press ENTER to continue..." << endl;
        cin.ignore(10000, '\n');
        
        
       
    }
    return true;

}

void GameImpl::play()
{
    int winner = TIE_GAME;
    cout << "Starting the game..." << endl;
    //display the initial empty scaffold
    m_scaffold.display();
    //take turn playing the game
    takeTurn();
    //determine winner and display appropriate message
    completed(winner);
    if(winner == RED){
        cout << "Player RED won!" << endl;
    }
    else if(winner == BLACK){
        cout << "Player BLACK won!" << endl;
    }
    else
        cout << "Game tied!" << endl;
        
}

int GameImpl::checkerAt(int c, int r) const
{
    return m_scaffold.checkerAt(c, r);
}

//******************** Game functions *******************************

//  These functions simply delegate to GameImpl's functions.
//  You probably don't want to change any of this code.

Game::Game(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    m_impl = new GameImpl(nColumns, nLevels, N, red, black);
}
 
Game::~Game()
{
    delete m_impl;
}
 
bool Game::completed(int& winner) const
{
    return m_impl->completed(winner);
}

bool Game::takeTurn()
{
    return m_impl->takeTurn();
}

void Game::play()
{
    m_impl->play();
}
 
int Game::checkerAt(int c, int r) const
{
    return m_impl->checkerAt(c, r);
}

