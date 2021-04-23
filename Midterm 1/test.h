//
//  test.hpp
//  Midterm 1
//
//  Created by Hyerin Lee on 4/22/21.
//

#ifndef test_hpp
#define test_hpp
#include <string>
#include <stdio.h>
class StringList
  {
    public:
        // Constructs a StringList with the characters in text
      StringList(std::string text);
      ~StringList();
      void eraseEvens();
      void print();
    private:
      struct Node
      {
        char  value;
        Node* next;
        Node(char v, Node* n) : value(v), next(n) {}
      };
      Node* head;  // points to first Node in the list
  };
#endif /* test_hpp */
