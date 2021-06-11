//
//  Table.cpp
//  Project 4
//
//  Created by Hyerin Lee on 6/4/21.
//

#include "Table.h"
#include <functional>
#include <iostream>
#include <cstdlib>
using namespace std;
bool stringToDouble(string s, double& d);
bool stringToDouble(string s, double& d)
    {
        char* end;
        d = std::strtof(s.c_str(), &end);
        return end == s.c_str() + s.size()  &&  !s.empty();
    }
class StringParser
{
  public:
    StringParser(std::string text = "")
    {
        setString(text);
    }

    void setString(std::string text)
    {
        m_text = text;
        m_start = 0;
    }

    bool getNextField(std::string& field);

  private:
    std::string m_text;
    size_t m_start;
};

bool StringParser::getNextField(std::string& fieldText)
{
    m_start = m_text.find_first_not_of(" \t\r\n", m_start);
    if (m_start == std::string::npos)
    {
        m_start = m_text.size();
        fieldText = "";
        return false;
    }
    if (m_text[m_start] != '\'')
    {
        size_t end = m_text.find_first_of(" \t\r\n", m_start+1);
        fieldText = m_text.substr(m_start, end-m_start);
        m_start = end;
        return true;
    }
    fieldText = "";
    for (;;)
    {
        m_start++;
        size_t end = m_text.find('\'', m_start);
        fieldText += m_text.substr(m_start, end-m_start);
        m_start = (end != std::string::npos ? end+1 : m_text.size());
        if (m_start == m_text.size()  ||  m_text[m_start] != '\'')
            break;
        fieldText += '\'';
    }
    return true;
}

Table::Table(std::string keyColumn, const std::vector<std::string>& columns){
    m_keyColumn = keyColumn;
    //hash table size: 997 since prime numbers distribute better
    m_table.resize(997);
    int i = 0;
    for(vector<string>::const_iterator ptr = columns.begin(); ptr < columns.end(); ptr++){
        m_columns.push_back(*ptr);
        if(*ptr == m_keyColumn){
            m_keyIndex = i;
        }
        i++;
            
    }
    
}

bool Table::good() const{
    //if there's no columns, return false
    if(m_columns.empty())
        return false;
    bool hasKey = false;
    vector<string>::const_iterator ptr;
    //check for empty strings as column
    for(ptr = m_columns.begin(); ptr < m_columns.end(); ptr++){
        if(*ptr == "")
            return false;
        if(*ptr == m_keyColumn){
            hasKey = true;
        }
        
    }
    //if key column was not in the columns list, return false
    if(hasKey == false)
        return false;
    vector<string> columns = m_columns;
    sort(columns.begin(), columns.end());
    //sort the columns and if there are any duplicate columns, return false
    for(int i = 1; i < columns.size(); i++){
        if(columns[i-1] == columns[i]){
            return false;
        }
    }
    return true;
}

