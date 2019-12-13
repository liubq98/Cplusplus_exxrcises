#ifndef LIST
#define LIST
 
#include <string>
#include <iostream>
 
typedef struct node {
  int data;
  struct node* next;
  node(int data = 0, struct node* next = NULL) : data(data), next(next) {}
} node;
 
class list {
 private:
  node* head;
  int _size;
 
 public:
  list();
  list(const list&);
  list& operator=(const list&);
  ~list();
 
  // Capacity
  bool empty(void) const;
  int size(void) const;
 
 public:
  // output
  // list: [1,2,3,4,5]
  // output: 1->2->3->4->5->NULL
  std::string toString(void) const;
 
  void insert(int position, const int& data);
  void erase(int position);
  void clear(void) {
    if (this->head != NULL) {
      node* p = this->head;
      while (p != NULL) {
        node* temp = p;
        p = p->next;
        delete temp;
      }
      this->head = NULL;
    }
    this->_size = 0;
  }
  list& sort(void);
};
 
#endif

#include <sstream> 

using namespace std;

list::list(){
	head = NULL;
	_size = 0;
}
 
list::list(const list& lian){
	_size = 0;
	head = NULL;
	_size = lian._size;
	node *temp = lian.head;
	int arr[_size] = {0};
	for(int i = 0; i < _size; i++)
	{
		arr[i] = temp->data;
		temp = temp->next;
	}
	head = new node;
	head->data = arr[0];
	head->next = NULL;
	temp = head;
	node *temp1;
	for(int i = 1; i < _size; i++)
	{
		temp1 = new node;
		temp1->data = arr[i];
		temp1->next = NULL;
		temp->next = temp1;
		temp = temp->next;
	}
}
 
list& list::operator=(const list& lian){
	clear();
	_size = lian._size;
	node *temp = lian.head;
	int arr[_size] = {0};
	for(int i = 0; i < _size; i++)
	{
		arr[i] = temp->data;
		temp = temp->next;
	}
	head = new node;
	head->data = arr[0];
	head->next = NULL;
	temp = head;
	node *temp1;
	for(int i = 1; i < _size; i++)
	{
		temp1 = new node;
		temp1->data = arr[i];
		temp1->next = NULL;
		temp->next = temp1;
		temp = temp->next;
	}
return *this;
}
 
list::~list(){
	clear();
}
 
 
// Capacity
bool list::empty(void) const{
	if(_size == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
 
int list::size(void) const{
	return _size;
}
 
  
    // output
  // list: [1,2,3,4,5]
  // output: 1->2->3->4->5->NULL
string list::toString(void) const{
	node *temp = head;
	string str;
	string str1;
	string str2 = "->";
	string str3 = "NULL";
	for(int i = 0; i < _size; i++)
	{
		stringstream ss;
		ss << temp->data;
		ss >> str1;
		str = str + str1 + str2;
		temp = temp->next;
	}
	str = str + str3;
return str;
}
 
 
void list::insert(int position, const int& data){
	node *temp = head;
	node *newnode = new node;
	newnode->data = data;
	newnode->next = NULL;
	if(position < 0 || position > _size)
	{
		delete newnode;
		return;
	}
	if(position == 0)
	{
		newnode->next = head;
		head = newnode;
		_size++;
	}
	else
	{
		for(int i = 0; i < position - 1; i++)
		{
			temp = temp->next;
		}
		newnode->next = temp->next;
		temp->next = newnode;
		_size++;
	}
}
 
void list::erase(int position){
	node *temp = head;
	if(position < 0 || position >= _size)
	{
		return;
	}
	if(_size == 1 && position == 0)
	{
		delete temp;
		head = NULL;
	}
	else if(position == 0)
	{
		temp = temp->next;
		delete head;
		head = temp;
	}
	else
	{
		for(int i = 0; i < position - 1; i++)
	    {
		    temp = temp->next;
	    }
	    node *temp2 = temp->next;
	    temp->next = temp2->next;
	    delete temp2;
	}
	
	_size--;
}
 
list& list::sort(void){
	int arr[_size] = {0};
	node* temp = head;
	for(int i = 0; i < _size; i++)
	{
		arr[i] = temp->data;
		temp = temp->next;
	}
	
	for(int i = 0; i < _size - 1; i++)
	{
		for(int j = i + 1; j < _size; j++)
		{
			if(arr[i] > arr[j])
			{
				int num = arr[i];
				arr[i] = arr[j];
				arr[j] = num;
			}
		}
	}
	temp = head;
	for(int i = 0; i < _size; i++)
	{
		temp->data = arr[i];
		temp = temp->next;
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
 
  cout << li.toString() << endl;
 
  cout << li.sort().toString() << endl;
  cout << li2.sort().toString() << endl;
  cout << li3.sort().toString() << endl;
 
  return 0;
}
 
