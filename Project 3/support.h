//
//  support.hpp
//  Project 3
//
//  Created by Hyerin Lee on 5/13/21.
//
#ifndef support_hpp
#define support_hpp
#include "provided.h"
#include <stdio.h>
bool hasEmpty(const Scaffold&s, int column);
int checkUpRight(const Scaffold& s, int col, int level, int color);
int checkUpLeft(const Scaffold& s, int col, int level, int color);
int checkDownRight(const Scaffold& s, int col, int level, int color);
int checkDownLeft(const Scaffold& s, int col, int level, int color);
int checkDown(const Scaffold& s, int col, int level, int color);
int checkLeft(const Scaffold& s, int col, int level, int color);
int checkUp(const Scaffold& s, int col, int level, int color);
int checkRight(const Scaffold& s, int col, int level, int color);
int rate(const Scaffold& s, int N, int humanColor, int computerColor, int col, int depth);
#endif /* support_hpp */
