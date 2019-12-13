#ifndef LIST_H_
#define LIST_H_
#include <string>
#define MAX_STORAGE 1000
 class list{
    typedef int data_type;
    typedef int pointer;
    typedef unsigned int size_type;
    static const pointer nullpointer = -1;
    typedef struct node {
        data_type data;
        pointer next;
        node(const node &another) {
          this->operator=(another);
        }
        node& operator=(const node &another) {
          this->data = another.data;
          this->next = another.next;
        }
        node(data_type data = 0, pointer next = nullpointer) : data(data), next(next) {}
    } node;
    node storage[MAX_STORAGE];
    size_type _size;
    pointer head;
    pointer empty_head;
 public:
    list();
    list(const list& another);
    list& operator=(const list&);
    ~list();
     // Capacity
    bool empty(void) const;
    size_type size(void) const;
     // output
    // list: [1,2,3,4,5]
    // output: 1->2->3->4->5->NULL
    std::string toString(void) const;
     void insert(int position, const int& data);
    void erase(int position);
    void clear(void);
    list& sort(void);
};
 #endif // !LIST_H_
 

#include <string>
#include <sstream>
#include <iostream>

using namespace std; 

list::list(){
	_size = 0;
	head = nullpointer;
	empty_head = 0;
	for(int i = 0; i < MAX_STORAGE; i++)
	{
		storage[i].next = i + 1;
	}
}

list::list(const list& another){
	*this = another;
}

list& list::operator=(const list& a){
	int ind = a.head;
	for(int i = 0; i < a._size; i++)
	{
		storage[ind] = a.storage[ind];
		ind = a.storage[ind].next;
	}
	_size = a._size;
	head = a.head;
	empty_head = a.empty_head;
return *this;
}

list::~list(){
	clear();
}

// Capacity
bool list::empty() const{
	if(_size == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

list::size_type list::size(void) const{
	return _size;
}

// output
// list: [1,2,3,4,5]
// output: 1->2->3->4->5->NULL
string list::toString() const{
	string str, str1;
	if(empty())
	{
		str = "NULL";
		return str; 
	}
	stringstream ss;
	int ind = head;
	for(int i = 0; i < _size; i++)
	{
		ss.clear();
		ss << storage[ind].data;
		ss >> str1;
		str = str + str1 + "->";
		ind = storage[ind].next;
	}
	str = str + "NULL";
return str;
}

void list::insert(int position, const int& data){
	if(position < 0 || position > _size)
	{
		return;
	}
	
	storage[empty_head].data = data;
	if(_size == 0 && position == 0)
	{
		head = empty_head;
	    empty_head = storage[empty_head].next;
		storage[head].next = nullpointer;
		_size++; 
		return;
	}
	else if(position == 0)
	{
		int temp = empty_head;
	    empty_head = storage[empty_head].next;
	    storage[temp].next = head;
		head = temp;
		_size++;
		return;
	}
	
	if(position == _size && _size != 0)
	{
		int temp = empty_head;
	    empty_head = storage[empty_head].next;
		storage[temp].next = nullpointer;
		int ind = head;
		for(int i = 0; i < position - 1; i++)
		{
			ind = storage[ind].next;
		}
		storage[ind].next = temp;
		_size++;
		return;
	}
	
	int ind1 = head;
	for(int i = 0; i < position - 1; i++)
	{
		ind1 = storage[ind1].next;
	}
	int ind2 = storage[ind1].next;
	
	int temp = empty_head;
	empty_head = storage[empty_head].next;
	
	storage[ind1].next = temp;
	storage[temp].next = ind2;
	_size++;
}

void list::erase(int position){
	if(position < 0 || position >= _size)
	{
		return;
	}
	
	if(position == 0 && _size == 1)
	{
		head = nullpointer;
		empty_head = 0;
	}
	else if(position == 0)
	{
		int temp = empty_head;
		empty_head = head;
		head = storage[head].next;
		storage[empty_head].next = temp;
	}
	else if(position == _size - 1)
	{
		int temp = empty_head;
		int ind1 = head;
		for(int i = 0; i < _size - 1; i++)
		{
			ind1 = storage[ind1].next;
		}
		empty_head = storage[ind1].next;
		storage[ind1].next = nullpointer;
		storage[empty_head].next = temp;
	}
	else
	{
		int temp = empty_head;
		int ind1 = head;
		for(int i = 0; i < position - 1; i++)
		{
			ind1 = storage[ind1].next;
		}
		int ind2 = storage[ind1].next;
		storage[ind1].next = storage[ind2].next;
		empty_head = ind2;
		storage[empty_head].next = temp;
	}
	
	_size--;
}

void list::clear(){
	_size = 0;
	head = nullpointer;
	empty_head = 0;
	for(int i = 0; i < MAX_STORAGE; i++)
	{
		storage[i].next = i + 1;
	}
}

list& list::sort(){
	if(_size == 0 || _size == 1)
	{
		return *this;
	}
	int ind = head;
	int arr[_size] = {0};
	for(int i = 0; i < _size; i++)
	{
		arr[i] = storage[ind].data;
		ind = storage[ind].next;
	}
	
	for(int i = 0; i < _size - 1; i++)
	{
		for(int j = i; j < _size; j++)
		{
			if(arr[i] > arr[j])
			{
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
	
	ind = head;
	for(int i = 0; i < _size; i++)
	{
		storage[ind].data = arr[i];
		ind = storage[ind].next;
	}
return *this;
}


#include <iostream>
#include <string>
 using std::cin;
using std::cout;
using std::endl;
using std::string;
 int main() {
    list li;
     int n;
    cin >> n;
     for (int i = 0, data, pos; i < n; i++) {
        cin >> pos >> data;
        li.insert(pos, data);
    }
    
     cout << li.toString() << " size: " << li.size() << endl;
     list li2(li);
    list li3;
     li = li3 = li2 = li;
     cout << li.toString() << " size: " << li.size() << endl;
    cout << li2.toString() << " size: " << li2.size() << endl;
    cout << li3.toString() << " size: " << li3.size() << endl;
     int m;
    cin >> m;
     for (int i = 0, pos; i < m; i++) {
        cin >> pos;
        li.erase(pos);
    }
     for (int i = 0, temp; i < m; i++) {
      cin >> temp;
      li.insert(0, temp);
    }
     cout << li.toString() << endl;
     cout << li.sort().toString() << endl;
    cout << li2.sort().toString() << endl;
    cout << li3.sort().toString() << endl;
     return 0;
}
 
