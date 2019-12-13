#ifndef BT_TREE
#define BT_TREE
#include <iostream>
using namespace std;
struct node {
  int ele;
  node* left;
  node* right;
  node(int e):left(0), right(0){
    ele = e;
  }
};
class BinaryTree {
  private:
    node* root;
    // 此处四个函数均为辅助函数
    static void MemoryDelete(node* p);  // 内存处理的辅助函数
    static void BuildTree(const node* Source_Root, node* &Target_Root);  // 拷贝构造函数的辅助函数
    static void BuildTree(const int* arr,int len, node* &root);  // 数组构建树的辅助函数
    static void preorder(const node* p);    // 输出的辅助函数
  public:
    BinaryTree();
    BinaryTree(const BinaryTree&);
    BinaryTree(const int* arr, int len);
    void ResetTree(const int* arr, int len);  // 清空当前树并重置
    ~BinaryTree();
    void clear();  // 清空
    void insert(int ele);  // 按值插入
    void Delete(int ele);  // 暗值删除
    void print();
};
#endif


#include "BinaryTree.hpp" 

using namespace std;

    // 此处四个函数均为辅助函数
void BinaryTree::MemoryDelete(node* p){
	if(p != NULL)
	{
		MemoryDelete(p->left);
		MemoryDelete(p->right);
		delete p;		
	}
}  // 内存处理的辅助函数

void BinaryTree::BuildTree(const node* Source_Root, node* &Target_Root){
	if(Source_Root != NULL)
	{
		Target_Root = new node(Source_Root->ele);
		BuildTree(Source_Root->left, Target_Root->left);
		BuildTree(Source_Root->right, Target_Root->right);
	}
	else
	  Target_Root=NULL;
    
}  // 拷贝构造函数的辅助函数

void BinaryTree::BuildTree(const int* arr,int len, node* &root){
	
	for(int i = 0; i < len; i++)
	{
		if(i == 0)
		{
			root = new node(arr[i]);
		}
		else
		{
	node *temp = new node(arr[i]);
	node* mid=root;
	while(mid != NULL)
	{
  	if(mid->ele > arr[i])
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
	else if(mid->ele < arr[i])
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
		break;
	}	
	}
		}
		
	}
}  // 数组构建树的辅助函数

void BinaryTree::preorder(const node* p){
    if(p != NULL)
    {
        cout << p->ele << " ";
        preorder(p->left);
        preorder(p->right);
    }  
}    // 输出的辅助函数


BinaryTree::BinaryTree(){
	root = NULL;
}

BinaryTree::BinaryTree(const BinaryTree& tre){
	BuildTree(tre.root, root);
}

BinaryTree::BinaryTree(const int* arr, int len){
	root = NULL;
	BuildTree(arr, len, root);
}

void BinaryTree::ResetTree(const int* arr, int len){
	clear();
	BuildTree(arr, len, root);
}  // 清空当前树并重置

BinaryTree::~BinaryTree(){
	MemoryDelete(root);
}

void BinaryTree::clear(){
    MemoryDelete(root);
    root = NULL;
}  // 清空

void BinaryTree::insert(int ele){
	node *temp = new node(ele);
	node *mid = root;
	if(root == NULL)
	{
		root = temp;
		return;
	}
	while(mid != NULL)
	{
  	if(mid->ele > ele)
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
}  // 按值插入

void BinaryTree::Delete(int ele){
	node *mid = root;
	node *flag = NULL;
	node* flag2 = NULL;
	while(mid != NULL)
	{
			if(mid->ele == ele)
			{
				node* temp = mid->left;
				if(temp == NULL)
				{
					if(mid->right == NULL)
					{
						delete mid;
						if(flag == NULL)
						{
						    mid = NULL;
						    root = NULL;
						    //cout<<"hi"<<endl;
							return;
						}
						else if(flag->left == mid)
						{
							flag->left = NULL;
						}
						else
						{
							flag->right = NULL;
						}
						return;
					}
					else
					{
						if(flag == NULL)
						{
							root = mid->right;
					        delete mid;
						}
						else if(flag->left == mid)
						{
							flag->left = mid->right;
						}
						else
						{
							flag->right = mid->right;
						}
					return;
					}
				}
				else
				{
					
					if(temp->right == NULL)
					{	
				        mid->ele = temp->ele;
				        mid->left = temp->left;
				        delete temp;
				        return;
					}
					while(temp->right != NULL)
				    {
				    	flag2 = temp;
					    temp = temp->right;
				    }
				    
				}
				
				mid->ele = temp->ele;
				flag2->right = temp->left;
				
				delete temp;
				return;
			}
		else if(mid->ele > ele)
		{
			if(mid->left != NULL)
			{
				flag = mid;
				mid = mid->left;
			}
			else
			{
				return;
			}
		}
		else if(mid->ele < ele)
		{
			if(mid->right != NULL)
			{
				flag = mid;
				mid = mid->right;
			}
			else
			{
				return;
			}
		}
	}
}  // 暗值删除

void BinaryTree::print(){
	if(root == NULL)
	{
		cout << endl;
		return;
	}
	preorder(root);
	cout << endl;
}



#include "BinaryTree.hpp"
void Test1() {
  BinaryTree t1;
  t1.print();
  int len;
  cin >> len;
  int* arr = new int[len+1];
  int index = 0;
  while (index < len) cin >> arr[index++];
  //cout<<"hi"<<endl;
  
  BinaryTree t2(arr, len);
  //t2.test();
  t2.print();
  int inser;
  int times;
  cin >> times;
  while (times--) {
    cin >> inser;
    t2.insert(inser);
  }
  t2.print();
  
  cin >> times;
  int del;
  while (times--) {
    cin >> del;
    t2.Delete(del);
  }
  //t2.test();
  BinaryTree t3 = t2;
  t3.print();
  t3.clear();
  t3.clear();
  t3.print();
  t2.print();
  // cout << &t3 << endl;
  // cout << &t2 << endl;
  delete []arr;
}

void Test2() {
  BinaryTree t1;
  t1.Delete(10);
  t1.clear();
  t1.print();
  int times;
  int tmp;
  cin >> times;
  while (times--) {
    cin >> tmp;
    t1.insert(tmp);
  }
  t1.Delete(tmp);
  t1.print();
}
void Test3() {
  int arr[10] = {9,4,3,1,2,10,15,17,18,6};
  BinaryTree t1(arr, 10);
  t1.print();
  arr[9] = 5;
  t1.ResetTree(arr, 10);
  t1.print();
  t1.clear();
  t1.ResetTree(arr, 10);
  t1.print();
}
int main() {
  Test1();
  Test2();
  Test3();
}
