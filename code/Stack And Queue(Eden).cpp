#include "stack.hpp"

void stack::push(int num){
	if(isFull())
	{
		return;
	}
	
	top++;
	storage[top] = num;
}

void stack::pop(void){
	if(isEmpty())
	{
		return;
	}
	
	top--;
}

int stack::peek(void){
	return storage[top];
}

bool stack::isEmpty(void){
	if(top == -1)
	{
		return true;
	}
return false;
}

bool stack::isFull(void){
	if(top == 9)
	{
		return true;
	}
return false;
}

void stack::clear(void){
	top = -1;
}

#include "queue.hpp"

void queue::push(int num){
	if(isFull())
	{
		return;
	}
	rear = (rear + 1) % 11;
	storage[rear] = num;
}

void queue::pop(void){
	if(isEmpty())
	{
		return;
	}
	head = (head + 1) % 11;
}

int queue::front(void){
	int i = (head + 1) % 11;
	return storage[i];
}

int queue::back(void){
	if(isEmpty())
	{
		return 0;
	}
	return storage[rear];
}

bool queue::isFull(void){
	if((rear + 1) % 11 == head)
	{
		return true;
	}
return false;
}

bool queue::isEmpty(void){
	if(head == rear)
	{
		return true;
	}
return false;
}

void queue::clear(void){
	head = 0;
	rear = 0;
}
