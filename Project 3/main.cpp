//
//  main.cpp
//  Project 3
//
//  Created by Hyerin Lee on 5/10/21.
//

// main.cpp

#include "provided.h"
#include <string>
#include <iostream>
using namespace std;
void doScaffoldTests();
void doPlayerTests();
void doGameTests();
int main()
{
    /*string name;
    cout << "What's your name?  ";
    getline(cin, name);
    HumanPlayer hp(name);
    SmartPlayer sp("Computer");
    Game g1(4, 3, 3, &hp, &sp);
    g1.play();
    cout << endl << "This time I'll go first." << endl;
    Game g2(4, 3, 3, &sp, &hp);
    g2.play();*/
    
    SmartPlayer human("hyerin");
    HumanPlayer bad("seul");
    
    
    Game game(10, 1, 4, &human, &bad);
    game.play();
    

    
}



