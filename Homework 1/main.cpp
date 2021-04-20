//
//  main.cpp
//  Homework 1
//
//  Created by Hyerin Lee on 4/13/21.
//

#include <stdio.h>
#include "Set.h"
#include "AccountSet.h"
    #include <iostream>
    #include <cassert>
    using namespace std;
void test()
      {
          Set ss;
          AccountSet s1;
          s1.add("6789");
          s1.add("yeah");
          s1.add("lol");
          cout << s1.size() << endl;
          AccountSet s2;
          s2.add("1");
          s2.add("5");
          s2.add("7");
          s2.add("9");
          cout << s2.size() << endl;
          s2.print();
          
          assert(s1.size() == 3);
          assert(ss.insert("pita"));
          assert(ss.insert("roti"));
          assert(ss.size() == 2);
          assert(ss.contains("roti"));
          ItemType x = "laobing";
          assert(ss.get(0, x)  &&  x == "roti");
          assert(ss.get(1, x)  &&  x == "pita");
          ss.insert("haha");
          cout << ss.size() << endl;
          ss.erase("roti");
          cout << ss.size() << endl;
          ss.erase("haha");
          ss.erase("pita");
          cout << ss.size() << endl;
          
          s1.print();
      }

    int main()
    {
        test();
                    cout << "Passed all tests" << endl;
        
        
    }
