#ifndef _BIG_INTEGER_
#define _BIG_INTEGER_
 
#include <iostream>
#include <string>
using std::string;
using std::ostream;
 
// forward declaration
class BigInteger;
 
// operators overloading
BigInteger operator+(const BigInteger& left, const BigInteger& right);
BigInteger operator-(const BigInteger& left, const BigInteger& right);
ostream& operator<<(ostream& out, const BigInteger& Bint);
 
class BigInteger {
 public:
  BigInteger();
  explicit BigInteger(const string& number);
  BigInteger(const BigInteger& other);
  friend BigInteger operator+(const BigInteger& left,
                              const BigInteger& right);
 
  // promise left >= right
  friend BigInteger operator-(const BigInteger& left,
                              const BigInteger& right);
  friend ostream& operator<<(ostream& out, const BigInteger& Bint);
  ~BigInteger();
 
 private:
  int *data_;
  int size_;
};
 
#endif  // _BIG_INTEGER_



using namespace std;

// operators overloading
BigInteger operator+(const BigInteger& left, const BigInteger& right){
	BigInteger temp;
	int len = left.size_;
	int len2 = right.size_;
	if(left.size_ > right.size_)
	{
		len = right.size_;
		len2 = left.size_;
	}
	int data1[left.size_] = {0};
	int data2[right.size_] = {0};
	for(int i = 0; i < left.size_; i++)
	{
		data1[i] = left.data_[left.size_ - 1 - i];
	}
	for(int i = 0; i < right.size_; i++)
	{
		data2[i] = right.data_[right.size_ - 1 - i];
	}
	
	temp.data_ = new int[len2 + 1];
	
	for(int i =  0;i < len2 + 1; i++)
	{
		temp.data_[i] = 0;
	}
	for(int i = 0; i < len; i++)
	{
		temp.data_[i + 1] = (data1[i] + data2[i] + temp.data_[i]) / 10;
		temp.data_[i] = (data1[i] + data2[i] + temp.data_[i]) % 10;
	}
	
	for(int i = len; i < len2; i++)
	{
		if(left.size_ > right.size_)
		{
			temp.data_[i + 1] = (temp.data_[i] + data1[i]) / 10;
			temp.data_[i] = (temp.data_[i] + data1[i]) % 10;
		}
		else
		{
			temp.data_[i + 1] = (temp.data_[i] + data2[i]) / 10;
			temp.data_[i] = (temp.data_[i] + data2[i]) % 10;
		}
		 
	}
	
	if(temp.data_[len2] != 0)
	{
		temp.size_ = len2 + 1;
	}
	else
	{
		temp.size_ = len2;
	}
	
return temp;
} 

BigInteger operator-(const BigInteger& left, const BigInteger& right){
	BigInteger temp;
	int len = right.size_;
	temp.data_ = new int[left.size_];
	int arr[left.size_] = {0};
	
	int data1[left.size_] = {0};
	int data2[right.size_] = {0};
	for(int i = 0; i < left.size_; i++)
	{
		data1[i] = left.data_[left.size_ - 1 - i];
	}
	for(int i = 0; i < right.size_; i++)
	{
		data2[i] = right.data_[right.size_ - 1 - i];
	}
	
	for(int i = 0; i < left.size_; i++)
	{
		arr[i] = data1[i];
	}
	for(int i = 0; i < len; i++)
	{
		if(arr[i] < data2[i])
		{
			arr[i] += 10;
			int index = i + 1;
			while(arr[index] == 0)
			{
				arr[index] = 9;
				index++;
			}
			arr[index]--;
		}
		
		temp.data_[i] = arr[i] - data2[i];
	}
	
	for(int i = len; i < left.size_; i++)
	{
		temp.data_[i] = arr[i];
	}
	if(arr[left.size_ - 1] == 0)
	{
		temp.size_ = left.size_ - 1;
	}
	else
	{
		temp.size_ = left.size_;
	}
	
return temp;
} 

ostream& operator<<(ostream& out, const BigInteger& Bint){
	for(int i = Bint.size_ - 1; i >= 0; i--)
	{
		out << Bint.data_[i];
	}
} 


BigInteger::BigInteger(){
	size_ = 0;
} 

BigInteger::BigInteger(const std::string& number){
	int len = number.size();
	data_ = new int[len];
	size_ = len;
	char num[len] = {0};
	for(int i = 0; i < len; i++)
	{
		num[i] = number[i];
	}
	
	for(int i = 0; i < len; i++)
	{
		data_[i] = num[i] - '0';
	}
} 

BigInteger::BigInteger(const BigInteger& other){
	size_ = other.size_;
	data_ = new int[size_];
	for(int i = 0; i < size_; i++)
	{
		data_[i] = other.data_[i];
	}
} 

  
BigInteger::~BigInteger(){
	delete []data_;
	size_ = 0;
} 



using namespace std;
 
int main() {
  string s1, s2, s3, s4;
  cin >> s1 >> s2;
  cin >> s4;
  BigInteger a(s1);
  BigInteger b(s2);
  BigInteger c(a);
  BigInteger d(s4);
  BigInteger sum(a+b);
  BigInteger diff(c-d);
  cout << sum << endl;
  cout << diff << endl;
  return 0;
}
 
