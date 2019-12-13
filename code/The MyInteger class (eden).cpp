#include "MyInteger.hpp"
#include <cctype>
#include <string>

MyInteger::MyInteger(int valu){
    value = valu;
}

int MyInteger::getValue() const{
    return value;
}

bool MyInteger::isEven() const{
    if(value % 2 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
    
bool MyInteger::isOdd() const{
    if(value % 2 != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
    
bool MyInteger::isPrime() const{
	if(value == 1)
	{
		return false;
	}
    for(int i = 2; i < value; i++)
    {
        if(value % i == 0)
        {
            return false;
        }
    }
    return true;
}
    
bool MyInteger::isEven(int val){
    if(val % 2 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

    
bool MyInteger::isOdd(int val){
    if(val % 2 != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
    
bool MyInteger::isPrime(int val){
	if(val == 1)
	{
		return false;
	}
    for(int i = 2; i < val; i++)
    {
        if(val % i == 0)
        {
            return false;
        }
    }
    return true;
}
    
bool MyInteger::isEven(const MyInteger& temp){
    if(temp.value % 2 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
    
bool MyInteger::isOdd(const MyInteger& temp){
    if(temp.value % 2 != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
    
bool MyInteger::isPrime(const MyInteger& temp){
	if(temp.value == 1)
	{
		return false;
	}
    for(int i = 2; i < temp.value; i++)
    {
        if(temp.value % i == 0)
        {
            return false;
        }
    }
    return true;
}
    
bool MyInteger::equals(int val){
    if(value == val)
    {
        return true;
    }
    else
    {
        return false;
    }
}
    
bool MyInteger::equals(const MyInteger& temp){
    if(value == temp.value)
    {
        return true;
    }
    else
    {
        return false;
    }
}
    
int MyInteger::parseInt(const std::string& str){
    int val; 
    val = atoi(str.c_str());
return val;
}

