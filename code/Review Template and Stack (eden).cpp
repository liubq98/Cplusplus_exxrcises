#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <queue>

using namespace std;

template<typename T>

class Stack {
  public:
    Stack(){
    	count = 0;
	}
	
	 // constructor.
    void push(const T& data){
    	if(q2.empty() && q1.empty())
    	{
    		q1.push(data);
		}
		else if(q2.empty())
		{
			q1.push(data);
		}
		else
		{
			q2.push(data);
		}
		count++;
	}
	 // push operation.
    T pop(){
    	if(q1.empty() && q2.empty())
    	{
    		T e;
    		return e;
		}
		
    	if(q2.empty())
    	{
    		for(int i = 0; i < count - 1; i++)
    		{
    			T temp = q1.front();
    			q1.pop();
    			q2.push(temp);
			}
			T temp1 = q1.front();
			q1.pop();
			count--;
			return temp1;
		}
		else
		{
			for(int i = 0; i < count - 1; i++)
    		{
    			T temp = q2.front();
    			q2.pop();
    			q1.push(temp);
			}
			T temp1 = q2.front();
			q2.pop();
			count--;
			return temp1;
		}
	}
	 // return the value in the top and pop it out of the stack.
    T top(){
    	if(q2.empty())
    	{
    		return q1.back();
		}
		else
		{
			return q2.back();
		}
	}
	 // return the value in top.
    int size() const{
    	return count;
	}
	  // return size of the stack.
    bool empty(){
    	return (count == 0);
	}
	 // check whether is empty.

  private:
    queue<T> q1; // two queues.
    queue<T> q2;
    int count; // the number of elements.
};

template<typename T>

void print(Stack<T> s){
	int len = s.size();
	for(int i = 0; i < len; i++)
	{
		cout << s.top() << " ";
		s.pop();
	}
	
	cout << endl;
}

#endif


//#include "Stack.h"
#include<iostream>
#include<exception>

using namespace std;

class StackForbidden : public exception {
    virtual const char *what() const throw() {
        return "Please do not use Stack in stl..";
    }
};

int main() {

    #if defined(_GLIBCXX_STACK)
        throw StackForbidden();
    #endif

    Stack<int> stack;
    stack.push(88);
    stack.push(44);
    stack.push(99);

    cout << "The size is: " << stack.size() << endl;
    if (!stack.empty()) cout << stack.top() << endl;
    print(stack);

    stack.pop();
    print(stack);

    stack.push(777);
    cout << "The size is: " << stack.size() << endl;
    if (!stack.empty()) cout << stack.top() << endl;
    print(stack);

    stack.pop();
    stack.pop();
    cout << "The size is: " << stack.size() << endl;
    print(stack);
    stack.pop();
    if (!stack.empty()) cout << stack.top() << endl;
    else cout << "it is empty now." << endl;

    Stack<double> stack1;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        stack1.push(i + 0.01);
    }
    print(stack1);
    while (m--) {
        stack1.pop();
    }
    cout << "The size is: " << stack1.size() << endl;
    if (!stack1.empty()) cout << stack1.top() << endl;
    print(stack1);

}

