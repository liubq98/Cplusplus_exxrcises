#ifndef SSCPP2014_ACCOUNT_H
#define SSCPP2014_ACCOUNT_H
 #include <string>
 class Account {
  protected:
    int _id;
    double _balance;
    bool _valid;
    static int _total_account;
  public:
    Account();
    ~Account();
    int id() const;
    double balance() const;
    bool valid() const;
    std::string profile() const;
    void reset();
    bool deposit(const double &num);
    bool draw(const double &num);
    static int get_total_account();
};
 #endif
 
#include <string>
#include <sstream>

using namespace std;

int Account::_total_account = 0;

Account::Account(){
	_id = 0;
	_balance = 0.000000;
	_valid = false;
	_total_account++;
}

Account::~Account(){
	_total_account = 0;
}

int Account::id() const{
	return _id;
}

double Account::balance() const{
	return _balance;
}

bool Account::valid() const{
	return _valid;
}

string Account::profile() const{
	string str, str1, str2;
	stringstream ss;
	ss << _id;
	ss >> str1;
	ss.clear();
	ss << _balance;
	ss >> str2;
	str = "ID:" + str1 + "\nBALANCE:" + str2 + ".000000\nVALID:N\n";
return str;
}

void Account::reset(){
	_total_account = 0;
	_balance = 0.000000;
}

bool Account::deposit(const double &num){
	if(num < 0)
	{
		return false;
	}
	
	_balance += num;
return true;
}

bool Account::draw(const double &num){
	if(num < 0 || num > _balance - 0.01)
	{
		return false;
	}
	
	_balance -= num;
return true;
}

//static 
int Account::get_total_account(){
	return _total_account;
}


#ifndef PERSONAL_ACCOUNT_H_
#define PERSONAL_ACCOUNT_H_
 

 
class PersonalAccount : public Account {
  private:
    static int _total_per_account;
    static int _acc_id_ptr;
  public:
    PersonalAccount();
    ~PersonalAccount();
    // override
    std::string profile() const;
    void reset();
    // static
    static int get_total_per_account();
};
 
#endif


#include <string>
#include <sstream>

using namespace std;

int PersonalAccount::_total_per_account = 0;
int PersonalAccount::_acc_id_ptr = 12009999;

PersonalAccount::PersonalAccount(){
	_acc_id_ptr++;
	_total_per_account++;
	_valid = true;
	_balance = 10.000000;
}

PersonalAccount::~PersonalAccount(){
	_total_per_account = 0;
}

// override
string PersonalAccount::profile() const{
	string str, str1, str2;
	stringstream ss;
	ss << _acc_id_ptr;
	ss >> str1;
	ss.clear();
	ss << _balance;
	ss >> str2;
	str = "ID:" + str1 + "\nBALANCE:" + str2 + ".000000\nVALID:Y\nTYPE:PERSONAL\n";
return str;
}

void PersonalAccount::reset(){
	_total_per_account = 0;
	_balance = 10.000000;
}

// static
int PersonalAccount::get_total_per_account(){
	return _total_per_account;
}





#ifndef VIP_ACCOUNT_H_
#define VIP_ACCOUNT_H_
 
 
class VIPAccount : public Account {
  private:
    static int _total_vip_account;
    static int _acc_id_ptr;
  protected:
    double _loan;
    double _loan_limit;  // initial as 1k
  public:
    VIPAccount();
    ~VIPAccount();
    bool loan(const double &num);
    bool repay(const double &num);
    // override
    std::string profile() const;
    void reset();
    // static
    static int get_total_vip_account();
};
 
#endif


#include <string>
#include <sstream>

using namespace std;

int VIPAccount::_total_vip_account = 0;
int VIPAccount::_acc_id_ptr = 12049999;

VIPAccount::VIPAccount(){
	_acc_id_ptr++;
	_total_vip_account++;
	_valid = true;
	_balance = 10.000000;
	_loan_limit = 1000.000000;
	_loan = 0.000000;
}

VIPAccount::~VIPAccount(){
	_total_vip_account = 0;
}

bool VIPAccount::loan(const double &num){
	if(num < 0 || _loan + num > 1000)
	{
		return false;
	}
	
	_balance += num;
	_loan += num;
return true;
}

bool VIPAccount::repay(const double &num){
	if(num < 0 || _loan == 0 || num > _balance)
	{
		return false;
	}
	else
	{
		if(num <= _balance - 0.01)
		{
			_balance -= num;
			_loan -= num;
		}
		else
		{
			
			_loan -= _balance - 0.01;
			_balance = 0.01;
		}
	}
return true;
}

// override
string VIPAccount::profile() const{
	string str, str1, str2, str3, str4;
	stringstream ss;
	ss << _acc_id_ptr;
	ss >> str1;
	ss.clear();
	ss << _balance;
	ss >> str2;
	ss.clear();
	ss << _loan;
	ss >> str3;
	ss.clear();
	ss << _loan_limit;
	ss >> str4;
	
	str = "ID:" + str1 + "\nBALANCE:" + str2 + ".000000\nVALID:Y\nTYPE:VIP\nLOAN:" + str3 + ".000000,LIMIT:" + str4 + ".000000\n";
return str;
}

void VIPAccount::reset(){
	_total_vip_account = 0;
	_balance = 10.000000;
	_loan = 0.000000;
}

// static
int VIPAccount::get_total_vip_account(){
	return _total_vip_account;
}




#include <iostream>
using namespace std;
 
void display_count() {
  cout << Account::get_total_account() << ",";
  cout << PersonalAccount::get_total_per_account() << ",";
  cout << VIPAccount::get_total_vip_account() << endl;
}
 
int main() {
  display_count();
  if (true) {
    Account a0, a1, a2;
    display_count();
    PersonalAccount b0, b1;
    display_count();
  }
  VIPAccount c0, c1, c2, c3;
  display_count();
 
  Account *bptr = new Account();
  cout << bptr->profile() << endl;
  cout << bptr->id() << bptr->balance() << bptr->valid() << endl;
  delete bptr;
 
  PersonalAccount *pptr = new PersonalAccount();
  cout << pptr->profile() << endl;
  for (int i = 0; i < 5; ++i) {
    double t;
    int op;
    cin >> op >> t;
    if (op < 5) {
      cout << pptr->deposit(t) << ", ";
    } else {
      cout << pptr->draw(t) << ", ";
    }
    cout << pptr->balance() << endl;
  }
  cout << pptr->profile() << endl;
  pptr->reset();
  cout << pptr->profile() << endl;
  delete pptr;
 
  VIPAccount *vptr = new VIPAccount();
  cout << vptr->profile() << endl;
  for (int i = 0; i < 5; ++i) {
    double t;
    int op;
    cin >> op >> t;
    if (op < 5) {
      cout << vptr->loan(t);
    } else {
      cout << vptr->repay(t);
    }
    cout << "\n" << vptr->profile() << endl;
  }
  vptr->reset();
  cout << vptr->profile() << endl;
  delete vptr;
 
  return 0;
}

