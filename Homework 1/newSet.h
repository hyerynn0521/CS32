//
//  newSet.hpp
//  Homework 1
//
//  Created by Hyerin Lee on 4/13/21.
//

#ifndef newSet_h
#define newSet_h
#include <string>
#include <stdio.h>
using ItemType = std::string;
const int DEFAULT_MAX_ITEMS = 150;
class Set
{
  public:
    Set();
    Set(int size);// Create an empty set (i.e., one with no items).
    Set(const Set& other);
    ~Set();
    
    Set& operator=(const Set& other);
    
    bool empty() const;  // Return true if the set is empty, otherwise false.

    int size() const;    // Return the number of items in the set.

    bool insert(const ItemType& value);
      // Insert value into the set if it is not already present.  Return
      // true if the value is actually inserted.  Leave the set unchanged
      // and return false if the value is not inserted (perhaps because it
      // was already in the set or because the set has a fixed capacity and
      // is full).

    bool erase(const ItemType& value);
      // Remove the value from the set if it is present.  Return true if the
      // value was removed; otherwise, leave the set unchanged and
      // return false.
     
    bool contains(const ItemType& value) const;
      // Return true if the value is in the set, otherwise false.
     
    bool get(int i, ItemType& value) const;
      // If 0 <= i < size(), copy into value the item in the set that is
      // strictly less than exactly i items in the set and return true.
      // Otherwise, leave value unchanged and return false.

    void swap(Set& other);
      // Exchange the contents of this set with the other one.
private:
    ItemType * m_Array;
    int m_Size;
    int m_MaxItems;
    
};


#endif /* newSet_hpp */
