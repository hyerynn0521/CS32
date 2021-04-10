//
//  Player.hpp
//  Project 1
//
//  Created by Hyerin Lee on 4/5/21.
//

#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED
#include "globals.h"
//#include "Flatulan.h"
#include "City.h"
class City;

class Player
{
  public:
    Player(City *cp, int r, int c);

        // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    int  health() const;
    bool isPassedOut() const;

        // Mutators
    void  preach();
    void  move(int dir);
    void  getGassed();
private:
    City* m_city;
    int   m_row;
    int   m_col;
    int   m_health;
    int   m_age;
};

#endif /* Player_hpp */
