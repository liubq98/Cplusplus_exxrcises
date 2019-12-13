#ifndef LIST
#define LIST

#include <string>
#include <iostream>

class list {
 public:
  typedef int data_type;
  struct node {
   public:
    data_type data;
    node* next;
    node* prev;
    node(data_type data = 0, node* next = NULL, node* prev = NULL)
        : data(data), next(next), prev(prev){};
  };
  typedef node listNode;
  typedef node* listPointer;
  typedef unsigned int size_type;

 private:
  listPointer head;
  listPointer tail;
  size_type _size;
  inline listPointer at(int index) {
    if (index >= 0 && index < this->_size) {
      if (index <= this->_size / 2) {
        int counter = 0;
        listPointer p = this->head;
        while (counter != index) {
          counter++;
          p = p->next;
        }
        return p;
      } else {
        int counter = 0;
        listPointer p = this->tail;
        while (counter != this->_size - 1 - index) {
          counter++;
          p = p->prev;
        }
        return p;
      }
    }
    return NULL;
  }

 public:
  list();
  // construct a list from an exist array
  list(const data_type[], int length);
  list(const list&);
  list& operator=(const list&);
  ~list();

  // Capacity
  bool empty(void) const;
  size_type size(void) const;

  // Element access
  data_type& front(void) const;
  data_type& back(void) const;

 public:
  // output
  std::string toString(void) const;

  // Modifiers
  void assign(const list&);
  void assign(const data_type datas[], int length);
  void push_front(const data_type&);
  void push_back(const data_type&);
  void pop_front(void);
  void pop_back(void);

  void insert(int position, const data_type& data);
  void erase(int position);
  void clear(void);

  // Operations
  // split this list into to lists at the given position
  void split(int position, list* des1, list* dest2);
  // merge two list to this list from src1 and src2
  list& merge(const list& src1, const list& src2);
  // remove the elements who satisfy the condition
  list& remove_if(bool (*condition)(listPointer));

  // remove duplicate elements
  list& unique(void);
  // reverse the list
  list& reverse(void);

  // operators
  data_type& operator[](int index);
  list& operator+=(const list&);
  friend std::ostream& operator<<(std::ostream& os, const list& li);
};

#endif


#include <sstream>

using namespace std;


//first public
list::list(){
	head = NULL;
	tail = NULL;
	_size = 0;
}

  // construct a list from an exist array
list::list(const data_type arr[], int length){
	if(length == 0)
	{
		head = NULL;
	    tail = NULL;
	    _size = 0;
	    return;
	}
	_size = length;
	for(int i = 0; i < length; i++)
	{
		if(i == 0)
		{
			head = new node;
			head->data = arr[0];
			head->next = NULL;
			head->prev = NULL;
			tail = head;
		}
		else
		{
			listPointer temp = new node;
			temp->data = arr[i];
			temp->next = NULL;
			temp->prev = tail;
			tail->next = temp;
			tail = temp;
		}
	}
}

list::list(const list& a){
	if(a._size == 0)
	{
		head = NULL;
	    tail = NULL;
	    _size = 0;
	    return;
	}
	_size = a._size;
	listPointer ptr;
	for(int i = 0; i < _size; i++)
	{
		if(i == 0)
		{
			head = new node;
			head->data = a.head->data;
			head->next = NULL;
			head->prev = NULL;
			tail = head;
			
			ptr = a.head->next;
		}
		else
		{
			listPointer temp = new node;
			temp->data = ptr->data;
			temp->next = NULL;
			temp->prev = tail;
			tail->next = temp;
			tail = temp;
			ptr = ptr->next;
		}
	}
}

