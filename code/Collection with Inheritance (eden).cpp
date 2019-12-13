#ifndef COLLECTION_HPP
#define COLLECTION_HPP

#include <iostream>

using namespace std;
//template <typename E>

typedef int E;

class Collection{
	public:
		
		virtual ~Collection(){
			
		}
		virtual void add(E e) = 0;
		virtual void clear(void) = 0;
		virtual bool contain(E e) = 0;
		virtual bool isEmpty(void) = 0;
		virtual void remove(E e) = 0;
		virtual int size(void) = 0;
	private:
		
};

#endif


#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
//#include "Collection.hpp"

using namespace std;

class List:public Collection {
	public:
		List(){
			
		}
		virtual ~List(){
			
		}
		virtual E& get(int index) = 0;
		virtual E& operator[](int index) = 0;
		virtual int indexOf(E element) = 0;
		virtual void sort(void) = 0;
	private:
		
};

#endif



#ifndef ARRAYLIST_H_
#define ARRAYLIST_H_


//template <typename E>

class ArrayList : public List {
 public:
  ArrayList();
  ~ArrayList();
  virtual void add(E e);
  virtual void clear(void);
  virtual bool contain(E e);
  virtual bool isEmpty(void);
  virtual void remove(E e);
  virtual E& operator[](int index);
  virtual E& get(int index);
  virtual int indexOf(E element);
  virtual void sort(void);
  virtual int size(void);

 private:
  E* storage;
  int _size;
  int _maxsize;
  static const int extend_factor = 2;
  void extend(void);
};

#endif

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <iostream>

//template <typename E>

class LinkedList : public List {
 public:
  typedef struct node {
    E data;
    struct node* next;
    struct node* prev;
    node(E data, struct node* next = NULL, struct node* prev = NULL)
        : data(data), next(next), prev(prev) {}
  } node;
  LinkedList();
  ~LinkedList();
  virtual void add(E e);
  virtual void clear(void);
  virtual bool contain(E e);
  virtual bool isEmpty(void);
  virtual void remove(E e);
  virtual E& operator[](int index);
  virtual E& get(int index);
  virtual int indexOf(E element);
  virtual void sort(void);
  virtual int size(void);

 private:
  node* head;
  node* tail;
  int _size;
};

#endif

#include <iostream>
#include <cstdlib>

//template <typename E>

using namespace std;

int partition(E* a, int lo, int hi){
	E pivot = a[hi];
	int i = lo;
	for(int j = lo; j < hi; j++)
	{
		if(a[j] <= pivot)
		{
			E temp = a[i];
			a[i] = a[j];
			a[j] = temp;
			i++;
		}
	}
	E temp = a[i];
	a[i] = a[hi];
	a[hi] = temp;
	return i;
}

void quicksort(E* a, int lo, int hi){
	if(lo < hi)
	{
		int p = partition(a, lo, hi);
		quicksort(a, lo, p - 1);
		quicksort(a, p + 1, hi);
	}
}

  void ArrayList::extend(void){
  	_maxsize *= extend_factor;
  	E* arr = new E[_maxsize];
  	for(int i = 0; i < _size; i++)
  	{
  		arr[i] = storage[i];
	}
	delete []storage;
	storage = arr;
  } 

  ArrayList::ArrayList(){
  	storage = new E[1000];
  	_size = 0;
  	_maxsize = 1000;
  }
  
  ArrayList::~ArrayList(){
  	clear();
  }
  
  void ArrayList::add(E e){
  	if(_size >= _maxsize - 1)
  	{
  		extend();
	}
  	storage[_size++] = e;
  }
  
  void ArrayList::clear(){
  	if(_size != 0)
  	{
  		delete []storage;
  		storage = NULL;
  		_size = 0;
	}
  }
  
  bool ArrayList::contain(E e){
  	for(int i = 0; i < _size; i++)
  	{
  		if(storage[i] == e)
  		{
  			return true;
		}
	}
	return false;
  }
  
  bool ArrayList::isEmpty(void){
  	return (_size == 0);
  }
  
void ArrayList::remove(E e){
  	for(int i = 0; i < _size; i++)
  	{
  		if(storage[i] == e)
  		{
  			for(int j = i; j < _size - 1; j++)
			{
			  	storage[j] = storage[j + 1];
			} 
  			_size--;
  			i--;
		}
	}
}
  
E& ArrayList::operator[](int index){
  	return storage[index];
}
  
E& ArrayList::get(int index){
  	return storage[index];
}
  
int ArrayList::indexOf(E element){
  	for(int i = 0; i < _size; i++)
  	{
  		if(storage[i] == element)
  		{
  			return i;
		}
	}
	return -1;
}
  
void ArrayList::sort(void){
  	quicksort(storage, 0, _size - 1);
}
  
int ArrayList::size(void){
  	return _size;
}
  


#include <iostream>
#include <cstdlib>

//template <typename E>

using namespace std;


  // merge two list to this list from src1 and src2


LinkedList::LinkedList(){
  	head = NULL;
  	tail = NULL;
  	_size = 0;
}
LinkedList::~LinkedList(){
  	clear();
}
  
void LinkedList::add(E e){
	if(_size == 0)
	{
		node* temp = new node(e);
		head = temp;
		tail = temp;
	}
	else
	{
		node* temp = new node(e, NULL, tail);
		tail->next = temp;
		tail = temp;
	}
	_size++;
}
  
