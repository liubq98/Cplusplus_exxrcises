#ifndef INSERVICE_H
#define INSERVICE_H

#include <string>
#include <iostream>

using namespace std;


class Person
{
public:
	Person(){
        cout << "Construct Person" << endl;
	}
	~Person(){
		cout << "Destruct Person" << endl;
	}
	Person(string _name, int _sex, string _sno, string _wno){
		name = _name;
		sex = _sex;
		sno = _sno;
		wno = _wno;
		cout << "Construct Person" << endl;
	}
	string getName(){
        return name;
	}

	int getSex(){
		return sex;
	}

	string getSno(){
		return sno;
	}

	string getWno(){
		return wno;
	}
private:
	string name;
	int sex;
	string sno;
	string wno;
};

class Student
{
public:
	Student(){
		cout << "Construct Student" << endl;
	}
	~Student(){
		cout << "Destruct Student" << endl;
	}
	Student(string _name, int _sex, string _sno, string _wno){
		name = _name;
		sex = _sex;
		sno = _sno;
		wno = _wno;
		cout << "Construct Student" << endl;
	}
	string getName(){
        return name;
	}

	int getSex(){
		return sex;
	}

	string getSno(){
		return sno;
	}

	string getWno(){
		return wno;
	}
private:
	string name;
	int sex;
	string sno;
	string wno;
};

class Worker
{
public:
	Worker(){
		cout << "Construct Worker" << endl;
	}
	~Worker(){
		cout << "Destruct Worker" << endl;
	}
	Worker(string _name, int _sex, string _sno, string _wno){
		name = _name;
		sex = _sex;
		sno = _sno;
		wno = _wno;
		cout << "Construct Worker" << endl;
	}
	string getName(){
        return name;
	}

	int getSex(){
		return sex;
	}

	string getSno(){
		return sno;
	}

	string getWno(){
		return wno;
	}
private:
	string name;
	int sex;
	string sno;
	string wno;
};

class InService: public Person, public Student, public Worker
{
public:
	InService(){
		cout << "Construct InService" << endl;
	}
	~InService(){
		cout << "Destruct InService" << endl;
	}
	InService(string _name, int _sex, string _sno, string _wno): Person(_name, _sex, _sno, _wno), Student(_name, _sex, _sno, _wno), Worker(_name, _sex, _sno, _wno){
		name = _name;
		sex = _sex;
		sno = _sno;
		wno = _wno;
		cout << "Construct InService" << endl;
	}
	string getName(){
        return name;
	}

	int getSex(){
		return sex;
	}

	string getSno(){
		return sno;
	}

	string getWno(){
		return wno;
	}
private:
	string name;
	int sex;
	string sno;
	string wno;
};


#endif

