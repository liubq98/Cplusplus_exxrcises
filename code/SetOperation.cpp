#include <iostream>
#include <algorithm>
#include <stdio.h>
#define MAX_MEMBERS 100

class Set {
private:
    int members[MAX_MEMBERS];
    int size;
public:
    // Create an empty set.
    Set();
    // Create an set with some element.
    Set(int* m, int s);
    // Copy Constructor
    Set(Set const &s);
    
    // append a element to set.
    // If element in the set, return false.
    // Or insert in set and return true.
    bool append(int e);
    
    // remove a element by its value from set.
    // If element in the set, then remove it and return true.
    // Or return false.
    bool remove(int e);
    
    // return true if the set is empty, or return false.
    bool isEmptySet();
    
    // return true if the element e is in the set, or return false.
    bool isInSet(int e);
    
    // & is intersection of two set
    Set operator&(const Set &s);
    // | is union of two set
    Set operator|(const Set &s);
    // A - B is the complement of B with respect to A
    Set operator-(const Set &s);
    // A + B is their symmetric difference. A + B = (A - B) | (B - A)
    Set operator+(const Set &s);
    
    // return set.
    int* getMembers();
    
    // return size of set.
    int getSize();
    
};
 
void display(int* members, int size) {
    std::sort(members, members + size);
    std::cout << "{";
    for (int i = 0; i < size; i++) {
        if (i < size - 1) std::cout << members[i] << ", ";
        else std::cout << members[i];
    }
    std::cout << "}" << std::endl;
}


Set::Set(){
	size = 0;
}

    // Create an set with some element.
Set::Set(int* m, int s){
	size = s;
	for(int i = 0; i < size; i++)
	{
		members[i] = m[i];
	}
}

    // Copy Constructor
Set::Set(Set const &s){
	size = s.size;
	for(int i = 0; i < size; i++)
	{
		members[i] = s.members[i];
	}
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
	size++;
	members[size - 1] = e;
return true;
}

    
    // remove a element by its value from set.
    // If element in the set, then remove it and return true.
    // Or return false.
bool Set::remove(int e){
	for(int i = 0; i < size; i++)
	{
		if(members[i] == e)
		{
			members[i] = members[size - 1];
			size--;
			return true;
		}
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

    
    // return true if the element e is in the set, or return false.
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

    
    // & is intersection of two set
Set Set::operator&(const Set &s){
	Set temp;
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < s.size; j++)
		{
			if(members[i] == s.members[j])
			{
				temp.append(members[i]);
			}
		}
	}
return temp;
}

    // | is union of two set
Set Set::operator|(const Set &s){
	Set temp;
	for(int i = 0; i < size; i++)
	{
		temp.append(members[i]);
	}
	for(int j = 0; j < s.size; j++)
	{
		temp.append(s.members[j]);
	}
return temp;
}

    // A - B is the complement of B with respect to A
Set Set::operator-(const Set &s){
	Set temp;
	int j;
	for(int i = 0; i < size; i++)
	{
		for(j = 0; j < s.size; j++)
		{
			if(members[i] == s.members[j])
			{
				break;
			}
		}
		if(j == s.size)
		{
			temp.append(members[i]);
		}
	}
return temp;
}

    // A + B is their symmetric difference. A + B = (A - B) | (B - A)
Set Set::operator+(const Set &s){
	Set temp;
	Set temp1, temp2;
	int j;
	for(int i = 0; i < size; i++)
	{
		for(j = 0; j < s.size; j++)
		{
			if(members[i] == s.members[j])
			{
				break;
			}
		}
		if(j == s.size)
		{
			temp1.append(members[i]);
		}
	}
	
	j = 0;
	for(int i = 0; i < s.size; i++)
	{
		for(j = 0; j < size; j++)
		{
			if(s.members[i] == members[j])
			{
				break;
			}
		}
		if(j == size)
		{
			temp2.append(s.members[i]);
		}
	}
	
	for(int i = 0; i < temp1.size; i++)
	{
		temp.append(temp1.members[i]);
	}
	for(int j = 0; j < temp2.size; j++)
	{
		temp.append(temp2.members[j]);
	}
return temp;
}

    
    // return set.
int* Set::getMembers(){
	return members;
}

    
    // return size of set.
int Set::getSize(){
	return size;
}

 
int main(int argc, const char * argv[]) {
    int test[6];
    std::cin >> test[0]
    >> test[1]
    >> test[2]
    >> test[3]
    >> test[4]
    >> test[5];
    // Constructor 1
    Set s1 = Set();
    display(s1.getMembers(), s1.getSize());
    std::cout << "is empty set: " << s1.isEmptySet() << std::endl;
    // append func
    std::cout << "append: " << s1.append(test[0]) << std::endl;
    std::cout << "append: " << s1.append(test[4]) << std::endl;
    display(s1.getMembers(), s1.getSize());
    // repeat append
    std::cout << "append: " << s1.append(test[0]) << std::endl;
    display(s1.getMembers(), s1.getSize());
 
    std::cout << "is empty set: " << s1.isEmptySet() << std::endl;
 
    // Constructor 2
    Set s2 = Set(test, 5);
    // remove func
    std::cout << "remove: " << s2.remove(test[0]) << std::endl;
    display(s2.getMembers(), s2.getSize());
    // repeat append
    std::cout << "remove: " << s2.remove(test[0]) << std::endl;
    display(s2.getMembers(), s2.getSize());
 
    std::cout << test[5] << " is in set: " << s2.isInSet(test[5]) << std::endl;
    std::cout << test[2] << " is in set: " << s2.isInSet(test[2]) << std::endl;
 
    display(s1.getMembers(), s1.getSize());
    display(s2.getMembers(), s2.getSize());
 
    Set s3;
    s3 = s1 & s2;
    display(s3.getMembers(), s3.getSize());
 
    s3 = s1 | s2;
    display(s3.getMembers(), s3.getSize());
 
    s3 = s1 - s2;
    display(s3.getMembers(), s3.getSize());
 
    s3 = s2 - s1;
    display(s3.getMembers(), s3.getSize());
 
    s3 = s1 + s2;
    display(s3.getMembers(), s3.getSize());
 
    return 0;
}
