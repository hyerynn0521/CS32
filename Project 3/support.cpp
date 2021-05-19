//
//  support.cpp
//  Project 3
//
//  Created by Hyerin Lee on 5/13/21.
//

#include "support.h"
#include "provided.h"

bool hasEmpty(const Scaffold& s, int column){
    //checks if a chosen column has a empty spot
    //called in smartPlayer algorithm determineBest(Human/Computer)Move to check if a move can be made in a column
    for(int i = s.levels(); i > 0 ; i--){
        if(s.checkerAt(column, i) == VACANT){
            return true;
        }
    }
    return false;
}

int checkUpRight(const Scaffold& s, int col, int level, int color){
    //base case: checker in current position does not match color, or cannot move anymore in this direction
    if((col > s.cols() && level  > s.levels()) || (s.checkerAt(col, level) != color)){
        return 0;
    }
    //if able to move upward right diagonally, recursively call, incrementing the count of checker in a row
    return 1 + checkUpRight(s, col+1, level+1, color);
}
int checkUpLeft(const Scaffold& s, int col, int level, int color){
    //base case: checker in current position does not match color, or cannot move anymore in this direction
    if((col < 0 && level > s.levels()) || (s.checkerAt(col, level) != color)){
        return 0;
    }
    //if able to move upward left diagonally, recursively call, incrementing the count of checker in a row
    return 1 + checkUpLeft(s, col - 1, level + 1, color);
}
int checkDownRight(const Scaffold& s, int col, int level, int color){
    //base case: checker in current position does not match color, or cannot move anymore in this direction
    if((col > s.cols() && level< 0) || (s.checkerAt(col, level) != color)){
        return 0;
    }
    //if able to move downward right diagonally, recursively call, incrementing the count of checker in a row
    return 1 + checkDownRight(s,col+1, level - 1, color);
}
int checkDownLeft(const Scaffold& s, int col, int level, int color){
    //base case: checker in current position does not match color, or cannot move anymore in this direction
    if((col  < 0 && level < 0) || (s.checkerAt(col, level) != color)){
        return 0;
    }
    //if able to move down left diagonally, recursively call, incrementing the count of checker in a row
    return 1 + checkDownLeft(s, col - 1, level - 1, color);
}
int checkRight(const Scaffold& s,  int col, int level, int color){
    //base case: checker in current position does not match color, or cannot move anymore in this direction
    if(col  > s.cols() || s.checkerAt(col, level) != color){
        return 0;
    }
    //if able to move right, recursively call, incrementing the count of checker in a row
    return 1 + checkRight(s, col+1, level, color);
}
int checkLeft(const Scaffold& s, int col, int level, int color){
    //base case: checker in current position does not match color, or cannot move anymore in this direction
    if(col < 0 || s.checkerAt(col, level) != color){
        return 0;
    }
    //if able to move left, recursively call, incrementing the checker in a row
    return 1 + checkLeft(s,col - 1, level, color);
}
int checkUp(const Scaffold& s,int col, int level, int color){
    //base case: checker in current position does not match color, or cannot move anymore in this direction
    if(level  > s.levels() || s.checkerAt(col, level) != color){
        return 0;
    }
    //if able to move up, recursively call, incrementing the checker in a row
    return 1 + checkUp(s, col, level+1, color);
}
int checkDown(const Scaffold& s, int col, int level, int color){
    //base case: checker in current position does not match color, or cannot move anymore in this direction
    if(level < 0 || s.checkerAt(col, level) != color){
        return 0;
    }
    // if able to move down, recursively call, incrementing the checker in a row
    return 1 + checkDown(s, col, level-1, color);
}

int rate(const Scaffold& s, int N, int humanColor, int computerColor, int col, int depth){
    int checker;
    int maxDepth  = s.cols()*s.levels()+1;
    //note: the col parameter passed in indicates a column where the most recent move was made
        for(int i = s.levels(); i > 0; i--){
            //store the color of checker of most recent move
            checker = s.checkerAt(col, i);
            if(checker != VACANT){
                //check in each direction
                //method: helper function that checks in each direction,
                //adds the count in a row of paired directions (left&right, down&up, etc.)
                //subtract one to account for the overlap
                if( checkDown(s, col, i, checker) >= N
                   || checkLeft(s, col, i, checker) + checkRight(s, col, i, checker) - 1 >= N
                   || checkUpRight(s, col, i, checker) + checkDownLeft(s, col, i, checker) - 1 >= N
                   || checkDownRight(s, col, i, checker) + checkUpLeft(s, col, i, checker) - 1 >= N){
                    if(checker == humanColor)
                        return -1*(maxDepth - depth);
                    else if(checker == computerColor)
                        return (maxDepth - depth);
                }
                //if no one won but board is full, mark tied game
                else if(s.numberEmpty() == 0){
                    return 0;
                }
                break;
            }
            
        }
    //if neither win or a tie or a loss
    return -10000;
}