void LinkedList::clear(void){
  	if(_size != 0)
  	{
  		while(head != NULL)
  		{
  			node* temp = head;
  			head = head->next;
  			delete temp;
		}
		head = NULL;
		tail = NULL;
		_size = 0;
	}
}
  
bool LinkedList::contain(E e){
	node* temp = head;
  	for(int i = 0; i < _size; i++)
  	{
  		if(temp->data == e)
  		{
  			return true;
		}
		temp = temp->next;
	}
	return false;
}
  
bool LinkedList::isEmpty(void){
  	return (_size == 0);
}
  
void LinkedList::remove(E e){
  	node* temp = head;
  	for(int i = 0; i < _size; i++)
  	{
  		if(temp->data == e)
  		{
  			if(_size == 1)
  			{
  				delete temp;
  				head = NULL;
  				tail = NULL;
			}
  			else if(temp == head)
  			{
  				head = head->next;
  				delete temp;
  				temp = head;
			}
			else if(temp == tail)
			{
				tail = tail->prev;
				delete temp;
				temp = tail;
			}
			else
			{
				node* temp1 = temp->next;
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				delete temp;
				temp = temp1;
			}
			_size--;
			i--;
		}
		else
		{
			temp = temp->next;
		}
	}
}
  
E& LinkedList::operator[](int index){
  	return get(index);
}
  
E& LinkedList::get(int index){
  	node* temp = head;
  	for(int i = 0; i < index; i++)
  	{
		temp = temp->next;
	}
	return temp->data;
}
  
int LinkedList::indexOf(E element){
  	node* temp = head;
  	for(int i = 0; i < _size; i++)
  	{
  		if(temp->data == element)
  		{
  			return i;
		}
		temp = temp->next;
	}
	return -1;
}

LinkedList::node* merge(LinkedList::node* left, LinkedList::node* right){
	LinkedList::node* ptr = new LinkedList::node(0);
	LinkedList::node* temp = ptr;
	while(left != NULL && right != NULL)
	{
		if(left->data <= right->data)
		{
			temp->next = left;
			left->prev = temp;
			temp = temp->next;
			left = left->next;
		}
		else
		{
			temp->next = right;
			right->prev = temp;
			temp = temp->next;
			right = right->next;
		}
	}
	
	if(left != NULL)
	{
		temp->next = left;
		left->prev = temp;
	}
	else
	{
		temp->next = right;
		right->prev = temp;
	}
	
	temp = ptr->next;
	delete ptr;
	return temp;
}

LinkedList::node* mergesort(LinkedList::node* head){
	if(head == NULL)
	{
		return head;
	}
	if(head->next == NULL)
	{
		return head;
	}
	
	LinkedList::node* fast, *slow, *pre;
	fast = head;
	slow = head;
	while(fast != NULL && fast->next != NULL)
	{
		fast = fast->next->next;
		pre = slow;
		slow = slow->next;
	}
	pre->next = NULL;
	
	LinkedList::node* left, *right;
	left = mergesort(head);
	right = mergesort(slow);
	return merge(left, right);
}
  
void LinkedList::sort(void){
  	head = mergesort(head);
}
  
int LinkedList::size(void){
  	return _size;
}
  



#include <iostream>
#include <cstdlib>
#include <exception>

using std::cin;
using std::cout;
using std::endl;
using std::exception;

class AlgorithmnForbidden : public exception {
  virtual const char *what() const throw() {
    return "Please do not use std::sort or std::list or std::vector .....";
  }
};

class TEST {
 private:
  int *testData;
  int data_size;

 public:
  TEST() {
#if defined(_GLIBCXX_ALGORITHM) || defined(_GLIBCXX_LIST) || \
    defined(_GLIBCXX_VECTOR)
    //throw AlgorithmnForbidden();
    cout << "please do not use algorithm" << endl;
#endif
    cin >> data_size;
    cout << "test data size:" << data_size << endl;
    testData = new int[data_size];
    for (int i = 0; i < data_size; i++) {
      cin >> testData[i];
    }
  }

  ~TEST() { delete[] testData; }

  void test_List(Collection *c) {
    cout << (c->isEmpty() ? "true" : "false") << endl;

    int n = data_size;

    for (int i = 0; i < n; i++) {
      c->add(testData[i]);
    }
    
    
    reinterpret_cast<List *>(c)->sort();

    for (int i = 0; i < n; i++) {
      cout << (*reinterpret_cast<List *>(c))[i] << " ";
    }

    cout << endl;

    // not empty
    cout << (c->isEmpty() ? "true" : "false") << endl;

    for (int i = 0; i < n / 2; i++) {
      cout << "(" << (c->contain(i) ? "true" : "false");
      cout << ","
           << (reinterpret_cast<List *>(c)->indexOf(i) != -1 ? "true" : "false")
           << ") ";
      c->remove(i);
    }

    cout << endl;

    for (int i = 0; i < c->size(); i++) {
      cout << (*reinterpret_cast<List *>(c))[i] << " ";
    }
    cout << endl;
  }

  void test_ArrayList() {
    Collection *c = new ArrayList();
    test_List(c);
    delete c;
  }

  void test_LinkedList() {
    Collection *c = new LinkedList();
    test_List(c);
    delete c;
  }

  void runAllTests() {
    cout << "Testing ArrayList:" << endl;
    test_ArrayList();
    cout << endl;
    cout << "Testing LinkedList:" << endl;
    test_LinkedList();
  }
};

int main() {
  TEST t;
  t.runAllTests();
  return 0;
}

