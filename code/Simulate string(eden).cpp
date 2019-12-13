#ifndef SSCPP2014_STRING_H
#define SSCPP2014_STRING_H
 
#include <iostream>
 
class String {
  private:
    char *_buff;
    int _length, _size;  // _size is of the allocated memory
 
  public:
    // constructors
    String();
    explicit String(const char *src);
    String(const String &src);
    // destructor
    ~String();
    // member methods
    void assign(const char *src);
    void append(const char &other);
    void clear();
    int compare(const String &other) const;
    const char* c_str() const;
    bool empty() const;
    int find(const String &other, int pos = 0) const;
    int length() const;
    String substr(const int &pos, const int &count) const;
    // overload operators
    char& operator[](const int &index);
    void operator=(const String &other);
    void operator=(const char *src);
    String operator+(const String &other) const;
    bool operator<(const String &other) const;
    bool operator<=(const String &other) const;
    bool operator>(const String &other) const;
    bool operator>=(const String &other) const;
    bool operator==(const String &other) const;
    bool operator!=(const String &other) const;
    // friend methods
    friend std::ostream& operator<<(std::ostream& out, const String &str);
    // non-meaning static property
    static char _error_sign;  // initial as any char is okay
};
 
#endif
#include <iostream>
#include <cstring>
#include "String.h"
#include <string>

using namespace std;

// constructors
String::String(){
	_length = 0;
	_size = 0;
}

String::String(const char *src){
	int len = strlen(src);
	_buff = new char[len + 1];
	_buff[len] = '\0';
	for(int i = 0; i < len; i++)
	{
		_buff[i] = src[i];
	}
	_length = len;
	_size = len * sizeof(char);
}

String::String(const String &src){
	int len = strlen(src._buff);
	_buff = new char[len + 1];
	_buff[len] = '\0';
	for(int i = 0; i < len; i++)
	{
		_buff[i] = src._buff[i];
	}
	_length = len;
	_size = len * sizeof(char);
}

    // destructor
String::~String(){
	delete []_buff;
	_length = 0;
	_size = 0;
}

    // member methods
void String::assign(const char *src){
	if(_length != 0)
	{
		delete []_buff;
	}
	int len = strlen(src);
	_buff = new char[len + 1];
	_buff[len] = '\0';
	for(int i = 0; i < len; i++)
	{
		_buff[i] = src[i];
	}
	_length = len;
	_size = len * sizeof(char);
}

void String::append(const char &other){
	if(_length == 0)
	{
		_length++;
		_size += sizeof(char);
		_buff = new char[2];
		_buff[0] = other;
		_buff[1] = '\0';
		return;
	}
	
	char* temp = new char[_length];
	for(int i = 0; i < _length; i++)
	{
		temp[i] = _buff[i];
	}
	delete []_buff;
	_length++;
	_size += sizeof(char);
	_buff = new char[_length + 1];
	for(int i = 0; i < _length - 1; i++)
	{
		_buff[i] = temp[i];
	}
	_buff[_length - 1] = other;
	_buff[_length] = '\0';
	delete []temp;
}

void String::clear(){
	delete []_buff;
	_length = 0;
	_size = 0;
}

