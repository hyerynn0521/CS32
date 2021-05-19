//
//  Player.cpp
//  Project 3
//
//  Created by Hyerin Lee on 5/10/21.
//

// Player.cpp

#include "provided.h"
#include "support.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;
int determineBestComputerMove(Scaffold& s, AlarmClock &ac, int N, int color, int& score, int depth = 0);
int determineBestHumanMove(Scaffold& s, AlarmClock &ac, int N, int color, int& score, int depth = 0);



class HumanPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class BadPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class SmartPlayerImpl 
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
  private:
    int m_depth;
    
    
};

int HumanPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    bool invalid = true;
    int col = 0;
    //prompt user to choose move
    cout << "Which column do you choose? ";
    cin >> col;
    //if move is valid, do not go into the loop that prompts for valid move
    if(col > 0 && col <= s.cols() && hasEmpty(s, col) == true)
        invalid = false;
    //if move is invalid, keep prompting the user for valid move until valid move is entered
    while(invalid){
        cout << "Invalid move! ";
        cout << "Which column do you choose? ";
        cin >> col;

        if(col > 0 && col <= s.cols() && hasEmpty(s, col) == true)
            invalid = false;
    }
    return col;
}

int BadPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    //chooses a first empty spot that it finds
    int i = 1;
    for(i = 1; i <= s.cols(); i ++){
        if(hasEmpty(s, i))
            return i;
    }
    
    return i;
}

int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    int score;
    Scaffold copy = s;
    AlarmClock ac(9900);
    return determineBestComputerMove(copy, ac, N, color, score);  
}

int determineBestComputerMove(Scaffold& s, AlarmClock &ac, int N, int color, int& score,int depth){
    vector<int> move, outcome;
    move.clear();
    outcome.clear();


    int result;

    for(int i = 1; i <= s.cols(); i ++){
        //if a move can be made in this column
        if(hasEmpty(s, i)){
            s.makeMove(i, color);
            //rate the scaffold after move has been simulated in that column
            if(color==RED)
                result = rate(s, N, BLACK, color, i, depth);
            else
                result = rate(s, N, RED, color, i, depth);
            if (result >= 0){ // if it's a tie or a win
                move.push_back(i);
                outcome.push_back(result);

            }
            //or if alarmClock is not timed out
            else if(!ac.timedOut()){
                //call determineBestHumanMove recursively and store its return value of bestmove and its score
                if(color == RED){
                    move.push_back(i);
                    determineBestHumanMove(s, ac,  N, BLACK, score, depth + 1);
                    outcome.push_back(score);
                }
                else if(color == BLACK){
                    move.push_back(i);
                    determineBestHumanMove(s, ac, N, RED, score, depth + 1);
                    outcome.push_back(score);
                }
            }
            
            s.undoMove();
        }
    }

    int bestMove = 0;
    int bestOutcome = -1000;
    int currOutcome;
    //loop through the collection of moves and outcomes to determine the best move
    for(size_t j = 0; j < move.size(); j ++){
        currOutcome = outcome.at(j);

        if(currOutcome > bestOutcome){
            bestOutcome = currOutcome;
            bestMove = move.at(j);
        }


    }
    score = bestOutcome;
    return bestMove;
}

int determineBestHumanMove(Scaffold& s, AlarmClock &ac, int N, int color, int& score, int depth){
    vector<int> move, outcome;
    move.clear();
    outcome.clear();


    int result;

    for(int i = 1; i <= s.cols(); i++){
        //if a move can be made in this column
        if(hasEmpty(s, i)){
            s.makeMove(i, color);
            //rate the scaffold after move has been simulated in that column
            if(color==RED)
                result = rate(s, N, color, BLACK, i, depth);
            else
                result = rate(s, N, color, RED, i, depth);

            if(result <= 0 && result != -10000){ // if it's a tie or a win
                move.push_back(i);
                outcome.push_back(result);
            }
            //or if alarmClock is not timed out
            else if(!ac.timedOut()){
                //call determineBestComputerMove recursively and store its return value of bestmove and its score
                if(color == RED){
                    move.push_back(i);
                    determineBestComputerMove(s,ac, N, BLACK, score,depth + 1);
                    outcome.push_back(score);
                }
                else if(color == BLACK){
                    move.push_back(i);
                   determineBestComputerMove(s,ac, N, RED, score,depth + 1);
                    outcome.push_back(score);
                }
            }
            s.undoMove();
        }
    }
    int bestMove = 0;
    int bestOutcome = 1000;
    int currOutcome;
    //loop through the collection of moves and outcomes to determine the best move
    for(size_t j = 0; j < move.size(); j ++){
        currOutcome = outcome.at(j);
        if(currOutcome < bestOutcome){
            bestOutcome = currOutcome;
            bestMove = move.at(j);
        }
    }
    score = bestOutcome;
    return bestMove;
}




//******************** Player derived class functions *************************

//  These functions simply delegate to the Impl classes' functions.
//  You probably don't want to change any of this code.

HumanPlayer::HumanPlayer(string nm)
 : Player(nm)
{
    m_impl = new HumanPlayerImpl;
}
 
HumanPlayer::~HumanPlayer()
{
    delete m_impl;
}
 
int HumanPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

BadPlayer::BadPlayer(string nm)
 : Player(nm)
{
    m_impl = new BadPlayerImpl;
}
 
BadPlayer::~BadPlayer()
{
    delete m_impl;
}
 
int BadPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

SmartPlayer::SmartPlayer(string nm)
 : Player(nm)
{
    m_impl = new SmartPlayerImpl;
}
 
SmartPlayer::~SmartPlayer()
{
    delete m_impl;
}
 
int SmartPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

