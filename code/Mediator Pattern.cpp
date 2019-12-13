#ifndef _DRESS_
#define _DRESS_
#include <iostream>
using std::string;
class Dress {
    private:
        string name;
        int price;
    public:
        Dress(const string & name, const int price);
        Dress(const Dress & oth);
        int getPrice() const;
        string getName() const;
};

#endif


#ifndef _USER_
#define _USER_

//#include "Dress.hpp"
#include <vector>
#include <iostream>
using std::vector;
using std::pair;
using std::cout;

using std::endl;

using std::string;

class Mediator;
class User {
    private:
        string name;
        int money;
        int id;
        vector<Dress>dresses;
    public:
        int getId() const {return id;}
        static int Count;   // Assign to id
        User(const string & name, const int & money, const vector<pair<string, int> > & dresses);
        void BuyBeautifulDress(const int & id, const int & pay, const string & name);
        /*
            if pay > money
              cout << this->name << " : " << "Forget to Check Wallet!" << endl;
            if buy success
              cout << this->name << " : " << "So happy to get new Dress!" << endl;
            if No such a dress
              cout << this->name << " : " << "I'm so sorry maybe just because I love it so much." << endl;
            if Can't afford it
              cout << this->name << " : " <<  "OMG! Why it is so Expensive!" << endl;
        */
        void GetDressInfo(const int & id);
        /*
            You need print this sentence at first
            cout << this->name << " : " << "I wanna see your beautiful suits!" << endl;
        */
        pair<int, string> SellBeautifulDress(const int & pay, const string & dname);  // how to use to pair to represent diffierent information?
        /*
            if Don't have that dress
            cout << this->name <<" : " << "I never have this Dress stupid!" << endl;
            if pay is lower than your price
            cout << this->name << " : " <<  "No monry then no talking" << endl;
            if success
            cout << this->name << " : " << "What a good taste you have !" << endl;
        */
        void SendMessage(const int & to, const string & msg);
        void GetMessage(const string & msg);
        /*
            print like:
            cout << this->name <<" : I got a Msg - " << msg << endl;
        */
        void ShowMyCuteDresses();
        /*  
            print this at first:
            cout << this->name << " : ok,these are all I have : "<<endl;
            Then For each Dress
            cout << dresses[i].getName() << "-" << dresses[i].getPrice() << endl;
        */
};

#endif


#ifndef _MEDIATOR_
#define _MEDIATOR_
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)
#include <list>
#include <iostream>
//#include "User.hpp"
using std::list;
class Mediator {
    private:
        DISALLOW_COPY_AND_ASSIGN(Mediator);
        std::list<User*> users;
        Mediator() {}
        ~Mediator() {}
        static Mediator* Ins;
    public:
        static Mediator* getInstance() {
            return Mediator::Ins == NULL ? (Mediator::Ins = new Mediator()) : Mediator::Ins;
        }
        static void DestroyIns() {
            if (Ins)
                delete Ins;
            Ins = NULL;
        }
        void RegisterHandler(User * u);
        void ChatHandler(const int & to, const string & msg);
        /*
            if No Such a User
            cout << "Are you kidding ? There is no such a guy!" << endl;
        */
        pair<int,string> TradeHandler(const int & to, const int & pay, const string & dressName);
        /*
            if no such a User
            cout << "There is no Such a guy!" << endl;
        */
        void DressInfoHandler(const int & to);
};


#endif


//#include "Dress.hpp" 
#include <string>
#include <iostream>

using namespace std;

Dress::Dress(const string & name, const int price){
	this->name = name;
	this->price = price;
}

Dress::Dress(const Dress & oth){
	name = oth.name;
	price = oth.price;
}

int Dress::getPrice() const{
	return price;
}

string Dress::getName() const{
	return name;
}



//#include "User.hpp"
//#include "Dress.hpp"
//#include "Mediator.hpp"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

int User::Count = 0;   // Assign to id

User::User(const string & name, const int & money, const vector<pair<string, int> > & dresses){
	this->name = name;
	this->money = money;
	id = Count;
	Count++;
	vector<pair<string, int> > temp1 = dresses;
	while(!temp1.empty())
	{
		Dress temp(temp1.front().first, temp1.front().second);
		this->dresses.push_back(temp);
		
		temp1.erase(temp1.begin());
	}
}

void User::BuyBeautifulDress(const int & id, const int & pay, const string & name){
	if(pay > money)
	{
		cout << this->name << " : " << "Forget to Check Wallet!" << endl;
		return;
	}
	
	pair<int, string> temp = Mediator::getInstance()->TradeHandler(id, pay, name);
	
	
	if(temp.first == -1)
	{
		cout << this->name << " : " << "I'm so sorry maybe just because I love it so much." << endl;
	}
	
	else if(temp.first == -2)
	{
		cout << this->name << " : " <<  "OMG! Why it is so Expensive!" << endl;
	}
	else if(temp.first != 0)
	{
		money -= temp.first;
		Dress temp1(temp.second, temp.first);
		dresses.push_back(temp1);
		cout << this->name << " : " << "So happy to get new Dress!" << endl;
	}
}

/*
    if pay > money
        cout << this->name << " : " << "Forget to Check Wallet!" << endl;
    if buy success
        cout << this->name << " : " << "So happy to get new Dress!" << endl;
    if No such a dress
        cout << this->name << " : " << "I'm so sorry maybe just because I love it so much." << endl;
    if Can't afford it
        cout << this->name << " : " <<  "OMG! Why it is so Expensive!" << endl;
*/
void User::GetDressInfo(const int & id){
	cout << this->name << " : " << "I wanna see your beautiful suits!" << endl;
	Mediator::getInstance()->DressInfoHandler(id);
}

