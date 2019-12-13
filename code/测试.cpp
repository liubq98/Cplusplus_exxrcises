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




#include <cstring>
#include <string>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::string;
list::list()
{
	head=NULL;
	tail=NULL;
	_size=0;
} 
list::list(const data_type num[], int length)
{
	_size=length;
	if(_size==0)
	{
		head=NULL;
		tail=NULL;
		return;
	}
	head=new list::node;
	head->data=num[0];
	list::node *p=head;
	int i;
	for(i=1;i<length;i++)
	{
		p->next=new list::node;
		p->next->data=num[i];
		p->next->prev=p;
		p=p->next;
	}
	tail=p;
}
list::list(const list& other)
{
	_size=other._size;
	if(_size==0)
	{
		head=NULL;
		tail=NULL;
		return;
	}
	node *p=other.head;
	head=new node;
	head->data=p->data;
	node *myp=head;
	int i;
	for(i=0;i<_size-1;i++)
	{
		p=p->next;
		myp->next=new node;
		myp->next->data=p->data;
		myp->next->prev=myp;
		myp=myp->next;
	}
	tail=myp;
}
list& list::operator=(const list& other)
{
	clear();
	_size=other._size;
	if(_size==0)
	{
		head=NULL;
		tail=NULL;
		return *this;
	}
	node *p=other.head;
	head=new node;
	head->data=p->data;
	node *myp=head;
	int i;
	for(i=0;i<_size-1;i++)
	{
		p=p->next;
		myp->next=new node;
		myp->next->data=p->data;
		myp->next->prev=myp;
		myp=myp->next;
	}
	tail=myp;
	return *this;
}
list::~list()
{
	clear();
}
bool list::empty(void) const
{
	
}
list::size_type list::size(void) const
{
	return _size;
}


list::data_type& list::front(void) const
{
	if(head==NULL)
	{
		int *p=NULL;
		return *p;
	}
	return head->data;
}
list::data_type& list::back(void) const
{
	if(tail==NULL)
	{
		int *p=NULL;
		return *p;
	}
	return tail->data;
}
std::string list::toString(void) const
{
	int i,len;
	char num[100]={};
	std::string os="",snum="";
	os=os+"NULL";
	if(_size==0)
	{
		return os;
	}
	node *p=head;
	os=os+"<-";
	sprintf(num,"%d",p->data);
	snum=num;
	len=strlen(num);
	for(i=0;i<len;i++)
	{
		num[i]='\0';
	}
	os=os+snum;
	while(p->next!=NULL)
	{
		p=p->next;
		sprintf(num,"%d",p->data);
		snum=num;
		len=strlen(num);
	    for(i=0;i<len;i++)
	    {
		    num[i]='\0';
	    }
		os=os+"<->"+snum;
	}
	os=os+"->NULL";
	return os;
}
void list::assign(const list&)
{
	
}
void list::assign(const data_type datas[], int length)
{
	clear();
	_size=length;
	if(_size==0)
	{
		head=NULL;
		tail=NULL;
		return;
	}
	head=new list::node;
	head->data=datas[0];
	list::node *p=head;
	int i;
	for(i=1;i<length;i++)
	{
		p->next=new list::node;
		p->next->data=datas[i];
		p->next->prev=p;
		p=p->next;
	}
	tail=p;
}
void list::push_front(const data_type& num)
{
	insert(0,num);
}
void list::push_back(const data_type& num)
{
	node *p;
	p=new node;
	p->data=num;
	if(tail!=NULL)
	{
		tail->next=p;
	    p->prev=tail;
	    tail=p;
	    _size++;
	}
	else
	{
		head=p;
		tail=p;
		_size++;
	}
}
void list::pop_front(void)
{
	
} 
void list::pop_back(void)
{
	
}
void list::insert(int position, const data_type& data)
{
	if(position>_size)
	  return;
	list::node *temp,*p=head;
	temp=new node;
	temp->data=data;
	if(position==0)
	{
		if(_size==0)
		{
			head=temp;
			tail=temp;
			_size++;
			return;
		}
		temp->next=head;
		head->prev=temp;
		head=temp;
		_size++;
		return;
	}
	int i;
	for(i=0;i<position-1;i++)
	{
		p=p->next;
	}
	temp->next=p->next;
	if(position!=_size)
	  p->next->prev=temp;
	p->next=temp;
	temp->prev=p;
	if(position==_size)
	  tail=temp;
	_size++;
}
void list::erase(int position)
{
	if(position>=_size)
	  return;
	node *p=head;
	if(position==0)
	{
		head=head->next;
		delete p;
		if(_size!=1)
		  head->prev=NULL;
		else
		  tail=NULL;
		_size--;
		return;
	}
	int i;
	for(i=0;i<position;i++)
	{
		p=p->next;
	}
	p->prev->next=p->next;
	if(position!=_size-1)
	  p->next->prev=p->prev;
	if(position==_size-1)
	  tail=p->prev;
	delete p;
	_size--;
}
void list::clear(void)
{
	int i,time=_size;
	for(i=0;i<time;i++)
	{
		//cout<<_size<<endl;
		//cout<<*this<<endl;
		erase(0);
	}
}
void list::split(int position, list* des1, list* dest2)
{
	
	if(position==0)
	{
		*dest2=*des1;
		//cout<<des1->_size<<endl;
		des1->clear();
		return;
	}
	list temp1,temp2;
	if(position>=des1->_size)
	{
		temp1=*dest2;
		temp2=*des1;
		*des1=temp1;
		*dest2=temp2;
		return;
	}
	int i;
	for(i=0;i<position;i++)
	{
		temp1.push_back((*des1)[i]);
	}
	for(i=position;i<des1->_size;i++)
	{
		temp2.push_back((*des1)[i]);
	}
	*des1=temp1;
	*dest2=temp2;
}


