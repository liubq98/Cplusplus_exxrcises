 #ifndef RHTREE_HPP
#define RHTREE_HPP

using namespace std;

struct node
{
	int ele;
	node* left;
	node* right;
	node(int e):left(0), right(0){
    ele = e;
    }
};

class RHTree
{
public:
	RHTree();
	~RHTree();
	void insert(int ele);
	void inOrder(node* p);
	void preOrder(node* p);
	void postOrder(node* p);
	node* getRoot();
	void clear(node* p);
private:
	node* root;
};

#endif

 #include "RHTree.hpp"
#include <iostream>

using namespace std;


RHTree::RHTree(){
	root = NULL;
}

RHTree::~RHTree(){
	clear(root);
}

void RHTree::insert(int ele){
	node* temp = new node(ele);
	node* mid = root;
	if(root == NULL)
	{
		root = temp;
		return;
	}
	while(mid != NULL)
	{
  	if(mid->ele >= ele)
  	{
  	    if(mid->left == NULL)
	    {
	        mid->left = temp;
			break;
		}
		else
		{
			mid = mid->left;
		}	
	}
	else if(mid->ele < ele)
	{
		if(mid->right == NULL)
		{
			mid->right = temp;
			break;
		}
		else
		{
			mid = mid->right;
		}
		  
    }
    else
    {
    	delete temp;
    	return;
	}
	}	
}  // °´Öµ²åÈë


void RHTree::inOrder(node* p){
	if(p != NULL)
	{
		inOrder(p->left);
		cout << " " << p->ele;
		inOrder(p->right);
	}
}

void RHTree::preOrder(node* p){
	if(p != NULL)
	{
		
		cout << " " << p->ele;
		preOrder(p->left);
		preOrder(p->right);
	}
}

void RHTree::postOrder(node* p){
	if(p != NULL)
	{
		postOrder(p->left);
		postOrder(p->right);
		
		cout << " " << p->ele;
	}
}


node* RHTree::getRoot(){
    return root;
}

void RHTree::clear(node* p){
	if(p != NULL)
	{
		clear(p->left);
		clear(p->right);
		delete p;
	}
}