/*
    You need print this sentence at first
    cout << this->name << " : " << "I wanna see your beautiful suits!" << endl;
*/
pair<int, string> User::SellBeautifulDress(const int & pay, const string & dname){
	int i;
	pair<int,string> temp;
	for(i = 0; i < dresses.size(); i++)
	{
		if(dresses[i].getName() == dname)
		{
			break;
		}
	}
	if(i == dresses.size())
	{
		cout << this->name <<" : " << "I never have this Dress stupid!" << endl;
		temp.first = -1;
		temp.second = "n";
		return temp;
	}
	
	if(pay < dresses[i].getPrice())
	{
		cout << this->name << " : " <<  "No monry then no talking" << endl;
		temp.first = -2;
		temp.second = "n";
		return temp;
	}
	else
	{
		cout << this->name << " : " << "What a good taste you have !" << endl;
		money += dresses[i].getPrice();
		
		temp.first = dresses[i].getPrice();
		temp.second = dresses[i].getName();
		
		vector<Dress>::iterator it = dresses.begin()+i;
		dresses.erase(it);
		return temp;
	}
}
  // how to use to pair to represent diffierent information?
/*
    if Don't have that dress
    cout << this->name <<" : " << "I never have this Dress stupid!" << endl;
    if pay is lower than your price
    cout << this->name << " : " <<  "No monry then no talking" << endl;
    if success
    cout << this->name << " : " << "What a good taste you have !" << endl;
*/
void User::SendMessage(const int & to, const string & msg){
	Mediator::getInstance()->ChatHandler(to, msg);
}

void User::GetMessage(const string & msg){
	cout << this->name <<" : I got a Msg - " << msg << endl;
}

/*
    print like:
    cout << this->name <<" : I got a Msg - " << msg << endl;
*/
void User::ShowMyCuteDresses(){
	cout << this->name << " : ok,these are all I have : "<<endl;
	for(int i = 0; i < dresses.size(); i++)
	{
		cout << dresses[i].getName() << "-" << dresses[i].getPrice() << endl;
	}
}

/*  
    print this at first:
    cout << this->name << " : ok,these are all I have : "<<endl;
    Then For each Dress
    cout << dresses[i].getName() << "-" << dresses[i].getPrice() << endl;
*/


#include <list>
#include <iostream>
#include <string>
//#include "User.hpp"
//#include "Mediator.hpp"

using namespace std;

Mediator* Mediator::Ins = NULL;

void Mediator::RegisterHandler(User * u){
	users.push_back(u);
}

void Mediator::ChatHandler(const int & to, const string & msg){
	list<User*>::iterator it;
	for(it = users.begin(); it != users.end(); it++)
	{
		if((*it)->getId() == to)
		{
			break;
		}
	}
	if(it == users.end())
	{
		cout << "Are you kidding ? There is no such a guy!" << endl;
	}
	else
	{
		(*it)->GetMessage(msg);
	}
}

/*
    if No Such a User
    cout << "Are you kidding ? There is no such a guy!" << endl;
*/
pair<int,string> Mediator::TradeHandler(const int & to, const int & pay, const string & dressName){
	list<User*>::iterator it;
	for(it = users.begin(); it != users.end(); it++)
	{
		if((*it)->getId() == to)
		{
			break;
		}
	}
	if(it == users.end())
	{
		cout << "There is no Such a guy!" << endl;
		pair<int,string> temp;
		temp.first = 0;
		temp.second = "n";
		return temp;
	}
	else
	{
		return (*it)->SellBeautifulDress(pay, dressName);
	}
}

/*
    if no such a User
    cout << "There is no Such a guy!" << endl;
*/
void Mediator::DressInfoHandler(const int & to){
	list<User*>::iterator it;
	for(it = users.begin(); it != users.end(); it++)
	{
		if((*it)->getId() == to)
		{
			break;
		}
	}
	if(it == users.end())
	{
		cout << "There is no Such a guy!" << endl;
	}
	else
	{
		(*it)->ShowMyCuteDresses();
	}
}



//#include "Mediator.hpp"

#include <iostream>
using std::cin;
int main() {
    cout << "Generate User" << endl;
    vector<User*> users;
    int size;
    cin >> size;
    while (size--) {
        string name;
        int money;
        vector<pair<string,int> > dresses;
        cin >> name >> money;
        int dress_size;
        cin >> dress_size;
        while (dress_size--) {
            string dname;
            int price;
            cin >> dname >> price;
            dresses.push_back(std::make_pair(dname, price));
        }
        User* t = new User(name, money, dresses);
        users.push_back(t);
        Mediator::getInstance()->RegisterHandler(t);
    }
    cout << "Communication part Start!" << endl;
    int Userid;
    while (cin >> Userid && Userid != -1) {
        char c;
        cin >> c;
        switch(c) {
            case 'b': {
                    string dname;
                    int pay, seller;
                    cin >> dname >> pay >>seller;
                    users[Userid]->BuyBeautifulDress(seller, pay, dname);
                    break;
                    }
            case 'd': {
                    int id;
                    cin >> id;
                    users[Userid]->GetDressInfo(id);
                    break;
                    }
            case 's': {
                    int to;
                    string msg;
                    cin >> to;
                    getline(cin, msg,'\n');
                    users[Userid]->SendMessage(to, msg);
                    break;
                    }
                default:
                    break;
            }
    }
    for (int i = 0; i < users.size(); i++)
        delete users[i];
    Mediator::DestroyIns();
    return 0;
}
