//
//  Table.hpp
//  Project 4
//
//  Created by Hyerin Lee on 6/4/21.
//

#ifndef Table_hpp
#define Table_hpp
#include <string>
#include <vector>
#include <stdio.h>
#include <list>

class Table
{
  public:
    Table(std::string keyColumn, const std::vector<std::string>& columns);
    ~Table();
    bool good() const;
    bool insert(const std::string& recordString);
    void find(std::string key, std::vector<std::vector<std::string>>& records) const;
    int select(std::string query, std::vector<std::vector<std::string>>& records) const;

      // We prevent a Table object from being copied or assigned by
      // making the copy constructor and assignment operator unavailable.
    Table(const Table&) = delete;
    Table& operator=(const Table&) = delete;
  private:
    bool checkColumn(const std::string& column) const;
    bool checkOperator(const std::string& Operator, bool& digitComparison) const;
    void strComparison(const int& keyIndex, const std::string& compare,const std::string& against, std::vector<std::vector<std::string>>& records) const;
    void numComparison(const int& keyIndex, const std::string& compare, const std::string& against, std::vector<std::vector<std::string>>& records, int & invalid) const;
    bool validStr(const std::string& input) const;
    
    std::string m_keyColumn;
    int m_keyIndex;
    std::vector<std::list<std::vector<std::string>>> m_table;
    std::vector<std::string> m_columns;
};



#endif /* Table_hpp */
