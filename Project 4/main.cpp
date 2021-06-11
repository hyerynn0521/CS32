//
//  main.cpp
//  Project 4
//
//  Created by Hyerin Lee on 6/4/21.
//

#include <iostream>
#include "Table.h"
#include <vector>
#include <string>
#include <iostream>
#include <functional>
using namespace std;
#include <cassert>
void spec1();
void spec2();
void spec3();
void spec4();
void spec5();
void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
void test7();
void test8();
void test9();
int main() {
    bool r = " " < "5.00";
    cout << r << endl;
    spec1();
    spec2();
    spec3();
    spec4();
    spec5();
    test1();
    test2();
    test3();
    test4();
    //test5();
    test6();
    test7();
    test8();
    test9();
    
}

void spec1(){
        std::vector<std::string> cols = {
                "customer", "product", "price", "location"
            };
            Table t("customer", cols);
            assert(t.good());
            assert(t.insert("Patel 12345 42.54 Westwood"));
            assert(t.insert("O'Reilly 34567     4.99 Westwood   "));
            assert(t.insert("   Hoang  12345 30.46 'Santa Monica' "));
            assert(t.insert("Patel\t67890\t142.75  \t \t\t  \tHollywood"));
            assert( ! t.insert("Figueroa 54321 59.95"));
        std::cout <<"passed" << std::endl;
}
void spec2(){
    std::vector<std::string> cols = {
            "customer", "product", "price", "location"
        };
        Table t("customer", cols);
        assert(t.good());
        assert(t.insert("Patel 12345 42.54 Westwood"));
        assert(t.insert("O'Reilly 34567     4.99 Westwood   "));
        assert(t.insert("   Hoang  12345 30.46 'Santa Monica' "));
        assert(t.insert("Patel\t67890\t142.75  \t \t\t  \tHollywood"));
        assert( ! t.insert("Figueroa 54321 59.95"));
    vector<vector<string>> v;
        t.find("Patel", v);
        assert(v.size() == 2);
        vector<vector<string>> expected = {
            { "Patel", "12345", "42.54", "Westwood" },
            { "Patel", "67890", "142.75", "Hollywood" }
        };
        assert((v[0] == expected[0]  &&  v[1] == expected[1])  ||
               (v[0] == expected[1]  &&  v[1] == expected[0]) );
    std::cout <<"passed" << std::endl;
}
void spec3(){
    std::vector<std::string> cols = {
            "customer", "product", "price", "location"
        };
        Table t("customer", cols);
        assert(t.good());
        assert(t.insert("Patel 12345 42.54 Westwood"));
        assert(t.insert("O'Reilly 34567     4.99 Westwood   "));
        assert(t.insert("   Hoang  12345 30.46 'Santa Monica' "));
        assert(t.insert("Patel\t67890\t142.75  \t \t\t  \tHollywood"));
        assert( ! t.insert("Figueroa 54321 59.95"));
    std::cout <<"passed" << std::endl;
    vector<vector<string>> v;
    assert(t.select("location < Westwood", v) == 0);
    assert(v.size() == 2);
    vector<vector<string>> expected = {
        { "Hoang", "12345", "30.46", "Santa Monica" },
        { "Patel", "67890", "142.75", "Hollywood" }
    };
    assert((v[0] == expected[0]  &&  v[1] == expected[1])  ||
           (v[0] == expected[1]  &&  v[1] == expected[0]) );
    std::cout <<"passed" << std::endl;
}
void spec4(){
    vector<string> cols = { "item name", "price" };
    Table t("item name", cols);
    assert(t.good());
    assert(t.insert("'chocolate bar' 1.69"));
    assert(t.insert("coffee 7.99"));
    assert(t.insert("hummus 3.49"));
    vector<vector<string>> v;
    assert(t.select("price LT 5", v) == 0);
    assert(v.size() == 2);  // chocolate bar and hummus
    assert(t.insert("pretzels 1.W9"));
    assert(t.select("price LT H", v) == -1);
    assert(v.size() == 0);
    assert(t.select("price LT 5", v) == 1);  // 1 because pretzels 1.W9
    assert(v.size() == 2);  // chocolate bar and hummus
    std::cout <<"passed" << std::endl;
}
void spec5(){
   vector<string> cols = { "N", "Z" };
    Table t("Z", cols);
    assert(t.good());
    assert(t.insert("UCLA 90095"));
    assert(t.insert("Caltech 91125"));
    vector<vector<string>> v;
    t.find("90095", v);
    assert(v.size() == 1);
    assert(v[0][0] == "UCLA"  &&  v[0][1] == "90095");
    assert(t.select("Z > 90210", v) == 0);
    int size = v.size();
    assert(v.size() == 1);
    assert(v[0][0] == "Caltech"  &&  v[0][1] == "91125");
    //vector<vector<string>> v;
    vector<string> uclacols = { "last name", "first name", "major", "UID", "GPA" };
    Table ucla("UID", uclacols);
    assert(ucla.good());
    assert(ucla.insert("Bruin Jose 'COG SCI' 304567890 3.4"));
    assert(ucla.insert("Bruin Josephine 'COM SCI' 605432109 3.8"));
    assert(ucla.insert("Trojan Tommy LOSING 000000000 1.7"));
      // Troy brought a wooden horse full of Greek soldiers inside the
      // city walls and lost the Trojan War.  How strange to look up to
      // gullible losers as role models.
    assert(ucla.select("GPA GE 3.2", v) == 0);
    assert(v.size() == 2);
    assert(v[0][0] == v[1][0]  &&  v[0][1] != v[1][1]);

    cout << "DONE" << endl;
}
void test1()
{
    vector<string> cols = { "N", "Z" };
    Table t("Z", cols);
    assert(t.good());
    assert(t.insert("UCLA 90095"));
    assert(t.insert("Caltech 91125"));
    vector<vector<string>> v;
    t.find("90095", v);
    assert(v.size() == 1);
    assert(v[0][0] == "UCLA"  &&  v[0][1] == "90095");
    assert(t.select("Z > 90210", v) == 0);
    assert(v.size() == 1);
    assert(v[0][0] == "Caltech"  &&  v[0][1] == "91125");
    cout << "DONE" << endl;
}
void test2()
{
    vector<string> cols = { "N", "Z" };
    Table t("Z", cols);
    assert(t.good());
    assert(t.insert("UCLA 90095"));
    assert(t.insert("Caltech 91125"));
    assert(t.insert("Caltech 91125"));
    vector<vector<string>> v;
    t.find("91125", v);
    assert(v.size() == 2);
    assert(t.select("Z > 90210", v) == 0);
    assert(v.size() == 2);
    assert(t.insert("  Berk 333K"));
    assert(t.insert("  UCR 3X33"));
    assert(t.select("Z LT 95210", v) == 2);
    assert(v.size() == 3);
    assert(t.select("Z GT 95210", v) == 2);
    assert(v.size() == 0);
    assert(t.select("Z EQ 95210", v) == 2);
    assert(v.size() == 0);
    assert(t.select("Z EQ 333K", v) == -1);
    assert(t.select("Z EQ 91125", v) == 2);
    assert(v.size() == 2);
    assert(t.select("Z EQ 91125", v) == 2);
    assert(t.select("Z NE 91125", v) == 2);
    assert(v.size() == 1);
    assert(t.insert("UCI .333"));
    assert(t.select("Z GE .333", v) == 2);
    assert(v.size() == 4);
    assert(t.select("Z LE 99999", v) == 2);
    assert(v.size() == 4);
    assert(t.select("N < Z", v) == 0);
    assert(v.size() == 6);
    assert(t.select("N = U", v) == 0);
    assert(v.size() == 0);
    assert(t.select("N == U", v) == 0);
    assert(v.size() == 0);
    assert(t.select("N == UCR", v) == 0);
    assert(v.size() == 1);
    cout << "DONE" << endl;
}
void test3(){
    vector<string> goodtest1_v = {"column1", "column2"};
    Table goodtest1("notcolumnname", goodtest1_v);
    assert(!goodtest1.good());
    assert(!goodtest1.insert("one two"));
    vector<vector<string>> goodtest1_w;
    goodtest1.find("column1", goodtest1_w);
    assert(goodtest1_w.empty());
    assert(goodtest1.select("idk", goodtest1_w) == -1);
        
    vector<string> goodtest2_v;
    Table goodtest2("any", goodtest2_v);
    assert(!goodtest2.good());
    assert(!goodtest2.insert("one two"));
        
    vector<string> goodtest3_v = {"duplicate", "duplicate"};
    Table goodtest3("duplicate", goodtest3_v);
    assert(!goodtest3.good());
    assert(!goodtest3.insert("one two"));
    cout << "DONE" << endl;

}
void test4(){
    vector<string> friends = { "Name", "Birthday", "Phone", "FavColor" };
        Table myFriends("Name", friends);
        assert(myFriends.good());
        assert(myFriends.insert("Patty 0423 1234567 pink"));
        assert(myFriends.insert("Monica            0223 12435235 blue"));
        assert(myFriends.insert("   Natalie  1225 12481241       'light purple'"));
        assert(myFriends.insert("Matthew 0312        14685343 \t\t\t black"));
        vector<vector<string>> records;
        myFriends.find("Natalie", records);
        assert(records.size() == 1);
        myFriends.find("125451", records);
        assert(records.size() == 0);
        vector<vector<string>> anotherVector;
        assert(myFriends.select("name = Natale", anotherVector) == -1);
        assert(myFriends.select("Birthday on Christmas", anotherVector) == -1);
        assert(myFriends.select("Phone GT ''", anotherVector) == -1);
        assert(myFriends.select("Birthday eq 0423", anotherVector) == 0);
        assert(anotherVector.size() == 1);
        assert(myFriends.select("FavColor > apricot", anotherVector) == 0);
        assert(anotherVector.size() == 4);
        assert(myFriends.insert("Patty\t\t 0734 1455345 orange"));
        myFriends.find("Patty", records);
        assert(records.size() == 2);
        assert(!myFriends.insert("Patrick 0222 124125125"));
        assert(myFriends.insert("Brad 0812 1423521 brown"));
        assert(myFriends.insert("Chad 0118 1253463 red"));
        assert(myFriends.insert("'Maddy Tom' 1124 12354632 indigo"));
        myFriends.find("Maddy", records);
        assert(records.size() == 0);
        myFriends.find("Maddy Tom", records);
        assert(records.size() == 1);
        assert(myFriends.select("Phone gT 1", anotherVector) == 0);
        assert(anotherVector.size() == 8);
        assert(myFriends.insert("Frank December07 12435233 charcoal"));
        assert(myFriends.insert("Phil 12December 12343523 yellow"));
        assert(myFriends.select("Birthday LT 12512356", anotherVector) == 2);
        assert(anotherVector.size() == 8);
    cout << "DONE" << endl;

}
void test5(){
    vector<string> cols = {
                    "customer", "product", "price", "location"
                };
                Table t("customer", cols);
                assert(t.good());
                assert(t.insert("Patel 12345 42.54 Westwood"));
                assert(t.insert("O'Reilly 34567     4.99 Westwood   "));
                assert(t.insert("   Hoang  12345 30.46 'Santa Monica' "));
                assert(t.insert("Patel\t67890\t142.75  \t \t\t  \tHollywood"));
                assert( ! t.insert("Figueroa 54321 59.95"));
            vector<vector<string>> v;
            assert(t.select("product = 12345 location != Westwood", v)==-1);
            assert(t.select("location =  Westwood | Hollywood )", v)==-1);
            assert(t.select("(product = Xi) & ( | )", v)==-1);
            assert(t.select(") product = Jiang (", v)==-1);
            assert(t.select("( ( customer = Mao ) )", v)==0);
            assert(t.select("product != me & ( location > me | product < biden )", v)==0);
            assert(t.select("product = 'O''Reilly'", v)==0);
            assert(t.select("customers > Hoang | product < T", v)==-1);
            assert(t.select("&", v)==-1);
            assert(t.select("(", v)==-1);
            assert(t.select("()", v)==-1);
            assert(t.select("( )", v)==-1);
            assert(t.select("customer = Patel & product GT 12345", v)==0);
            assert(v.size()==1 && v[0][0]=="Patel" && v[0][1]=="67890" && v[0][2]=="142.75" && v[0][3]=="Hollywood");
            assert(t.select("customer != Patel & ( location == Westwood | price gT 30 )", v)==0);
            assert(v.size()==2 && v[1][0]=="O'Reilly" && v[1][1]=="34567" && v[1][2]=="4.99" && v[1][3]=="Westwood" && v[0][0]=="Hoang" && v[0][1]=="12345" && v[0][2]=="30.46" && v[0][3]=="Santa Monica");
            assert(t.select("customer '=' Biden | ( product != 12345 & product le 67799 )", v)==0);
            assert(v.size()==1 && v[0][0]=="O'Reilly" && v[0][1]=="34567" && v[0][2]=="4.99" && v[0][3]=="Westwood");
            assert(t.select("customer = Patel", v)==0);
            assert(v.size()==2 && v[0][0]=="Patel" && v[0][1]=="12345" && v[0][2]=="42.54" && v[0][3]=="Westwood" && v[1][0]=="Patel" && v[1][1]=="67890" && v[1][2]=="142.75" && v[1][3]=="Hollywood");
            assert(t.select("( customer = Patel ')'", v)==0);
            assert(v.size()==2 && v[0][0]=="Patel" && v[0][1]=="12345" && v[0][2]=="42.54" && v[0][3]=="Westwood" && v[1][0]=="Patel" && v[1][1]=="67890" && v[1][2]=="142.75" && v[1][3]=="Hollywood");
            assert(t.select("( location == Westwood | location == Hollywood ) '&' price LT 100", v)==0);
            assert(v.size()==2 && v[1][0]=="O'Reilly" && v[1][1]=="34567" && v[1][2]=="4.99" && v[1][3]=="Westwood" && v[0][0]=="Patel" && v[0][1]=="12345" && v[0][2]=="42.54" && v[0][3]=="Westwood");
            assert(t.select("price GE 20  &  location != Westwood", v)==0);
            assert(v.size()==2 && v[1][0]=="Hoang" && v[1][1]=="12345" && v[1][2]=="30.46" && v[1][3]=="Santa Monica" && v[0][0]=="Patel" && v[0][1]=="67890" && v[0][2]=="142.75" && v[0][3]=="Hollywood");
            cout<<"Passed"<<endl;

}
void test6(){
    vector<string> cols = {
                "customer", "product", "price", "location"
            };
            Table t("customer", cols);
            assert(t.good());
        
            assert(t.insert("Patel 12345 42.54 Westwood"));
            assert(t.insert("O'Reilly 34567     4.99 Westwood   "));
            assert(t.insert("   Hoang  12345 30.46 'Santa Monica' "));
            assert(t.insert("Patel\t67890\t142.75  \t \t\t  \tHollywood"));
            assert( ! t.insert("Figueroa 54321 59.95"));
         
        vector<vector<string>> v;
            t.find("Patel", v);
            assert(v.size() == 2);
            vector<vector<string>> expected = {
                { "Patel", "12345", "42.54", "Westwood" },
                { "Patel", "67890", "142.75", "Hollywood" }
            };
            assert((v[0] == expected[0]  &&  v[1] == expected[1])  ||
                   (v[0] == expected[1]  &&  v[1] == expected[0]) );
        assert(t.select("location < Westwood", expected)==0);
        assert(t.select("location     '<'  'Westwood'", expected)==0);
        assert(t.select("'location' < 'Westwood'", expected)==0);
        assert(t.select("customer != 'O''Reilly'", expected)==0);
        assert(t.select("customer = Patel", expected)==0);
        assert(t.select("product != 12345", expected)==0);
        assert(t.select("Hollywood = location", expected)==-1);
        assert(t.select("price is expensive", expected)==-1);
        assert(t.select("location = Santa Monica", expected)==-1);
        assert(t.select("price GT ''", expected)==-1);
        assert(t.select("price GT 100K", expected)==-1);
        assert(t.select("location = 'Santa Monica'", expected)==0);
        assert(t.select("product == 12345", expected)==0);
        assert(t.select("product != 00012345", expected)==0);
        assert(t.select("product EQ 12345", expected)==0);
        assert(t.select("product EQ 00012345", expected)==0);
        assert(t.select("product < 900", expected)==0);
        assert(t.select("product GT 900", expected)==0);
        expected.clear();
        assert(t.select("customer < 'O''Reilly'", expected)==0);
        assert(expected[0][0]=="Hoang" && expected[0][1]=="12345" && expected[0][2]=="30.46" && expected[0][3]=="Santa Monica" && expected.size()==1);
        assert(t.select("customer <= 'O''Reilly'", expected)==0);


        assert(expected[0][0]=="Hoang" && expected[0][1]=="12345" && expected[0][2]=="30.46" && expected[0][3]=="Santa Monica" && expected[1][0]=="O'Reilly" && expected[1][1]=="34567" && expected[1][2]=="4.99" && expected[1][3]=="Westwood" && expected.size()==2);
        assert(t.select("customer > Patel", expected)==0);
        assert(expected.empty());
        assert(t.select("customer >= Patel", expected)==0);
        assert(expected[0][0]=="Patel" && expected[0][1]=="12345" && expected[0][2]=="42.54" && expected[0][3]=="Westwood" && expected[1][0]=="Patel" && expected[1][1]=="67890" && expected[1][2]=="142.75" && expected[1][3]=="Hollywood" && expected.size()==2);
        assert(t.select("customer != Patel", expected)==0);
        assert(expected[0][0]=="Hoang" && expected[0][1]=="12345" && expected[0][2]=="30.46" && expected[0][3]=="Santa Monica" && expected[1][0]=="O'Reilly" && expected[1][1]=="34567" && expected[1][2]=="4.99" && expected[1][3]=="Westwood" && expected.size()==2);
        assert(t.select("customer == Hoang", expected)==0);
        assert(expected[0][0]=="Hoang" && expected[0][1]=="12345" && expected[0][2]=="30.46" && expected[0][3]=="Santa Monica" && expected.size()==1);
        assert(t.select("customer = Hoang", expected)==0);
        assert(expected[0][0]=="Hoang" && expected[0][1]=="12345" && expected[0][2]=="30.46" && expected[0][3]=="Santa Monica" && expected.size()==1);
        vector<string> x={"num","fname", "lname"};
        Table t1("num", x);
        assert(t1.good());
        assert(t1.insert("0TT1 George Washington"));
        assert(t1.insert("4.6 Joe Biden"));
        assert(t1.select("num Lt 046", expected)==1);
        assert(expected[0][0]=="4.6" && expected[0][1]=="Joe" && expected[0][2]=="Biden" && expected.size()==1);
        assert(t1.select("num LE 4.60", expected)==1);
        assert(expected[0][0]=="4.6" && expected[0][1]=="Joe" && expected[0][2]=="Biden" && expected.size()==1);
        assert(t1.insert("45 Donald Trump"));
        assert(t1.select("num GT 4.60000", expected)==1);
        assert(expected[0][0]=="45" && expected[0][1]=="Donald" && expected[0][2]=="Trump" && expected.size()==1);
        assert(t1.select("num ge 4.6", expected)==1);
        assert(expected[1][0]=="45" && expected[1][1]=="Donald" && expected[1][2]=="Trump" && expected[0][0]=="4.6" && expected[0][1]=="Joe" && expected[0][2]=="Biden" && expected.size()==2);
        assert(t1.select("num Ne 45", expected)==1);
        assert(expected[0][0]=="4.6" && expected[0][1]=="Joe" && expected[0][2]=="Biden" && expected.size()==1);
        assert(t1.select("num eQ 4.6", expected)==1);
        assert(expected[0][0]=="4.6" && expected[0][1]=="Joe" && expected[0][2]=="Biden" && expected.size()==1);
        vector<string> v1={"name", "year"};
        Table t2("year", v1);
        assert(t2.insert("Biden 1946"));
        assert(t2.insert("Clinton 1955"));
        assert(t2.insert("Obama 1965"));
        assert(t2.select("name < Obama", expected)==0);
        assert(expected[1][0]=="Biden" && expected[1][1]=="1946" && expected.size()==2 && expected[0][0]=="Clinton" && expected[0][1]=="1955");
        assert(t2.select("name <= Clinton", expected)==0);
        assert(expected[1][0]=="Biden" && expected[1][1]=="1946" && expected.size()==2 && expected[0][0]=="Clinton" && expected[0][1]=="1955");
        assert(t2.select("name > Biden", expected)==0);
        assert(expected[1][0]=="Obama" && expected[1][1]=="1965" && expected.size()==2 && expected[0][0]=="Clinton" && expected[0][1]=="1955");
        assert(t2.select("name >= Obama", expected)==0);
        assert(expected[0][0]=="Obama" && expected[0][1]=="1965" && expected.size()==1);
        assert(t2.select("name != Biden", expected)==0);
        assert(expected[1][0]=="Obama" && expected[1][1]=="1965" && expected.size()==2 && expected[0][0]=="Clinton" && expected[0][1]=="1955");
        assert(t2.select("name == Obama", expected)==0);
        assert(expected[0][0]=="Obama" && expected[0][1]=="1965" && expected.size()==1);
        assert(t2.select("name = Obama", expected)==0);
        assert(expected[0][0]=="Obama" && expected[0][1]=="1965" && expected.size()==1);
        vector<string> v5={"name", "year"};
        Table t3("name", v5);
        assert(t3.insert("Biden 78"));
        assert(t3.insert("Obama 00060.000"));
        assert(t3.insert("Carter 96"));
        assert(t3.insert("Trump 0safkasfivk"));
        assert(t3.select("year lt 000061.0000", expected)==1);
        assert(expected[0][0]=="Obama" && expected[0][1]=="00060.000" && expected.size()==1);
        assert(t3.select("year Le 60.0", expected)==1);
        assert(expected[0][0]=="Obama" && expected[0][1]=="00060.000" && expected.size()==1);
        assert(t3.select("year gt 95", expected)==1);
        assert(expected[0][0]=="Carter" && expected[0][1]=="96" && expected.size()==1);
        assert(t3.select("year gE 96.00", expected)==1);
        assert(expected[0][0]=="Carter" && expected[0][1]=="96" && expected.size()==1);
        assert(t3.insert("Bush ijlajfla"));
        assert(t3.insert("Reagan jqirjqoi"));
        assert(t3.select("year NE 78", expected)==3);
        assert(expected[0][0]=="Obama" && expected[0][1]=="00060.000" && expected[1][0]=="Carter" && expected[1][1]=="96" && expected.size()==2);
        assert(t3.select("year eq 60", expected)==3);
        assert(expected[0][0]=="Obama" && expected[0][1]=="00060.000" && expected.size()==1);
        cout<<"Nice!!"<<endl;
}
void test7(){
    vector<string> usccols = { "last name", "first name", "frat", "UID", "GPA" };
        Table usc("frat", usccols);
        vector<vector<string>> findchecker;
        assert(usc.good());
        assert(usc.insert("spoiled kid akpsi 6055050 2.1"));
        usc.find("akpsi", findchecker);
        assert(findchecker.size() == 1);
        usc.find("dsp", findchecker);
        assert(findchecker.size() == 0);
        usc.find("6055050", findchecker);
        assert(findchecker.size() == 0);
        usc.find("akpsii", findchecker);
        assert(findchecker.size() == 0);
        usc.find("", findchecker);
        assert(findchecker.size() == 0);
        assert(usc.insert("spoiled kid akpsi 6055050 2.1"));
        usc.find("akpsi", findchecker);
        assert(findchecker.size() == 2);
        assert(usc.insert("spoiled jock akpsi 6055050 2.1"));
        usc.find("akpsi", findchecker);
        assert(findchecker.size() == 3);
        assert(usc.insert("refined man dsp 6055050 4.0"));
        usc.find("dsp", findchecker);
        assert(findchecker.size() == 1);
        assert(usc.select("frat GE 4.0", findchecker) == 4);
        assert(findchecker.size() == 0);
        assert(usc.select("frat is 4.0", findchecker) == -1);
        assert(findchecker.size() == 0);
        assert(usc.select("frat GED 4.0", findchecker) == -1);
        assert(findchecker.size() == 0);
        assert(usc.select("frat 4.0", findchecker) == -1);
        assert(findchecker.size() == 0);
        assert(usc.select("frat GE 4.0 rawr", findchecker) == -1);
        assert(findchecker.size() == 0);
        assert(usc.select("GPA GE 4.0rawr", findchecker) == -1);
        assert(findchecker.size() == 0);
        assert(usc.select("", findchecker) == -1);
        assert(findchecker.size() == 0);
        assert(usc.select("yooooooooooooo", findchecker) == -1);
        assert(findchecker.size() == 0);
        assert(usc.select("parties GE 40", findchecker) == -1);
        assert(findchecker.size() == 0);
        assert(usc.select("frat > b", findchecker) == 0);
        assert(findchecker.size() == 1);
        assert(usc.select("frat > a", findchecker) == 0);
        assert(findchecker.size() == 4);
        assert(usc.select("frat > akpsi", findchecker) == 0);
        assert(findchecker.size() == 1);
        assert(usc.select("frat != akps", findchecker) == 0);
        assert(findchecker.size() == 4);
        assert(usc.select("frat != akpsi", findchecker) == 0);
        assert(findchecker.size() == 1);
        assert(usc.select("frat == akpsi", findchecker) == 0);
        assert(findchecker.size() == 3);
        assert(usc.select("frat = akpsi", findchecker) == 0);
        assert(findchecker.size() == 3);
        assert(usc.select("frat >= akpsi", findchecker) == 0);
        assert(findchecker.size() == 4);
        assert(usc.select("frat <= akpsi", findchecker) == 0);
        assert(findchecker.size() == 3);
        assert(usc.select("frat < akpsi", findchecker) == 0);
        assert(findchecker.size() == 0);
        assert(usc.select("frat <= dsp", findchecker) == 0);
        assert(findchecker.size() == 4);
        assert(usc.select("frat < dsp", findchecker) == 0);
        assert(findchecker.size() == 3);
        assert(usc.select("frat < stephencurry", findchecker) == 0);
        assert(findchecker.size() == 4);
        assert(usc.select("frat <= stephencurry", findchecker) == 0);
        assert(findchecker.size() == 4);
        assert(usc.select("GPA lT 4.0", findchecker) == 0);
        assert(findchecker.size() == 3);
        assert(usc.select("GPA LT 2.1", findchecker) == 0);
        assert(findchecker.size() == 0);
        assert(usc.select("GPA Lt 2.2", findchecker) == 0);
        assert(findchecker.size() == 3);
        assert(usc.select("GPA lt 2.5", findchecker) == 0);
    assert(findchecker.size() == 3);
    assert(usc.select("GPA Le 4.0", findchecker) == 0);
    assert(findchecker.size() == 4);
    assert(usc.select("GPA le 4.0", findchecker) == 0);
    assert(findchecker.size() == 4);
    assert(usc.select("GPA LE 4.0", findchecker) == 0);
    assert(findchecker.size() == 4);
    assert(usc.select("GPA lE 4.0", findchecker) == 0);
    assert(findchecker.size() == 4);
    assert(usc.select("GPA GT 0", findchecker) == 0);
    assert(findchecker.size() == 4);
    assert(usc.select("GPA gt 2.0", findchecker) == 0);
    assert(findchecker.size() == 4);
    assert(usc.select("GPA gT 2.1", findchecker) == 0);
    assert(findchecker.size() == 1);
    assert(usc.select("GPA Gt 4.0", findchecker) == 0);
    assert(findchecker.size() == 0);
    assert(usc.select("GPA GE 2.1", findchecker) == 0);
    assert(findchecker.size() == 4);
    assert(usc.select("GPA ge 4.0", findchecker) == 0);
    assert(findchecker.size() == 1);
    assert(usc.select("GPA Ge 4.0", findchecker) == 0);
    assert(findchecker.size() == 1);
    assert(usc.select("GPA gE 2.1", findchecker) == 0);
    assert(findchecker.size() == 4);
    assert(usc.select("GPA NE 2.1", findchecker) == 0);
    assert(findchecker.size() == 1);
    assert(usc.select("GPA ne 4.0", findchecker) == 0);
    assert(findchecker.size() == 3);
    assert(usc.select("GPA Ne 2.0", findchecker) == 0);
    assert(findchecker.size() == 4);
    assert(usc.select("GPA nE 4.7", findchecker) == 0);
    assert(findchecker.size() == 4);
    assert(usc.select("GPA EQ 4.7", findchecker) == 0);
    assert(findchecker.size() == 0);
    assert(usc.select("GPA eq 4.0", findchecker) == 0);
    assert(findchecker.size() == 1);
    assert(usc.select("GPA Eq 2.1", findchecker) == 0);
    assert(findchecker.size() == 3);
    assert(usc.select("GPA eQ 2.1", findchecker) == 0);
    assert(findchecker.size() == 3);
    assert(usc.insert("Ivan Yau dsp 6055050 ASS"));
    assert(usc.select("GPA eQ 2.1", findchecker) == 1);
    assert(findchecker.size() == 3);
    assert(usc.insert("Ivan Yau dsp 6055050 4.YEET"));
    assert(usc.select("GPA eQ 2.1", findchecker) == 2);
    assert(findchecker.size() == 3);
    assert(usc.insert("Ivan Yau dsp 6055050 4.08347YEET"));
    assert(usc.select("GPA eQ 2.1", findchecker) == 3);
    assert(findchecker.size() == 3);
 
    vector<string> emptycols = {""};
    Table empty("", emptycols);
    assert(!empty.good());
 
    vector<string> emptyitem = { "last name", "first name", "", "UID", "GPA" };
    Table emptycol("first name", emptyitem);
    assert(!emptycol.good());
 
    vector<string> dupe = { "last name", "last name", "frat", "UID", "GPA" };
    Table dupl("last name", dupe);
    assert(!dupl.good());
 
    vector<string> nokey = { "frat", "UID", "GPA" };
    Table keygone("last name", nokey);
    assert(!keygone.good());
    cout << "DONE" << endl;
}
void test8(){
    vector<string> cols = {"customer", "product", "price", "location"};
    Table t("customer", cols);
    Table emptyRecord("customer", cols);
    std::vector<std::vector<std::string>> testSelect;
    assert(t.good());
    vector<vector<string>> eR;
    assert(emptyRecord.insert("' '  ' '  ' '  ' '"));  //has four fields, so valid
    emptyRecord.find(" ", eR);
    assert(eR.size() == 1);
    vector<string> theEmptyFields = { " ", " ", " ", " " };
    assert(eR[0] == theEmptyFields);
    emptyRecord.find("", eR);  //whether there's a space or not in between the quotes matters
    assert(eR.size() == 0);
    assert(emptyRecord.select("price LT ' '", testSelect) == -1);
     
    
    assert(t.good());
    Table t1("name", cols); //key isn't in cols
    assert(!t1.good());
    assert(t.insert("Patel 12345 42.54 Westwood"));
    assert(t.insert("O'Reilly 34567     4.99 Westwood   "));
    assert(t.insert("   Hoang  12345 30.46 'Santa Monica' "));
    assert(t.insert("Patel\t67890\t142.75  \t \t\t  \tHollywood"));
    assert(!t.insert("Figueroa 54321 59.95")); //not the right amount of fields
    assert(!t.insert("")); //not the right amount of fields
    assert(t.insert("'Baba O''Riley' 58201\n12.34 'Cool Hip City'")); //playing around with single quote
    assert(t.insert("       Alexa       '03510'77.77       'Outer Space City'       "));
    assert(t.insert("'Maca-roni'\r72945\t1.25\n'San Jose'"));
    assert(!t.insert("'Maca-roni'\r72945\t1.25\nSan Jose"));
    std::vector<std::vector<std::string>> v;
    t.find("Alexa", v);
    assert(v.size() == 1);
    std::vector<std::string> hasAlexa = { "Alexa", "03510", "77.77", "Outer Space City" };
    assert(v[0] == hasAlexa);
    assert(t.insert("Alexa '03510'77.77 'Outer Space City'"));
    t.find("Alexa", v);
    assert(v.size() == 2);
    assert(v[0] == hasAlexa && v[1] == hasAlexa);
     
     
    
    assert(t.select("price < 5.00", testSelect) == 0);  // '<' will do string comparisons not numeric comparisons
    assert(testSelect.size() == 6);
    vector<vector<string>> lessThanFive = {
        {"O'Reilly", "34567", "4.99", "Westwood"},
        {"Maca-roni", "72945", "1.25", "San Jose"},
        {"Patel", "12345", "42.54", "Westwood"},
        {"Hoang", "12345", "30.46", "Santa Monica"},
        {"Patel", "67890", "142.75", "Hollywood"},
        {"Baba O'Riley", "58201", "12.34", "Cool Hip City"}
    };
    assert(testSelect[0] == lessThanFive[0] ||testSelect[0] == lessThanFive[1]  || testSelect[0] == lessThanFive[2] ||        testSelect[0] == lessThanFive[3] || testSelect[0] == lessThanFive[4]  || testSelect[0] == lessThanFive[5]);
    assert(t.select("price LT 5.00", testSelect) == 0 && t.select("price lt 5.00", testSelect) == 0);
    assert(testSelect.size() == 2);
    lessThanFive.clear();
    lessThanFive = {
        {"O'Reilly", "34567", "4.99", "Westwood"},
        {"Maca-roni", "72945", "1.25", "San Jose"}
    };
    assert((testSelect[0] == lessThanFive[0] && testSelect[1] == lessThanFive[1]) || testSelect[0] == lessThanFive[1] &&  testSelect[1] == lessThanFive[0]);
     
    assert(t.select("Hollywood = location", testSelect) == -1);
    assert(t.select("location = 'Outer Space City'", testSelect) == 0);
    assert(testSelect.size() == 2);
    vector<vector<string>> selectLocation
    {
        {"Alexa", "03510", "77.77", "Outer Space City"}
    };
    assert(testSelect[0] == selectLocation[0]);
    assert(t.select("location == Cool Hip City", testSelect) == -1);
    assert(t.select("location == 'Cool Hip City'", testSelect) == 0);
    assert(testSelect.size() == 1);
    vector<vector<string>> hippityHop{
        {"Baba O'Riley", "58201", "12.34", "Cool Hip City"}
    };
    assert(testSelect[0] == hippityHop[0]);
    cout << "DONE" << endl;
}
void test9(){
    //test for good
        vector<string> col1 = {"a","b","c","d"};
        Table t1("z",col1);
        assert(!t1.good());//key not in the vector
        vector<string> col2;
        Table t2("z",col2);
        assert(!t2.good());//columns are empty
        assert(!t2.insert("abc"));
        vector<string> col3 = {"z","a","z"};
        Table t3("z",col3);//repeated value in the column
        assert(!t3.good());
        vector<string> col4 = {"","a","z"};
        Table t4("z",col4);//empty string
        assert(!t4.good());
        vector<string> col5 = {"a","b","c","d","z"};
        Table t5("z",col5);
        assert(t5.good());
     
    //test for select
        vector<string> cols = { "item name", "price", "location" };
        Table t("item name", cols);
        assert(t.insert("'chocolate' 1.75 Xian"));
        assert(t.insert("flower 000123 Shanghai"));
        assert(t.insert("seed 123 Wuhan"));
        vector<vector<string>> v;
        assert(t.select("price EQ 123",v) == 0);
        assert(v.size() == 2);
        assert(t.select("location EQ 123", v) == 3);
        assert(v.size() == 0);
        assert(t.select("price EQ w",v) == -1);
        assert(v.size() == 0);
        assert(t.select("Xian == location",v) == -1);
        assert(t.select("Xian EQ 3",v) == -1);
        assert(t.select("'item name' != chocolate", v) == 0);
        assert(v.size() == 2);
        assert(t.select ("price == 123",v) == 0);
        assert(v.size() == 1);
        assert(t.select("price ni 123",v) == -1);
        assert(t.select("item name == chocolate",v) == -1);
    cout << "DONE" << endl;
     

}





