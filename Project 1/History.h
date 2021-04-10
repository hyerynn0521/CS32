//
//  History.hpp
//  Project 1
//
//  Created by Hyerin Lee on 4/5/21.
//

#ifndef HISTORY_INCLUDED
#define HISTORY_INCLUDED

#include "globals.h"

class History
    {
      public:
        History(int nRows, int nCols);
        bool record(int r, int c);
        void display() const;
    private:
        int m_Rows;
        int m_Cols;
        char m_History[MAXROWS][MAXCOLS];
    };


#endif /* History_hpp */
