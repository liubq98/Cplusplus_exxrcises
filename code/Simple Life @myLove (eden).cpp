#ifndef SIMPLE_ITERATOR_H
#define SIMPLE_ITERATOR_H

#include <iostream>

using namespace std;

class simple_iterator
{
public:
	simple_iterator(){
		pointer = NULL;
	}
	simple_iterator(char* p){
		pointer = p;
	}
	simple_iterator prev(){
		simple_iterator temp(pointer);
		temp.pointer--;
		return temp;
	}
	simple_iterator next(){
		simple_iterator temp(pointer);
		temp.pointer++;
		return temp;
	}
	char* begin(){
		char* p = pointer;
		while(*(p - 1) != '\0')
		{
			p--;
		}
		
		return p;
	}
	char* end(){
		char* p = pointer;
		while(*(p + 1) != '\0')
		{
			p++;
		}
		
		return p;
	}
	char operator*(){
		return *pointer;
	}
	simple_iterator& operator++(){
		pointer++;
		return *this;
	}
	simple_iterator operator++(int){
		simple_iterator temp(pointer);
		pointer++;
		return temp;
	}
	simple_iterator operator--(int){
		simple_iterator temp(pointer);
		pointer++;
		return temp;
	}
	simple_iterator& operator--(){
		pointer--;
		return *this;
	}
	bool operator==(const simple_iterator& it){
		return (*pointer == *(it.pointer));
	}
	bool operator!=(const simple_iterator& it){
		return (*pointer != *(it.pointer));
	}
	bool operator<(const simple_iterator& it){
		return (*pointer < *(it.pointer));
	}
	bool operator>(const simple_iterator& it){
		return (*pointer > *(it.pointer));
	}
	bool operator<=(const simple_iterator& it){
		return (*pointer <= *(it.pointer));
	}
	bool operator>=(const simple_iterator& it){
		return (*pointer >= *(it.pointer));
	}
	simple_iterator& operator+(const int& a){
		pointer += a;
		return *this;
	}
	simple_iterator& operator-(const int& a){
		pointer -= a;
		return *this;
	}


private:
	char* pointer;
};


#endif


#ifndef SIMPLE_VECTOR_H
#define SIMPLE_VECTOR_H

#include <iostream>
#include <cstring>
//#include "simple_iterator.h"
using namespace std;

static long long int MAX = 9999999;

class simple_vector {
    char* data;
    long long int size;
    long long int capacity;
  public:
    typedef simple_iterator iterator;

    simple_vector() : size(0), capacity(0) {
        data = new char[MAX];
        data[0] = '\0';
        memset(data, '\0', MAX);
    }

    ~simple_vector() {
        clear();
    }

    void clear() {
        delete [] data;
        size = capacity = 0;
    }

    long long int getSize() {
        return size;
    }

    long long int getCapacity() {
        return capacity;
    }

    void pushBack(char c) {
        if (capacity == 0)
            capacity = 1;
        else if (size == capacity)
            capacity = capacity * 2;
        data[++size] = c;
    }

    simple_iterator Begin() {
        return iterator(data + 1);
    }

    simple_iterator End() {
        return iterator((data + size + 1));
    }

    simple_iterator rBegin() {
        return iterator((data + size));
    }

    simple_iterator rEnd() {
        return iterator(data);
    }
};

#endif



#include <iostream>
//#include "simple_vector.h"
using namespace std;

void test_iterator() {
    int t, i;
    char c;
    simple_vector ivec;
    simple_vector::iterator iter, iter1, iter2;

    cin >> t;
    for (i = 0; i < t; i++) {
        cin >> c;
        ivec.pushBack(c);
    }

    cout << "Foward test: ";
    for (iter = ivec.Begin(); iter != ivec.End(); ++iter)
        cout << *iter << " ";
    cout << "\n";
    cout << "Backward test: ";
    for (iter = ivec.rBegin(); iter != ivec.rEnd(); --iter)
        cout << *iter;
    cout << "\n";

    cout << "Self-Foward test: ";
    iter1 = ivec.Begin();
    iter2 = ++iter1;
    cout << *iter2;
    iter1 = ivec.Begin();
    iter2 = iter1++;
    cout << *iter2 << "\n";

    cout << "Self-Backward test: ";
    iter1 = ivec.rBegin();
    iter2 = --iter1;
    cout << *iter2;
    iter1 = ivec.rBegin();
    iter2 = iter1--;
    cout << *iter2 << "\n";

    cout << "Compare test#1: ";
    iter1 = ivec.Begin();
    iter2 = ivec.rBegin();
    cout << (iter1 < iter2);
    cout << (iter1 > iter2);
    cout << (iter1 <= iter2);
    cout << (iter1 >= iter2);
    cout << (iter1 == iter1);
    cout << (iter1 != iter2) << "\n";

    cout << "Compare test#2: ";
    iter1 = ivec.Begin();
    iter2 = ivec.rBegin();
    cout << (iter2 < iter1);
    cout << (iter2 > iter1);
    cout << (iter1 <= iter1);
    cout << (iter2 >= iter2);
    cout << (iter1 == iter2);
    cout << (iter1 != iter1) << "\n";

    cout << "Move test: ";
    iter1 = ivec.Begin();
    iter2 = iter1 + 4;
    cout << *iter2;
    iter2 = iter2 - 3;
    cout << *iter2;
    iter2 = iter2 + 2;
    cout << *iter2 << "\n";

    cout << "C++11 test: ";
    iter1 = ivec.Begin();
    iter2 = ivec.rBegin();
    ++iter1;
    cout << *(iter1.begin());
    cout << *(iter1.end());
    cout << *(iter1.prev());
    cout << *(iter1.next());
    --iter2;
    cout << *(iter2.begin());
    cout << *(iter2.end());
    cout << *(iter2.prev());
    cout << *(iter2.next());
}

int main() {
    test_iterator();
    return 0;
}