int String::compare(const String &other) const{
	if(strcmp(_buff, other._buff) < 0)
	{
		return -1;
	}
	else if(strcmp(_buff, other._buff) == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

const char* String::c_str() const{
	return _buff;
}

bool String::empty() const{
	if(_length == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int String::find(const String &other, int pos) const{
	for(int i = pos; i < _length; i++)
	{
		if(_buff[i] == other._buff[0])
		{
			int ind = i;
			int flag = 0;
			for(int j = 0; j < other._length; j++)
			{
				if(_buff[ind] != other._buff[j])
				{
					flag = 1;
					break;
				}
				ind++;
			}
			if(flag == 0)
			{
				return i;
			}
		}
	}
}

int String::length() const{
	return _length;
}

String String::substr(const int &pos, const int &count) const{
	String temp;
	temp._buff = new char[count + 1];
	for(int i = 0; i < count; i++)
	{
		temp._buff[i] = 0;
	}
	temp._buff[count] = '\0';
	temp._length = count;
	temp._size = count * sizeof(char);
	int ind = 0;
	for(int i = pos; i < pos + count; i++)
	{
		temp._buff[ind] = _buff[i];
		ind++;
	}
return temp;
}

    // overload operators
char& String::operator[](const int &index){
	return _buff[index];
}

void String::operator=(const String &other){
	if(_length != 0)
	{
		delete []_buff;
	}
	_length = other._length;
	_size = other._size;
	_buff = new char[_length + 1];
	_buff[_length] = '\0';
	for(int i = 0; i < _length; i++)
	{
		_buff[i] = other._buff[i];
	}
}

void String::operator=(const char *src){
	_length = strlen(src);
	_size = _length * sizeof(char);
	_buff = new char[_length + 1];
	_buff[_length] = '\0';
	for(int i = 0; i < _length; i++)
	{
		_buff[i] = src[i];
	}
}

String String::operator+(const String &other) const{
	String temp;
	temp._length = other._length + _length;
	temp._size = temp._length * sizeof(char);
	temp._buff = new char[temp._length + 1];
	temp._buff[_length] = '\0';
	strcpy(temp._buff, _buff);
	strcat(temp._buff, other._buff);
return temp;
}

bool String::operator<(const String &other) const{
	if(strcmp(_buff, other._buff) < 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool String::operator<=(const String &other) const{
	if(strcmp(_buff, other._buff) <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool String::operator>(const String &other) const{
	if(strcmp(_buff, other._buff) > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool String::operator>=(const String &other) const{
	if(strcmp(_buff, other._buff) >= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool String::operator==(const String &other) const{
	if(strcmp(_buff, other._buff) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool String::operator!=(const String &other) const{
	if(strcmp(_buff, other._buff) == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

    // friend methods
ostream& operator<<(ostream& out, const String &str){
	if(str._length == 0)
	{
		
	}
	else
	{
		out << str._buff;
	}
	return out;
}


#include <iostream>
#include <cstring>
#include <string>
using namespace std;
 
String a, b("MFGZ!");
String c = b;
 
void display() {
  cout << a.empty() << " " << a.length() << " " << a << endl;
  cout << b.empty() << " " << b.length() << " " << b << endl;
  cout << c.empty() << " " << c.length() << " " << c << endl;
}
 
int main() {
  string aa, bb, cc;
  display();
  c[0] = 'K';
  display();
  cin >> aa >> cc;
  a.assign(aa.c_str());
  c.assign(cc.c_str());
  display();
  b.clear();
  display();
  for (int i = 0 ; i < 10; ++i) {
      char t;
      cin >> t;
      a.append(t);
      b.append(t);
      c.append(t);
  }
  display();
  b = c;
  display();
  b = a + c;
  display();
  cout << a.find(String("1993")) << endl;
  cout << b.find(String("HYOUKA")) << endl;
  cout << c.find(String("RIKKA")) << endl;
  cout << a.substr(0, 3) << endl;
  cout << b.substr(3, 8) << endl;
  cout << c.substr(6, 1) << endl;
  cout << (a > b) << (a >= b) << (a < b) << (a <= b) << (a == b) << endl;
  cout << a.compare(b) << b.compare(a) << endl;
  cout << (a > c) << (a >= c) << (a < c) << (a <= c) << (a == c) << endl;
  cout << a.compare(c) << c.compare(a) << endl;
  b = a;
  cout << (a > b) << (a >= b) << (a < b) << (a <= b) << (a == b) << endl;
  cout << a.compare(b) << b.compare(a) << endl;
  cout << a.compare(a) << endl;
  return 0;
}
 
