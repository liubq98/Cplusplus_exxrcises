#include "user.hpp"
#include "test.hpp"

inline bool alipay::User::verifyPasswordFormat(const std::string &password){
	int len = password.size();
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

inline bool alipay::User::verifyUsernameFormat(const std::string &username){
	int len = username.size();
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

inline bool alipay::User::verifyPhoneFormat(const std::string &phone){
	int len = phone.size();
	int i;
	if(len != 13)
	{
		return false;
	}
	
	for(i = 0; i < len; i++)
	{
		if(phone[i] < '0' || phone[i] > '9')
		{
			return false;
		}
	}
return true;
}

bool alipay::User::setUsername(const char *username){
	std::string str = username;
	if(verifyUsernameFormat(str))
	{
		alipay::User::username = str;
		return true;
	}
return false;
}

bool alipay::User::setPassword(const char *new_password, const char *old_password){
	std::string newp = new_password;
	std::string oldp = old_password;
	if((alipay::User::password == oldp)&&(verifyPasswordFormat(oldp))&&(verifyPasswordFormat(newp)))
	{
		alipay::User::password = newp;
		return true;
	}
return false;
}

bool alipay::User::setPhone(const char *new_phone){
	std::string pho = new_phone;
	if(verifyPhoneFormat(pho))
	{
		alipay::User::phone = pho;
		return true;
	}
return false;
}

bool alipay::User::setGender(Gender::Gender gender){
	if(gender != alipay::Gender::Female && gender != alipay::Gender::Male)
	{
		return false;
	}
	else
	{
		alipay::User::gender = gender;
		return true;
	}
}
  
std::string alipay::User::getUsername(void){
	return alipay::User::username;
}

std::string alipay::User::getPhone(void){
	return alipay::User::phone;
}

alipay::Gender::Gender alipay::User::getGender(void){
	return alipay::User::gender;
}
  
  // if passowrd is in correct, return -1
long long int alipay::User::getMoneyAmount(const char *password){
	std::string str = password;
	if(alipay::User::password != str)
	{
		return -1;
	}
	else
	{
		return alipay::User::balance;
	}
}

bool alipay::User::deposit(long long int amount){
	if(amount <= 0)
	{
		return false;
	}
	else
	{
		alipay::User::balance += amount;
		return true;
	}
}

bool alipay::User::withdraw(long long int amount, const char *password){
	std::string str = password;
	if(alipay::User::password != str)
	{
		return false;
	}
	else
	{
		if(amount > alipay::User::balance || amount <= 0)
		{
			return false;
		}
		else
		{
			alipay::User::balance -= amount;
			return true;
		}
	}
}
