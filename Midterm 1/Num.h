//
//  test1.hpp
//  Midterm 1
//
//  Created by Hyerin Lee on 4/22/21.
//

#ifndef test1_hpp
#define test1_hpp

#include <stdio.h>
class Num
  {
    public:
      Num(int i) : m_i(i) {}
        // no other constructors are declared
      int geti() const { return m_i; }
      //… other members and implementation details are
        //irrelevant to this problem …
    private:
      int m_i;
  };
#endif /* test1_hpp */
