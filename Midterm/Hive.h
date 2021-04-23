//
//  Hive.hpp
//  Midterm 1
//
//  Created by Hyerin Lee on 4/22/21.
//

#ifndef Hive_hpp
#define Hive_hpp
#include "Num.h"
#include <stdio.h>
class Hive
  {
    public:
      Hive(int b);
      ~Hive();
      Hive(const Hive& other);
      void print();
     // … other public members are not shown here …
    private:
      Num* m_num;
      int m_bb;
      int* m_bees;
  };
#endif /* Hive_hpp */