list& list::operator=(const list& a){
	clear();
	_size = a._size;
	listPointer ptr;
	for(int i = 0; i < _size; i++)
	{
		if(i == 0)
		{
			head = new node;
			head->data = a.head->data;
			head->next = NULL;
			head->prev = NULL;
			tail = head;
			
			ptr = a.head->next;
		}
		else
		{
			listPointer temp = new node;
			temp->data = ptr->data;
			temp->next = NULL;
			temp->prev = tail;
			tail->next = temp;
			tail = temp;
			ptr = ptr->next;
		}
	}
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

list::size_type list::size() const{
	return _size;
}


  // Element access
list::data_type& list::front() const{
	return head->data;
}

list::data_type& list::back() const{
	return tail->data;
}

  
//second public
  // output
string list::toString() const{
	string str;
	string str2;
	listPointer temp = head;
	stringstream ss;
	if(_size == 0)
	{
		str = "NULL";
	}
	else if(_size == 1)
	{
		ss.clear();
		ss << temp->data;
		ss >> str2;
		str = "NULL<-" + str2 + "->NULL";
	}
	else
	{
		for(int i = 0; i < _size; i++)
		{
			ss.clear();
			ss << temp->data;
			ss >> str2;
			temp = temp->next;
			if(i == 0)
			{
				str = "NULL<-" + str2;
			}
			else if(i == _size - 1)
			{
				str = str + "<->" + str2 + "->NULL";
			}
			else
			{
				str = str + "<->" + str2;
			}
		}
	}
return str;
}


  // Modifiers
void list::assign(const list& a){
	clear();
	if(a._size == 0)
	{
		head = NULL;
	    tail = NULL;
	    _size = 0;
	    return;
	}
	_size = a._size;
	listPointer ptr;
	for(int i = 0; i < _size; i++)
	{
		if(i == 0)
		{
			head = new node;
			head->data = a.head->data;
			head->next = NULL;
			head->prev = NULL;
			tail = head;
			
			ptr = head->next;
		}
		else
		{
			listPointer temp = new node;
			temp->data = ptr->data;
			temp->next = NULL;
			temp->prev = tail;
			tail->next = temp;
			tail = temp;
			ptr = ptr->next;
		}
	}
}

void list::assign(const data_type datas[], int length){
	clear();
	if(length == 0)
	{
		head = NULL;
	    tail = NULL;
	    _size = 0;
	    return;
	}
	_size = length;
	for(int i = 0; i < length; i++)
	{
		if(i == 0)
		{
			head = new node;
			head->data = datas[0];
			head->next = NULL;
			head->prev = NULL;
			tail = head;
		}
		else
		{
			listPointer temp = new node;
			temp->data = datas[i];
			temp->next = NULL;
			temp->prev = tail;
			tail->next = temp;
			tail = temp;
		}
	}
}

void list::push_front(const data_type& a){
	listPointer temp = new node;
	temp->data = a;
    temp->prev = NULL;
	temp->next = head;
	if(head != NULL)
	{
		head->prev = temp;
	}
	
	if(head == NULL)
	{
		tail = temp;
	}
	
	head = temp;
	_size++;
}

void list::push_back(const data_type& a){
	listPointer temp = new node;
	temp->data = a;
	temp->next = NULL;
	temp->prev = tail;
	if(tail != NULL)
	{
		tail->next = temp;
	}
	
	if(tail == NULL)
	{
		head = temp;
	}
	
	tail = temp;
	_size++;
}

void list::pop_front(void){
	listPointer temp = head;
	head = head->next;
	delete temp;
	head->prev = NULL;
	_size--;
}

void list::pop_back(void){
	listPointer temp = tail;
	tail = tail->prev;
	delete temp;
	tail->next = NULL;
	_size--;
}


void list::insert(int position, const data_type& data){
	listPointer temp = head;
	listPointer newnode = new node;
	newnode->data = data;
	newnode->next = NULL;
	newnode->prev = NULL;
	if(position < 0 || position > _size)
	{
		delete newnode;
		return;
	}
	if(_size == 0)
	{
		head = newnode;
		tail = newnode;
		_size++;
		return;
	}
	
	if(position == 0)
	{
		newnode->next = head;
		head->prev = newnode;
		head = newnode;
		_size++;
		return;
	}
	if(position == _size)
	{
		tail->next = newnode;
		newnode->prev = tail;
		tail = newnode;
		_size++;
		return;
	}
	else
	{
		for(int i = 0; i < position - 1; i++)
		{
			temp = temp->next;
		}
		newnode->next = temp->next;
		temp->next->prev = newnode;
		newnode->prev = temp;
		temp->next = newnode;
		
		_size++;
	}
}

void list::erase(int position){
	listPointer temp = head;
	if(position < 0 || position >= _size)
	{
		return;
	}
	if(_size == 1 && position == 0)
	{
		delete temp;
		head = NULL;
		tail = NULL;
	}
	else if(position == 0)
	{
		head = head->next;
		delete temp;		
		head->prev = NULL;
	}
	else
	{
		for(int i = 0; i < position - 1; i++)
	    {
		    temp = temp->next;
	    }
	    listPointer temp2 = temp->next;
	    temp->next = temp2->next;
	    if(position == _size - 1)
	    {
	    	tail = temp;
	    	tail->next = NULL;
	    	delete temp2;
		}
		else
		{
			listPointer temp3 = temp2->next;
	        temp3->prev = temp;
	        temp->next = temp3;
	        delete temp2;
		}
	    
	}
	
	_size--;
}

void list::clear(){
    if (this->head != NULL) 
	{
        listPointer p = this->head;
        while (p != NULL) 
		{
            node* temp = p;
            p = p->next;
            delete temp;
            if(p != NULL)
            {
            	p->prev = NULL;
			}
            
        }
        this->head = NULL;
        tail = NULL;
    }
    this->_size = 0;
  
}


  // Operations
  // split this list into to lists at the given position
void list::split(int position, list* des1, list* dest2){
	des1->clear();
	dest2->clear();
	if(position < 0 || position > _size)
	{
		return;
	}
	else if(position == 0)
	{
		des1->head = NULL;
		des1->tail = NULL;
		des1->_size = 0;
		*dest2 = *this;
	}
	else if(position == _size)
	{
		dest2->head = NULL;
		dest2->tail = NULL;
		dest2->_size = 0;
		*des1 = *this;
	}
	else
	{
		listPointer ptr;
		for(int i = 0; i < position; i++)
		{
			if(i == 0)
		{
			des1->head = new node;
			des1->head->data = head->data;
			des1->head->next = NULL;
			des1->head->prev = NULL;
			des1->tail = des1->head;
			
			ptr = head->next;
		}
		else
		{
			listPointer temp = new node;
			temp->data = ptr->data;
			temp->next = NULL;
			temp->prev = des1->tail;
			des1->tail->next = temp;
			des1->tail = temp;
			ptr = ptr->next;
		}
	}
	for(int i = position; i < _size; i++)
	{
			if(i == position)
		{
			dest2->head = new node;
			dest2->head->data = ptr->data;
			dest2->head->next = NULL;
			dest2->head->prev = NULL;
			dest2->tail = dest2->head;
			
			ptr = ptr->next;
		}
		else
		{
			listPointer temp = new node;
			temp->data = ptr->data;
			temp->next = NULL;
			temp->prev = dest2->tail;
			dest2->tail->next = temp;
			dest2->tail = temp;
			ptr = ptr->next;
		}
	}
	
	des1->_size = position;
	dest2->_size = _size - position;
    }
	
}

  // merge two list to this list from src1 and src2
list& list::merge(const list& src1, const list& src2){
	list temp1, temp2;
	temp1 = src1;
	temp2 = src2;
	clear();
	for(int i = 0; i < temp1._size; i++)
	{
		push_back(temp1[i]);
	} 
	for(int i = 0; i < temp2._size; i++)
	{
		push_back(temp2[i]);
	}
return *this;
}

  // remove the elements who satisfy the condition
list& list::remove_if(bool (*condition)(listPointer)){
	int i = 0;
	listPointer temp = head;
	while(temp != NULL)
	{
		if(condition(temp))
		{
		    temp = temp->next;
			erase(i);
		}
		else
		{
		    temp = temp->next;
			i++;
		}
	}
return *this;
}


  // remove duplicate elements
list& list::unique(){
	int arr[_size];
	listPointer temp = head;
	for(int i = 0; i < _size; i++)
	{
		arr[i] = temp->data;
		temp = temp->next;
	}
	int len = _size;
	for(int i = 0; i < len; i++)
	{
		for(int j = i + 1; j < len; j++)
		{
			if(arr[i] == arr[j])
			{
				erase(j);
				j--;
				len--;
				temp = head;
				for(int k = 0; k < len; k++)
				{
					arr[k] = temp->data;
					temp = temp->next;
				} 
			}
		}
	}
	
return *this;
}

  // reverse the list
list& list::reverse(void){
	int arr[_size] = {0};
	listPointer temp = head;
	for(int i = 0; i < _size; i++)
	{
		arr[i] = temp->data;
		temp = temp->next;
	}
	temp = head;
	for(int i = _size - 1; i >= 0; i--)
	{
		temp->data = arr[i];
		temp = temp->next;
	}
}


  // operators
list::data_type& list::operator[](int index){
	listPointer temp = head;
	for(int i = 0; i < index; i++)
	{
		temp = temp->next;
	}
	return temp->data;
}

list& list::operator+=(const list& a){
	list temp;
	temp = a;
	for(int i = 0; i < temp._size; i++)
	{
		push_back(temp[i]);
	}
return *this;
}

//friend function
ostream& operator<<(ostream& os, const list& li){
	os << li.toString();
return os;	
}




#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

bool condition1(list::listPointer p) { return true; }

bool condition2(list::listPointer p) {
  if (p->data % 2 == 0) {
    return false;
  }
  return true;
}

bool condition3(list::listPointer p) {
  if (p->data > 5) {
    return false;
  }
  return true;
}

void outputList(const list& li) {
  cout << li << " size:" << li.size();
  if (&li.front() == NULL) {
    cout << " front:NULL";
  } else {
    cout << " front:" << li.front();
  }

  if (&li.back() == NULL) {
    cout << " back:NULL";
  } else {
    cout << " back:" << li.back();
  }
  cout << endl;
}

int main() {
  int n, m;

  cin >> n >> m;

  int* a = new int[n]();

  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
//cout<<a[0]<<endl;
  if (true) {
    list li1(a, n);
    //cout<<"hi"<<a[0]<<endl;
    li1.insert(2, 111);
    li1.push_front(150);
    list li2(li1);
    //cout<<a[0]<<endl;
    outputList(li1);
    outputList(li2);
  }
//cout<<a[0]<<endl;
  cout << endl;

  if (true) {
    list li1;
    //cout<<a[0]<<endl;
    for (int i = 0; i < n; i++) {
    	//cout<<a[i]<<endl;
      li1.insert(i, a[i]);
    }
    for (int i = 0; i < m; i++) {
      li1.erase(i);
    }
    outputList(li1);
  }

  cout << endl;

  if (true) {
    list li1(a, n), li2, li3;
    li1 = li2 = li3 = li1;
    outputList(li1);
    li1.split(0, &li2, &li3);
    outputList(li1);
    outputList(li2);
    outputList(li3);
    li1.split(li1.size(), &li2, &li3);
    outputList(li1);
    outputList(li2);
    outputList(li3);
    li1.split(li1.size() / 2, &li2, &li3);
    cout << li2.toString() << endl;
    cout << li3.toString() << endl;
    li1 += (li2 += li1).merge(li1, li1);
    outputList(li1);
    li1 += li3;
    li2.merge(li1, li3);
    for (int i = 0; i < li1.size(); i++) {
      cout << li1[i] << " ";
    }
    cout << endl;
    outputList(li2);
  }

  cout << endl;

  cout << endl;

  if (true) {
    list li1(a, n);
    li1.remove_if(condition1);
    cout << li1 << " " << endl;
    li1.assign(a, n);
    li1.remove_if(condition2);
    cout << li1 << endl;
    li1.assign(a, n);
    li1.remove_if(condition3);
    outputList(li1);
  }

  cout << endl;

  if (true) {
    list li(a, n);
    li.merge(li, li).merge(li, li).unique();
    outputList(li);
  }

  delete[] a;

  return 0;
}


