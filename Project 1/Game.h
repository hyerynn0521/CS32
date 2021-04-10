//
//  Game.hpp
//  Project 1
//
//  Created by Hyerin Lee on 4/5/21.
//

#ifndef GAME_INCLUDED
#define GAME_INCLUDED
//#include "globals.h"
#include "City.h"
//#include "Player.h"
//class City;
class Game
{
  public:
        // Constructor/destructor
    Game(int rows, int cols, int nFlatulans);
    ~Game();

        // Mutators
    void play();
    int decodeDirection(char dir);
  private:
    City* m_city;
};
#endif /* Game_hpp */
