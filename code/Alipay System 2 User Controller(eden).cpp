#ifndef ALIPAY_GLOBAL_H_
#define ALIPAY_GLOBAL_H_
 
namespace Alipay {
#define boss "Mayun"
#define MAX_USER 10000
enum GENDER { MALE = 0, FEMALE = 1 };
 
const double PRECISION = 0.000001;
}
 
#endif  // !ALIPAY_GLOBAL_H_
 
#ifndef ALIPAY_USER_H_
#define ALIPAY_USER_H_
namespace Alipay {
class user {
  char username[21];
  char password[21];
  double balance;
 
 public:
  user(const char* username, const char* password);
  ~user();
  const char* getUsername() const;
  const char* getPassword() const;
  const void setUsername(const char* username);
  const void setPassword(const char* password);
 
  double getBalance();
 
  bool withdraw(double amount);
  bool deposite(double amount);
};
}
#endif  // !ALIPAY_USER_H_
 
#ifndef ALIPAY_USERCONTROLLER_H
 

#include <string>
 
namespace Alipay {
class userController {
 private:
  double interest_rate;
  user* users[MAX_USER];
  int usercount;
  int getUserIndex(const char* username) const;
 
 public:
  userController(double interest_rate);
  ~userController();
  bool createUser(const char* username, const char* password);
  bool deposite(const char* username, double amount);
  bool withdraw(const char* username, double amount);
  std::string getUserInfoByName(const char* username) const;
  int getUserCount(void) const;
  bool removeUserByUsername(const char* username);
  bool setInterest(double interest);
  void payInterest(void);
};
}
 
#endif  // !ALIPAY_USERCONTROLLER_H



#include <string>
#include <string.h>
#include <iostream>

Alipay::user::user(const char* username, const char* password){
	balance =0; 
	strcpy(this->username, username);
	strcpy(this->username, username);
}

Alipay::user::~user(){
	
}

const char* Alipay::user::getUsername() const{
	return username;
}

const char* Alipay::user::getPassword() const{
	return password;
}

const void Alipay::user::setUsername(const char* username){
	strcpy(this->username, username);
}

const void Alipay::user::setPassword(const char* password){
	strcpy(this->username, username);
}

 
double Alipay::user::getBalance(){
	return balance;
}

 
bool Alipay::user::withdraw(double amount){
	if(amount < 0 || amount > balance)
	{
		return false;
	}
	else
	{
		balance -= amount;
		return true;
	}
}

bool Alipay::user::deposite(double amount){
	if(amount < 0)
	{
		return false;
	}
	else
	{
		balance += amount;
		return true;
	}
}



//fengexian
#include <sstream> 
#include <string.h>
#include <iostream>

bool verifyPasswordFormat(const char* &password){
	int len = strlen(password);
	if(len > 20 || len < 8)
	{
		return false;
	}
	int i;
	for(i = 0; i < len; i++)
	{
		if((password[i] > '9' || password[i] < '0')&&(password[i] < 'a' || password[i] > 'z')&&(password[i] > 'Z' || password[i] < 'A'))
		{
			return false;
		}
	}
return true;
} 

bool verifyUsernameFormat(const char* &username){
	int len = strlen(username);
	if(len < 6 || len > 20)
	{
		return false;
	}
	int i;
	for(i = 0; i < len; i++)
	{
		if((username[i] > '9' || username[i] < '0')&&(username[i] < 'a' || username[i] > 'z')&&(username[i] > 'Z' || username[i] < 'A'))
		{
			return false;
		}
	}
return true;
}

int Alipay::userController::getUserIndex(const char* username) const{
	for(int i = 0; i < usercount; i++)
	{
		if(strcmp(username, users[i]->getUsername()) == 0)
		{
			
			return i;
		}
	}
return -1;
}


Alipay::userController::userController(double interest_rate){
	this->interest_rate = interest_rate;
	usercount = 0;
}

Alipay::userController::~userController(){
	for(int i = 0; i < usercount; i++)
	{
		delete users[i];
	}
}

bool Alipay::userController::createUser(const char* username, const char* password){

	if(verifyPasswordFormat(password) == false || verifyUsernameFormat(username) == false)
	{
		return false;
	}
	    
	users[usercount] = new user(username, password);
	usercount++;
return true;
}

bool Alipay::userController::deposite(const char* username, double amount){
	if(verifyUsernameFormat(username) == false || amount < 0)
	{
		return false;
	}
	int ind = getUserIndex(username);
	if(ind == -1)
	{
		return false;
	}
	users[ind]->deposite(amount);
return true;
}

bool  Alipay::userController::withdraw(const char* username, double amount){
	if(verifyUsernameFormat(username) == false || amount < 0 )
	{
		return false;
	}
	else if(users[getUserIndex(username)]->getBalance() < amount)
	{
		return false;
	}
	int temp = getUserIndex(username);
	if(temp == -1)
	{
		return false;
	}
	users[temp]->withdraw(amount);
return true;
}

