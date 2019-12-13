#ifndef ANIMAL_H
#define ANIMAL_H

#include <iostream>
#include <string>

using namespace std;

enum Type {
    CAT,
    DOG
};

class Animal {
 public:
 	Animal(){
 		
	 }
    Animal(string _name, int _age) : name(_name), age(_age) {}
    virtual void Shout() const = 0;
    virtual Type getType() const = 0;
    string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

 private:
    string name;
    int age;
};

class Cat: public Animal{
	public:
		Cat():Animal(){
			
		}
		Cat(string _name, int _age): Animal(_name, _age){
			catc++;
		}
		
		~Cat(){
			
		}
		
		void Shout() const{
			cout << getName() << ": meow~~" << endl;
		}
		
		Type getType() const{
			return CAT;
		}
		
		static int catc;
};

class Dog: public Animal{
	public:
		Dog():Animal(){
			
		}
		
		Dog(string _name, int _age): Animal(_name, _age){
			dogc++;
		}
		
		~Dog(){
			
		}
		
		void Shout() const{
			cout << getName() << ": bark!!" << endl;
		}
		
		Type getType() const{
			return DOG;
		}
		
		static int dogc;
};

#endif



#ifndef ZOO_H
#define ZOO_H

//#include "animal.h"
#include <vector>
#include <string>

using namespace std;

class Zoo{
	public:
		Zoo();
		~Zoo();
		void addAnimal(Dog* d);
		void addAnimal(Cat* c);
		int getDogCount();
		int getCatCount();
		void deleteAnimalByName(string _name);
		void deleteAnimalByAge(int _age);
		void print();
	private:
		vector<Animal*> ani;
		static int count;
};

#endif


//#include "zoo.h"
//#include "animal.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int Zoo::count = 0;
int Dog::dogc = 0;
int Cat::catc = 0; 

Zoo::Zoo(){
	
}

Zoo::~Zoo(){
	
}

void Zoo::addAnimal(Dog* d){
	
	
	ani.push_back(d);
	count++;
}

void Zoo::addAnimal(Cat* c){
	
	ani.push_back(c);
	count++;
}

int Zoo::getDogCount(){
	return Dog::dogc;
}

int Zoo::getCatCount(){
	return Cat::catc;
}

void Zoo::deleteAnimalByName(string _name){
	for(int i = 0; i < count; i++)
	{
		if(ani[i]->getName() == _name)
		{
			if(ani[i]->getType() == CAT)
			{
				Cat::catc--;
			}
			else
			{
				Dog::dogc--;
			}
			ani.erase(ani.begin() + i);
			i--;
			count--;
		}
	}
}

void Zoo::deleteAnimalByAge(int _age){
	for(int i = 0; i < count; i++)
	{
		if(ani[i]->getAge() == _age)
		{
			if(ani[i]->getType() == CAT)
			{
				Cat::catc--;
			}
			else
			{
				Dog::dogc--;
			}
			ani.erase(ani.begin() + i);
			i--;
			count--;
		}
	}
}

void Zoo::print(){
	for(int i = 0; i < count; i++)
	{
		ani[i]->Shout();
	}
}


#include <iostream>
#include <string>
using namespace std;
 
int main() {
 
    Dog dogs[10];
    Cat cats[10];
    Zoo zoo;
 
    int cnt1, cnt2;
    string name;
    int age;
 
    cin >> cnt1 >> cnt2;
    for (int i = 0; i < cnt1; i++) {
        cin >> name >> age;
        dogs[i] = Dog(name, age);
        zoo.addAnimal(&dogs[i]);
    }
    for (int i = 0; i < cnt2; i++) {
        cin >> name >> age;
        cats[i] = Cat(name, age);
        zoo.addAnimal(&cats[i]);
    }
 
    std::cout << zoo.getDogCount() << std::endl;
    std::cout << zoo.getCatCount() << std::endl;
 zoo.print();
    cin >> name;  // specified name to delete.
    cin >> age;   // specified age to delete.
    zoo.deleteAnimalByName(name);
    zoo.deleteAnimalByAge(age);
 
    std::cout << zoo.getDogCount() << std::endl;
    std::cout << zoo.getCatCount() << std::endl;
 
    zoo.print();
 
    return 0;
}
