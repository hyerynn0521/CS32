//
//  main.cpp
//  Homework 3
//
//  Created by Hyerin Lee on 5/2/21.
//

#include <iostream>
#include <string>
using namespace std;

enum CallType {
    VOICE, TEXT
};

//Your declarations and implementations would go here
class Medium{
public:
    Medium(string id):m_id(id){}
    virtual string connect() const;
    virtual string id() const;
    virtual string transmit(string msg) const;
    virtual string medium() const = 0;
    virtual CallType callType() const {return TEXT;};
    virtual ~Medium(){}
private:
    string m_id;

    
    
};
string Medium::connect() const{
    return medium();
}
string Medium::id() const{
    return m_id;
}
string Medium::transmit(string msg) const{
    if(medium() == "Tweet" || medium() == "Email"){
        return "text: " + msg;
    }
    else{
        if(this->callType() == VOICE){
            return "voice: " + msg;
        }
        else if(this->callType() == TEXT){
            return "text: " + msg;
        }
    }
    return "";
}


class TwitterAccount: public Medium{
public:
    TwitterAccount(string id): Medium(id), m_medium("Tweet") {}
    string medium() const{ return m_medium;}
    ~TwitterAccount(){cout << "Destroying the Twitter account " << id() << "." << endl;}
private:
    string m_medium;

    
};

class Phone: public Medium{
public:
    Phone(string id, CallType type):  Medium(id), m_callType(type), m_medium("Call"){}
    string medium() const{ return m_medium;}
    CallType callType() const{return m_callType;}
    ~Phone(){cout << "Destroying the phone " << id() << "." << endl;}
private:
    
    CallType m_callType;
    string m_medium;
 
};

class EmailAccount: public Medium{
public:
    EmailAccount(string id):Medium(id), m_medium("Email"){}
    string medium() const{ return m_medium;}
    ~EmailAccount(){cout << "Destroying the email account " << id() << "." << endl; }
private:
    string m_medium;
};

void send(const Medium* m, string msg)
{
    cout << m->connect() << " using id " << m->id()
         << ", sending " << m->transmit(msg) << endl;
}

int main()
{
    
    Medium* media[4];
    media[0] = new TwitterAccount("UCLABruinAlert");
      // Phone users may prefer messages to be left as voice or text.
    media[1] = new Phone("(310) 825 3894", VOICE);
    media[2] = new Phone("(213) 389 9060", TEXT);
    media[3] = new EmailAccount("jbroon@ucla.edu");

    cout << "Send the message." << endl;
    for (int k = 0; k < 4; k++)
        send(media[k], "Major power outage in West L.A.");

      // Clean up the media before exiting
    cout << "Cleaning up." << endl;
    for (int k = 0; k < 4; k++)
        delete media[k];
}
/*Send the message.
 Tweet using id UCLABruinAlert, sending text: Major power outage in West L.A.
 Call using id (310) 825 3894, sending voice: Major power outage in West L.A.
 Call using id (213) 389 9060, sending text: Major power outage in West L.A.
 Email using id jbroon@ucla.edu, sending text: Major power outage in West L.A.
 Cleaning up.
 Destroying the Twitter account UCLABruinAlert.
 Destroying the phone (310) 825 3894.
 Destroying the phone (213) 389 9060.
 Destroying the email account jbroon@ucla.edu.
*/