std::string Alipay::userController::getUserInfoByName(const char* username) const{
	int ind = getUserIndex(username);
	std::string temp;
	if(ind == -1)
	{
		return temp;
	}
	std::ostringstream os;
	os << "username:" <<users[ind]->getUsername() << "\npassword:*********\nbalance:" << users[ind]->getBalance();
	return os.str();
	//std::cout << "hi";
}

int Alipay::userController::getUserCount() const{
	return usercount;
}

bool Alipay::userController::removeUserByUsername(const char* username){
	if(usercount == 0)
	{
		return false;
	}
	if(verifyUsernameFormat(username) == false)
	{
		return false;
	}
	else
	{
		int temp = getUserIndex(username);
		if(temp == -1)
		{
			return false;
		}
		
		delete users[temp];
		for(int i = temp; i < usercount - 1; i++)
		{
			users[i] = users[i + 1];
		}
		users[usercount - 1] = NULL;
		usercount--;
		return true;
	}
}

bool Alipay::userController::setInterest(double interest){
	if(interest < 0)
	{
		return false;
	}
	else
	{
		interest_rate = interest;
		return true;
	}
}

void Alipay::userController::payInterest(){
	if(usercount == 0)
	{
		return;
	}
	double money;
	for(int i = 0; i < usercount; i++)
	{
		money = users[i]->getBalance() * interest_rate;
		users[i]->deposite(money); 
	}
}



#include <iostream>
#include <string>
 
using std::cin;
using std::cout;
using std::endl;
using std::string;
 
void help() {
  cout << "Welcome to Alipay Managament System" << endl;
  cout << "Please select your service using the number:" << endl;
  cout << "[1] Create an user" << endl;
  cout << "[2] Get an user's info by username" << endl;
  cout << "[3] Get total user count" << endl;
  cout << "[4] Remove one user" << endl;
  cout << "[5] Set interest" << endl;
  cout << "[6] Pay interest" << endl;
  cout << "[7] withdraw(for one account)" << endl;
  cout << "[8] deposite(for one account)" << endl;
  cout << "[9] Display help info" << endl;
  cout << "[0] Quit" << endl;
}
 
int main() {
  help();
  Alipay::userController controller(0.005);
  while (true) {
    cout << "Alipay $ ";
    int choose;
    cin >> choose;
    switch (choose) {
      case 1:
        if (true) {
          char username[21];
          char password[21];
          cout << "please input [username] [password]" << endl;
          cin >> username >> password;
          if (controller.createUser(username, password)) {
            cout << "create user successfully!" << endl;
          } else {
            cout << "fail to create user with username:" << username
                 << " password:" << password << endl;
          }
          break;
        }
      case 2:
        if (true) {
          char username[21];
          cout << "please input username" << endl;
          cin >> username;
          cout << "user info:" << endl;
          cout << controller.getUserInfoByName(username) << endl;
          break;
        }
      case 3:
        cout << "Total user count: " << controller.getUserCount() << endl;
        break;
      case 4:
        if (true) {
          char username[21];
          cout << "please input username" << endl;
          cin >> username;
          if (controller.removeUserByUsername(username)) {
            cout << "remove user successfully!" << endl;
          } else {
            cout << "fail to reomove user with username:" << username << endl;
          }
          break;
        }
      case 5:
        if (true) {
          double newRate;
          cout << "please input the new interest rate:" << endl;
          cin >> newRate;
          if (controller.setInterest(newRate)) {
            cout << "set interest successfully" << endl;
          } else {
            cout << "set interest falied with interest rate:" << newRate
                 << endl;
          }
          break;
        }
      case 6:
        if (true) {
          controller.payInterest();
          cout << "pay interest compelete" << endl;
          break;
        }
      case 7:
        if (true) {
          cout << "please input [username] [withdraw_amount]" << endl;
          char username[21];
          double amount;
          cin >> username >> amount;
          if (controller.withdraw(username, amount)) {
            cout << "withdraw successfully!" << endl;
          } else {
            cout << "withdraw falied with amount:" << amount << endl;
          }
          break;
        }
      case 8:
        if (true) {
          cout << "please input [username] [deposite_amount]" << endl;
          char username[21];
          double amount;
          cin >> username >> amount;
          if (controller.deposite(username, amount)) {
            cout << "deposite successfully!" << endl;
          } else {
            cout << "deposite falied with amount:" << amount << endl;
          }
          break;
        }
      case 0:
        cout << "Tanks for using Alipay, Bye!" << endl;
        return 0;
      case 9:
        help();
        break;
      default:
        cout << "No suchu command! Please input again" << endl;
        help();
    }
  }
 
  return 0;
}
 