bool Table::insert(const std::string& recordString){
    if(!(*this).good()){
        return false;
    }
    string field;
    StringParser parse(recordString);
    vector<string> records;
    //get each field of the record and push back in a vector
    while(parse.getNextField(field)){
        records.push_back(field);
    }
    if(records.size() != m_columns.size()){
        return false;
    }
    string key = records.at(m_keyIndex);
    //calculate index by hasing
    int h = hash<string>()(key)%997;
    //add the records vector to the hash table
    m_table.at(h).push_back(records);
    
    
    return true;
}
void Table::find(std::string key, std::vector<std::vector<std::string>>& records) const{
    if(!(*this).good()){
        return;
    }
    
    records.clear();
    //get the index for the given key
    int index = hash<string>()(key)%997;
    list<vector<string>>::const_iterator it;
    //if the record has the same key, push the whole vector into records
    for(it = m_table.at(index).begin(); it != m_table.at(index).end(); it ++){
        if((*it).at(m_keyIndex) == key){
            records.push_back(*it);
        }
    }
}
bool Table::checkColumn(const string& column) const{
    //check for validity of the first token in query
    bool found = false;
    for(vector<string>::const_iterator itr = m_columns.begin(); itr != m_columns.end(); itr++){
        //if there is a matching column in the columns vector, first token is valid
        if(*itr ==column){
            found = true;
            break;
        }
    }
    //if matching column wasn't found in the list of columns, return false
    if(found == false){
        return false;
    }
    return true;
}
bool Table::checkOperator(const std::string& Operator, bool& digitComparison) const{
    //check for validity of the second token, the operator
    //if the operator is any of the numerical comparison operator, return true
    if(Operator == "LT" ||Operator == "lT" ||Operator == "Lt" ||Operator == "lt"||Operator == "LE" ||Operator == "lE" ||Operator == "Le" ||Operator == "le"||Operator == "GT" ||Operator == "gT" ||Operator == "Gt" ||Operator == "gt"||Operator == "GE" ||Operator == "gE" ||Operator == "Ge" ||Operator == "ge"||Operator == "NE" ||Operator == "nE" ||Operator == "Ne" ||Operator == "ne"||Operator == "EQ" ||Operator == "eQ" ||Operator == "Eq" ||Operator == "eq"){
        digitComparison = true;
        return true;
    }
    //if the operator is any of the string comparison operator, return true
    else if(Operator == "<" || Operator == "<=" ||Operator == ">" ||Operator == ">=" ||Operator == "!=" ||Operator == "==" ||Operator == "="){
        digitComparison = false;
        return true;
    }
    //otherwise return false
    return false;
}
int Table::select(std::string query, std::vector<std::vector<std::string>>& records) const{
    if(!(*this).good()){
        return -1;
    }
    records.clear();
    vector<string> queryItems;
    StringParser parse(query);
    string s;
    //push back each token of the query into a vector
    while(parse.getNextField(s)){
        queryItems.push_back(s);
    }
    //if there are more or less than three tokens
    if(queryItems.size() != 3){
        records.clear();
        return -1;
    }

    //if column is invalid
    if(!checkColumn(queryItems.at(0))){
        records.clear();
        return -1;
    }
    bool numberComparison;
    //check if operator is invalid, takes note whether it's a numerical or string comparison
    if(!checkOperator(queryItems.at(1), numberComparison)){
        records.clear();
        return -1;
    }
    int colIndex = 0;
    //find the corresponding index of the column in the first token
    for(int i = 0; i < m_columns.size(); i++){
        if(m_columns.at(i) == queryItems.at(0)){
            colIndex = i;
        }
    }
    //if it's a string comparison
    if(numberComparison == false){
        strComparison(colIndex, queryItems.at(1), queryItems.at(2), records);
        return 0;
    }
    //if it's a numerical comparison
    else if(numberComparison == true){
        //if third token is not valid, return -1
        if(!validStr(queryItems.at(2))){
            records.clear();
            return -1;
        }

        int invalid = 0;
        //do number comparison
        numComparison(colIndex, queryItems.at(1), queryItems.at(2), records, invalid);
        return invalid;
    }
    return 0;
}
bool Table::validStr(const std::string& input) const{
    //checks if the input is a valid string form of a number
    if(input == "" || input == " "){
        return false;
    }
    int dotCount = 0;
    for (char const &c : input) {
        //if there are any other characters besides digit and dot, return false
        if (!std::isdigit(c) && c != '.'){
            return false;
        }
        //keep track of dot counts
        if(c == '.'){
            dotCount ++;
        }
        //if more than one dot, invalid form
        if(dotCount >1){
            return false;
        }
               
    }

    return true;
}
void Table::numComparison(const int& keyIndex, const std::string& compare,const std::string& against, std::vector<std::vector<std::string>>& records, int& invalid) const{
    invalid = 0;
    list<vector<string>>::const_iterator itr;
    //for each entry of hash table
    for(int i = 0; i < m_table.size(); i++){
        //iterate through the list in the bucket
        for(itr = m_table.at(i).begin(); itr != m_table.at(i).end(); itr++){
            //if item has an invalid numerical value, keep track of invalid values
            string current = (*itr).at(keyIndex);
            if(!validStr(current)){
                invalid++;
                continue;
            }
            double current1;
            stringToDouble(current, current1);
            double against1;
            stringToDouble(against, against1);
            //if less than operator,
            if(compare == "LT" || compare == "Lt"|| compare == "lT"|| compare == "lt"){
                //compare accordingly and decide whether to push back
                if(current1 < against1){
                    records.push_back(*itr);
                }

            }
            //if less than or equal operator,
            else if(compare == "LE" || compare == "Le"|| compare == "lE"|| compare == "le"){
                //compare acordingly and decide whether to push back
                if(current1 <= against1){
                    records.push_back(*itr);
                }

            }
            //if greater than operator,
            else if(compare == "GT" || compare == "Gt"|| compare == "gT"|| compare == "gt"){
                //compare acordingly and decide whether to push back
                if(current1 > against1){
                    records.push_back(*itr);
                }

            }
            //if greater than equal operator,
            else if(compare == "GE" || compare == "Ge"|| compare == "gE"|| compare == "ge"){
                //compare acordingly and decide whether to push back
                if(current1 >= against1){
                    records.push_back(*itr);
                }

            }
            //if not equal operator,
            else if(compare == "NE" || compare == "Ne"|| compare == "nE"|| compare == "ne"){
                //compare acordingly and decide whether to push back
                if(current1 != against1){
                    records.push_back(*itr);
                }

            }
            //if equal to operator,
            else if(compare == "EQ" || compare == "Eq"|| compare == "eQ"|| compare == "eq"){
                //compare acordingly and decide whether to push back
                if(current1 == against1){
                    records.push_back(*itr);
                }

            }
        }
    }
    
}
void Table::strComparison(const int& keyIndex, const std::string& compare,const std::string& against, std::vector<std::vector<std::string>>& records) const{
    //compares strings between token and values
    list<vector<string>>::const_iterator itr;
    //iterate through the hash table
    for(int i = 0; i < m_table.size(); i++){
        //iterate through the list at each bucket
        for(itr = m_table.at(i).begin(); itr != m_table.at(i).end(); itr++){
            //determine the right operator and decide whether to push back
            if(compare == "<"){
                if((*itr).at(keyIndex) < against){
                    records.push_back(*itr);
                }
            }
            else if(compare == "<="){
                if((*itr).at(keyIndex) <= against){
                    records.push_back(*itr);
                }
            }
            else if(compare == ">"){
                if((*itr).at(keyIndex) > against){
                    records.push_back(*itr);
                }
            }
            else if(compare == ">="){
                if((*itr).at(keyIndex) >= against){
                    records.push_back(*itr);
                }
            }
            else if(compare == "==" || compare == "="){
                if((*itr).at(keyIndex) == against){
                    records.push_back(*itr);
                }
            }
            else if(compare == "!="){
                if((*itr).at(keyIndex) != against){
                    records.push_back(*itr);
                }
            }
        }
    }
}
Table::~Table(){

}

