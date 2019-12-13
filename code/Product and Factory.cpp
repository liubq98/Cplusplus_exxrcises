
#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <iostream>
#include <string>

using namespace std;

static int flag = 0;

class Laptop
{
public:
	Laptop(){}
	~Laptop(){}
	void compileCppProgram(){
		if(flag == 0)
		{
			cout << "Apple";
		}
		else
		{
			cout << "Xiaomi";
		}
		cout << " Laptop compiles a cpp program." << endl;
	}
};


class MobilePhone
{
public:
	MobilePhone(){}
	~MobilePhone(){}
	void sendShortMessage(){
		if(flag == 0)
		{
			cout << "Apple";
		}
		else
		{
			cout << "Xiaomi";
		}
		cout << " MobilePhone sends a short message." << endl;
	}
};




#include <iostream>
#include <string>

using namespace std;


class Factory
{
public:
	Factory(){}
	virtual ~Factory(){}
	virtual Laptop* produceLaptop() = 0;
	virtual MobilePhone* produceMobilePhone() = 0;
	
};


class AppleFactory: public Factory
{
public:
	AppleFactory(){
		flag = 0;
	}
	virtual ~AppleFactory(){}
	virtual Laptop* produceLaptop(){
		Laptop* temp = new Laptop();
		return temp;
	}
	virtual MobilePhone* produceMobilePhone(){
		MobilePhone* temp = new MobilePhone();
		return temp;
	}
};


class XiaomiFactory: public Factory
{
public:
	XiaomiFactory(){
		flag = 1;
	}
	virtual ~XiaomiFactory(){}
	virtual Laptop* produceLaptop(){
		Laptop* temp = new Laptop();
		return temp;
	}
	virtual MobilePhone* produceMobilePhone(){
		MobilePhone* temp = new MobilePhone();
		return temp;
	}
};

#endif
