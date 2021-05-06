//
//  mazequeue.cpp
//  Queue
//
//  Created by Hyerin Lee on 4/26/21.
//
#include <queue>
using namespace std;
#include "mazequeue.h"
class Coord
       {
         public:
           Coord(int r, int c) : m_row(r), m_col(c) {}
           int r() const { return m_row; }
           int c() const { return m_col; }
         private:
           int m_row;
           int m_col;
       };
bool pathExists(char maze[][10], int sr, int sc, int er, int ec);
bool pathExists(char maze[][10], int sr, int sc, int er, int ec){
    // Return true if there is a path from (sr,sc) to (er,ec)
    // through the maze; return false otherwise
    queue<Coord> coordQueue;
    coordQueue.push(Coord(sr, sc));
    maze[sr][sc] = 'e'; // e for encountered
    int r = sr;
    int c = sc;
    while(!coordQueue.empty()){
        if(!coordQueue.empty()){
            r = coordQueue.front().r();
            c = coordQueue.front().c();
        }
        coordQueue.pop();
        if(r == er && c == ec){
            return true;
        }
        
        else{
            if(maze[r+1][c] == '.'){ //SOUTH
                coordQueue.push(Coord(r+1, c));
                maze[r+1][c] = 'e';
            }
            if(maze[r][c-1] == '.'){ //WEST
                coordQueue.push(Coord(r, c-1));
                maze[r][c-1] = 'e';
            }
            if(maze[r-1][c] == '.'){ // NORTH
                coordQueue.push(Coord(r-1, c));
                maze[r-1][c] = 'e';
            }
            if(maze[r][c+1] == '.'){ // EAST
                coordQueue.push(Coord(r, c+1));
                maze[r][c+1] = 'e';
            }
            
        }
    }
    
    
    return false;
}
//stack: (3, 5) (4, 5) (5, 5)
/* char maze[10][10] = {
 0{ 'X','X','X','X','X','X','X','X','X','X' },
 1{ 'X','.','.','e','e','X','.','.','X','X' },
 2{ 'X','.','X','X','e','X','X','.','.','X' },
 3{ 'X','X','X','e','e','e','e','X','.','X' },
 4{ 'X','.','X','X','X','e','X','X','X','X' },
 5{ 'X','.','X','e','e','e','X','.','.','X' },
 6{ 'X','.','.','e','X','e','X','.','.','X' },
 7{ 'X','X','X','X','X','e','X','.','X','X' },
 8{ 'X','.','.','.','.','e','.','.','.','X' },
 9{ 'X','X','X','X','X','X','X','X','X','X' }
};

if (pathExists(maze, 3,5, 8,8))
 cout << "Solvable!" << endl;
else
 cout << "Out of luck!" << endl;*/

/*Push the starting coordinate (sr,sc) onto the coordinate stack and
            update maze[sr][sc] to indicate that the algorithm has encountered
            it (i.e., set maze[sr][sc] to have a value other than '.').
        While the stack is not empty,
        {   Pop the top coordinate off the stack. This gives you the current
                (r,c) location that your algorithm is exploring.
            If the current (r,c) coordinate is equal to the ending coordinate,
                then we've solved the maze so return true!
            Check each place you can move from the current cell as follows:
                If you can move SOUTH and haven't encountered that cell yet,
                    then push the coordinate (r+1,c) onto the stack and update
                    maze[r+1][c] to indicate the algorithm has encountered it.
                If you can move WEST and haven't encountered that cell yet,
                    then push the coordinate (r,c-1) onto the stack and update
                    maze[r][c-1] to indicate the algorithm has encountered it.
                If you can move NORTH and haven't encountered that cell yet,
                    then push the coordinate (r-1,c) onto the stack and update
                    maze[r-1][c] to indicate the algorithm has encountered it.
                If you can move EAST and haven't encountered that cell yet,
                    then push the coordinate (r,c+1) onto the stack and update
                    maze[r][c+1] to indicate the algorithm has encountered it.
        }
        There was no solution, so return false*/
          