list& list::merge(const list& src1, const list& src2)
{
	list temp1=src1,temp2=src2;
	clear();
	int i,num;
	//cout<<temp1<<endl;
	for(i=0;i<temp1._size;i++)
	{
		push_back(temp1[i]);
	}
	//cout<<*this<<endl;
	for(i=0;i<temp2._size;i++)
	{
		push_back(temp2[i]);
	}
	//cout<<*this<<endl;
	return *this;
}
list& list::remove_if(bool (*condition)(listPointer))
{
	if(_size==0)
	  return *this;
	int pos;
	node *p=head;
	pos=0;
	while(p!=NULL)
	{
		if(condition(p))
		{
			p=p->next;
			erase(pos);
		}
		else
		{
			p=p->next;
			pos++;
		}
	}
	return *this;
}
list& list::unique(void)
{
	if(_size==0)
	  return *this;
	//cout<<_size<<endl;
	int i,shu,j,num[_size],count=0,qian=0;
	node *p=head;
	for(i=0;i<_size;i++)
	{
		num[i]=p->data;
		p=p->next;
	}
	for(i=_size-1;i>0;i--)
	{
		for(j=i-1;j>=0;j--)
		{
			if(num[i]==num[j])
			{
				erase(i);
				goto a;
			}
		}
		a:continue;
	}
	//cout<<"hi"<<endl;
	return *this;
}
list& list::reverse(void)
{
	
}
list::data_type& list::operator[](int index)
{
	node *p=head;
	int i;
	for(i=0;i<index;i++)
	{
		p=p->next;
	}
	return p->data;
}
list& list::operator+=(const list& other)
{
	if(other._size==0)
	  return *this;
	int i;
	list temp=other;
	for(i=0;i<other._size;i++)
	{
		push_back(temp[i]);
	}
	return *this;
}
std::ostream& operator<<(std::ostream& os, const list& li)
{
	os<<"NULL";
	if(li._size==0)
	{
		return os;
	}
	list::node *p=li.head;
	os<<"<-"<<p->data;
	while(p->next!=NULL)
	{
		p=p->next;
		os<<"<->"<<p->data;
	}
	os<<"->NULL";
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

  if (true) {
    list li1(a, n);

    li1.insert(2, 111);
    li1.push_front(150);
    list li2(li1);
    outputList(li1);
    outputList(li2);
  }

  cout << endl;

  if (true) {
    list li1;
    for (int i = 0; i < n; i++) {
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


