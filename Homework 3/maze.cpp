//
//  main.cpp
//  maze
//
//  Created by Hyerin Lee on 5/3/21.
//

#include <iostream>
using namespace std;
bool pathExists(char maze[][10], int sr, int sc, int er, int ec);
int main() {
    char maze[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X' },//0
        { 'X','.','.','.','.','X','.','.','X','X' },//1
        { 'X','.','X','X','.','X','X','.','.','X' },//2
        { 'X','X','X','.','.','.','.','.','.','X' },//3
        { 'X','.','X','X','X','.','X','X','X','X' },//4
        { 'X','.','X','.','.','.','X','.','.','X' },//5
        { 'X','.','.','.','X','.','X','.','.','X' },//6
        { 'X','X','X','X','X','.','X','.','X','X' },//7
        { 'X','.','.','.','.','.','.','.','.','X' },//8
        { 'X','X','X','X','X','X','X','X','X','X' }//9
    };

    if (pathExists(maze, 1,1, 5, 8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}

bool pathExists(char maze[][10], int sr, int sc, int er, int ec){
    if(sr == er && sc == ec){
        return true;
    }
    maze[sr][sc] = 'e';
    if(maze[sr+1][sc] == '.'){ //SOUTH
        if(pathExists(maze, sr+1, sc, er, ec) == true){
            return true;
        }
        
    }
    if(maze[sr][sc-1] == '.'){ //WEST
        if(pathExists(maze, sr, sc-1, er, ec) == true){
            return true;
        }
       
    }
    if(maze[sr-1][sc] == '.'){ // NORTH
        if(pathExists(maze, sr-1, sc, er, ec) == true){
            return true;
        }
        
    }
    if(maze[sr][sc+1] == '.'){ // EAST
        if(pathExists(maze, sr, sc+1, er, ec) == true){
            return true;
        }
       
    }
    return false;
}
/*If the start location is equal to the ending location, then we've
 solved the maze, so return true.
Mark the start location as visted.
For each of the four directions,
 If the location one step in that direction (from the start
     location) is unvisited,
         then call pathExists starting from that location (and
                     ending at the same ending location as in the
                     current call).
              If that returned true,
                  then return true.
Return false.*/
