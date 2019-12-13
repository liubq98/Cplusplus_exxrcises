#include "set.hpp"

    // Create an empty set.
Set::Set(){
	size = 0;
}
    // Create an set with some element.
Set::Set(int* m, int s){
	for(int i = 0; i < s; i++)
	{
		members[i] = m[i];
	}
	size = s;
}
    
    // append a element to set.
    // If element in the set, return false.
    // Or insert in set and return true.
bool Set::append(int e){
	for(int i = 0; i < size; i++)
	{
		if(members[i] == e)
		{
			return false;
		}
	}
	
	members[size++] = e;
	return true;
}
    
    // remove a element by its value from set.
    // If element in the set, then remove it and return true.
    // Or return false.
bool Set::remove(int e){
	int flag = size;
	for(int i = 0; i < size; i++)
	{
		if(members[i] == e)
		{
			members[i] = members[size - 1]; 
			size--;
			i--;
		}
	}
	
	if(flag != size)
	{
		return true;
	}
return false;
}
    
    // return true if the set is empty, or return false.
bool Set::isEmptySet(){
	if(size == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
    
    // return set.
int* Set::getMembers(){
	return members;
}
    
    // return size of set.
int Set::getSize(){
	return size;
}
 
    // return false if element not in the set, or return true.
bool Set::isInSet(int e){
	for(int i = 0; i < size; i++)
	{
		if(members[i] == e)
		{
			return true;
		}
	}
return false;
}
