//
//  main.cpp
//  Midterm 1
//
//  Created by Hyerin Lee on 4/22/21.
//


#include <string>
#include<iostream>
#include "test.h"
#include "Hive.h"
void test();
int main() {
    StringList a("spsdfjksla");
   a.eraseEvens();
    a.print();
    test();
    std::cout << '\n' << "All tests succeeded" << std::endl;
}
void test()
{
  Hive h1(3);
  Hive h2(h1);
}
