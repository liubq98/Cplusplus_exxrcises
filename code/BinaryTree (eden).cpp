//
//  BinaryTree.hpp
//  C++
//
//  Created by ¿ÓÃÏ≈‡ on 16/5/4.
//  Copyright ? 2016ƒÍ lee. All rights reserved.
//
 
#ifndef BinaryTree_hpp
#define BinaryTree_hpp
 
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
 
#define EMPTY_ELE '#'
 
class BinaryTree {
public:
    struct Node {
        char val;
        Node* left;
        Node* right;
        Node(char v, Node* l = NULL, Node* r = NULL):
        val(v), left(l), right(r) {
        }
    };
    BinaryTree(const BinaryTree&);
    BinaryTree(std::vector<char>&);
    // created by preorder and inorder
    BinaryTree(const std::vector<char>& preOrder,
               const std::vector<char>& inOrder);
    ~BinaryTree();
    BinaryTree& operator=(const BinaryTree&);
    Node* getRoot() const;
    void clear();
    
    static void preOrder(void (*visite)(BinaryTree::Node*), Node*);
    static void inOrder(void (*visite)(BinaryTree::Node*), Node*);
    static void postOrder(void (*visite)(BinaryTree::Node*), Node*);
    
 
private:
    Node * copyNode(Node * oldNode, Node * newNode);
    
    Node * root;
};

#endif

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
//#include "BinaryTree.hpp"

BinaryTree::Node* creat(char* preOrder, char* inOrder, int size);

BinaryTree::Node* creat(char* preOrder, char* inOrder, int size){
	if(size == 0)
	{
		return NULL;
	}
	else
	{
		BinaryTree::Node* temp = new BinaryTree::Node(preOrder[0], NULL, NULL);
		int i, flag;
		for(i = 0; i < size; i++)
		{
			if(preOrder[0] == inOrder[i])
			{
				flag = i;
				break;
			}
		}
		
		int lnum = flag;
		int rnum = size - flag - 1;
		
		if(lnum == 0)
		{
			temp->left = NULL;
		}
		else
		{
			temp->left = creat(&(preOrder[1]), &(inOrder[0]), lnum);
		}
		
		if(rnum == 0)
		{
			temp->right = NULL;
		}
		else
		{
			temp->right = creat(&preOrder[flag + 1], &(inOrder[flag + 1]), rnum);
		}
		
		return temp;
	}

}

BinaryTree::BinaryTree(const BinaryTree& b){
	root = NULL;
	root = copyNode(b.getRoot(), root);
}

BinaryTree::BinaryTree(std::vector<char>& c){
	root = NULL;
	if(c.empty() || c[0] == '#')
	{
		root = NULL;
	}
	else
	{
		int len = c.size();
		root = new Node(c[0], NULL, NULL);
		std::queue<Node*> q;
		q.push(root);
		
		for(int i = 1; i < len; i++)
		{
			Node* temp = q.front();
			q.pop();
			if(c[i] != '#')
			{
				temp->left = new Node(c[i], NULL, NULL);
				q.push(temp->left);
			}
			
			i++;
			if(i >= len)
			{
				break;
			}
			
			if(c[i] != '#')
			{
				temp->right = new Node(c[i], NULL, NULL);
				q.push(temp->right);
			}
		}
	}
}

// created by preorder and inorder
BinaryTree::BinaryTree(const std::vector<char>& preOrder, const std::vector<char>& inOrder){
	root = NULL;
	int psize = preOrder.size();
	int isize = inOrder.size();
	if(psize != isize || psize == 0)
	{
		return;
	}
	char pre[psize];
	char in[psize];
	for(int i = 0; i < psize; i++)
	{
		pre[i] = preOrder[i];
		in[i] = inOrder[i];
	}
	root = creat(pre, in, psize);
}

BinaryTree::~BinaryTree(){
	clear();
}

BinaryTree& BinaryTree::operator=(const BinaryTree& b){
	if(root == b.root)
	{
		return *this;
	}
	
	clear();
	root = copyNode(b.getRoot(), root);
}

BinaryTree::Node* BinaryTree::getRoot() const{
	return root;
}

void BinaryTree::clear(){
	if(root == NULL)
	{
		return;
	}
	
	std::queue<Node*> q;
	q.push(root);
	while(!q.empty())
	{
		Node* temp = q.front();
        q.pop();
        if (temp->left != NULL)
        {
        	q.push(temp->left);
		}
            
        if (temp->right != NULL)
        {
        	q.push(temp->right);
		}
            
        delete temp;
	}
}

    
//static 
void BinaryTree::preOrder(void (*visite)(BinaryTree::Node*), BinaryTree::Node* p){
	if (p != NULL) 
	{
        visite(p);
        preOrder(visite, p->left);
        preOrder(visite, p->right);
    }
}

void BinaryTree::inOrder(void (*visite)(BinaryTree::Node*), BinaryTree::Node* p){
	if (p != NULL) 
	{
        inOrder(visite, p->left);
        visite(p);
        inOrder(visite, p->right);
    }
}

void BinaryTree::postOrder(void (*visite)(BinaryTree::Node*), BinaryTree::Node* p){
	if (p != NULL) 
	{
        postOrder(visite, p->left);
        postOrder(visite, p->right);
        visite(p);
    }
}


//private
BinaryTree::Node* BinaryTree::copyNode(Node * oldNode, Node * newNode){
	if (oldNode == NULL) 
	{
        newNode = NULL;
    }
    else
    {
    	newNode = new Node(oldNode->val, NULL, NULL);
        newNode->left = copyNode(oldNode->left, newNode->left);
        newNode->right = copyNode(oldNode->right, oldNode->right);
	}
return newNode;
}


#include <iostream>
//#include "BinaryTree.hpp"
 
using namespace std;
 
void print(BinaryTree::Node * temp) {
    cout << temp->val << " ";
}
 
std::vector<char> pre;
std::vector<char> in;
 
void getPreOrder(BinaryTree::Node * temp) {
    pre.push_back(temp->val);
}
 
void getInOrder(BinaryTree::Node * temp) {
    in.push_back(temp->val);
}
 
void testTree() {
    cout << "test Tree" << endl;
    int n = 1;
    std::vector<char> tree;
    cin >> n;
    while (n--) {
        char temp = '\0';
        cin >> temp;
        tree.push_back(temp);
    }
 
    BinaryTree x = BinaryTree(tree);
    x = x;
    BinaryTree::preOrder(print, x.getRoot());
    cout << endl;
    BinaryTree::inOrder(print, x.getRoot());
    cout << endl;
    BinaryTree::postOrder(print, x.getRoot());
    cout << endl;
 
    BinaryTree::preOrder(getPreOrder, x.getRoot());
    BinaryTree::inOrder(getInOrder, x.getRoot());
 
    BinaryTree t = BinaryTree(pre, in);
    t = t;
    BinaryTree::postOrder(print, t.getRoot());
    cout << endl;
 
    BinaryTree y = BinaryTree(t);
    y = y;
    BinaryTree::preOrder(print, y.getRoot());
    cout << endl;
    BinaryTree::inOrder(print, y.getRoot());
    cout << endl;
    BinaryTree::postOrder(print, y.getRoot());
 
    BinaryTree::preOrder(getPreOrder, y.getRoot());
    BinaryTree::inOrder(getInOrder, y.getRoot());
}
 
int main() {
    testTree();
}
