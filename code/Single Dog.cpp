#include "SingleDog.h"

int SingleDog::count = 0;


SingleDog::SingleDog(int id_, char* name_):id(id_){
    name = new char[20];
    for(int i = 0; i < 20; i++)
    {
    	name[i] = name_[i];
    }
    count++;
}

SingleDog::SingleDog(const SingleDog &other):id(other.id){
        name = new char[20];
    for(int i = 0; i < 20; i++)
    {
    	name[i] = other.name[i];
    }
    count++;
}

SingleDog::~SingleDog(){
	count--;
	delete []name;
}

int SingleDog::getCount(){
   return count;
}

