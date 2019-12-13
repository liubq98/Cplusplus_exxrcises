#ifndef BEAUTIFULTREE_HPP
#define BEAUTIFULTREE_HPP

#include <iostream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

namespace HFM{
	struct node{
		int e;
		char id;
		node* left;
		node* right;
		node* parent;
		string code;
		
		node(int num,char _id){
			id = _id;
			e = num;
			left = NULL;
			right = NULL;
			parent = NULL;
			code = ""; 
		}
	};
			
	class HuffmanCode{
		public:
			HuffmanCode(string &str);
			~HuffmanCode();
			HuffmanCode(int w[], int n);
			void DisplayCode();
			void tra(node* temp, string str);
			void tra2(node* temp, vector<node*>& v);
			string find(vector<node*> v, char _id);
			void tra3(node* temp);
		private:
			bool flag;
			int count;
			node* root;
			string tree;
	};
}



#endif


#include <iostream>
#include <cstring>
#include <string>
#include <vector>
//#include "BeautifulTree.hpp"

using namespace std;
using namespace HFM;

HuffmanCode::~HuffmanCode(){
	tra3(root);
}

HuffmanCode::HuffmanCode(string &str){
	vector<node*> v;
	int len = str.size();
	int num[26] = {0};
	string str1;
	for(int i = 0; i < len; i++)
	{
		if(str[i] < 'a' || str[i] > 'z')
		{
			continue;
		}
		else
		{
			num[str[i] - 'a']++;
			str1 += str[i];
		}
	}
	tree = str1;
	
	for(int i = 0; i < 26; i++)
	{
		if(num[i] != 0)
		{
			node* temp = new node(num[i], i + 'a');
			v.push_back(temp);
		}
	}
	count = v.size();
	
	while(v.size() != 1)
	{
		int len3 = v.size();
		int min1 = v[0]->e;
		int ind1 = 0;
		for(int i = 0; i < len3; i++)
		{
			if(v[i]->e < min1)
			{
				min1 = v[i]->e;
				ind1 = i;
			}
		}
		
		int min2 = 100;
		int ind2 = 0;
		for(int i = 0; i < len3; i++)
		{
			if(i != ind1 && v[i]->e < min2)
			{
				min2 = v[i]->e;
				ind2 = i;
			}
		}
		
		int newnum = min1 + min2;
		node* newnode = new node(newnum, ' ');
		newnode->left = v[ind1];
		newnode->right = v[ind2];
		v[ind1]->parent = newnode;
		v[ind2]->parent = newnode;
		
		v.erase(v.begin() + ind1);
		if(ind1 < ind2)
		{
			v.erase(v.begin() + ind2 - 1);
		}
		else
		{
			v.erase(v.begin() + ind2);
		}
		
		v.push_back(newnode);
	}
	
	root = v[0];
	flag = false;
	
	tra(root->left, "1");
	tra(root->right, "0");
}

HuffmanCode::HuffmanCode(int w[], int n){
	count = n;
	flag = true;
	vector<node*> v;
	for(int i = 0; i < n; i++)
	{
		node* temp = new node(w[i], i + 'a');
		v.push_back(temp);
	}
	while(v.size() != 1)
	{
		int len3 = v.size();
		int min1 = v[0]->e;
		int ind1 = 0;
		for(int i = 0; i < len3; i++)
		{
			if(v[i]->e < min1)
			{
				min1 = v[i]->e;
				ind1 = i;
			}
		}
		
		int min2 = 100;
		int ind2 = 0;
		for(int i = 0; i < len3; i++)
		{
			if(i != ind1 && v[i]->e < min2)
			{
				min2 = v[i]->e;
				ind2 = i;
			}
		}
		
		int newnum = min1 + min2;
		node* newnode = new node(newnum, ' ');
		newnode->left = v[ind1];
		newnode->right = v[ind2];
		v[ind1]->parent = newnode;
		v[ind2]->parent = newnode;
		
		v.erase(v.begin() + ind1);
		if(ind1 < ind2)
		{
			v.erase(v.begin() + ind2 - 1);
		}
		else
		{
			v.erase(v.begin() + ind2);
		}
		
		v.push_back(newnode);
	}
	
	root = v[0];
	
	tra(root->left, "1");
	tra(root->right, "0");
}

void HuffmanCode::DisplayCode(){
	vector<node*> v;
	if(flag)
	{
		tra2(root, v);
		vector<node*> v3;
		for(int i = 0; i < 26; i++)
		{
			for (int j = 0; j < v.size(); j++)
			{
				if((i + 'a') == v[j]->id)
				{
					v3.push_back(v[j]);
				}
			}
		}
		
		vector<node*> v2 = v3;
		
		for(int i = 0; i < count; i++)
		{
			int min = v3[0]->e;
			int ind = 0;
			for(int j = 0; j < v3.size(); j++)
			{
				if(v3[j]->e < min)
				{
					min = v3[j]->e;
					ind = j;
				}
			}
			cout << "Weight = " << min << "; Code = " << v3[ind]->code << endl;
			
			v3.erase(v3.begin() + ind);
			
		}
		
		int length = 0;
		for(int i = 0; i < v2.size(); i++)
		{
			length += v2[i]->e * (v2[i]->code).size();
		}
		
		cout << "Huffman's codeLength = " << length << endl;
	}
	else
	{
		tra2(root, v);
		vector<node*> v3;
		for(int i = 0; i < 26; i++)
		{
			for (int j = 0; j < v.size(); j++)
			{
				if((i + 'a') == v[j]->id)
				{
					v3.push_back(v[j]);
				}
			}
		}
		vector<node*> v2 = v3;
		
		for(int i = 0; i < count; i++)
		{
			int min = v3[0]->e;
			int ind = 0;
			for(int j = 0; j < v3.size(); j++)
			{
				if(v3[j]->e < min)
				{
					min = v3[j]->e;
					ind = j;
				}
			}
			cout << "(" << v3[ind]->id << ") "<< "Weight = " << min << "; Code = " << v3[ind]->code << endl;
			
			v3.erase(v3.begin() + ind);
			
		}
		
		int length = 0;
		for(int i = 0; i < v2.size(); i++)
		{
			length += v2[i]->e * (v2[i]->code).size();
		}
		
		cout << "Huffman's codeLength = " << length << endl;
		
		cout << "Origin Text: " << tree << endl;
		cout << "Huffman's Code: ";
		for(int i = 0; i < tree.size(); i++)
		{
			char ch = tree[i];
			string str = find(v2, ch);
			cout << str;
		}
		cout << endl;
	}
}

void HuffmanCode::tra(node* temp, string str){
	if(temp != NULL)
	{
		temp->code = temp->parent->code + str;
		tra(temp->left, "1");
		tra(temp->right, "0");
	}
}


void HuffmanCode::tra2(node* temp, vector<node*>& v){
	if(temp->left != NULL && temp->right != NULL)
	{
		tra2(temp->left, v);
		tra2(temp->right, v);
	}
	if(temp->left == NULL && temp->right == NULL)
	{
		v.push_back(temp);
	}
	
}

string HuffmanCode::find(vector<node*> v, char _id){
	for(int i = 0; i < v.size(); i++)
	{
		if(v[i]->id == _id)
		{
			return v[i]->code;
		}
	}
}

void HuffmanCode::tra3(node* temp){
	if(temp != NULL)
	{
		tra3(temp->left);
		tra3(temp->right);
		delete temp;
	}
}


#include <iostream>
#include <cstring>
#include <string>
//#include "BeautifulTree.hpp"
using namespace std;
using namespace HFM;

 void test_HFM() {
    cout << "---------- test_HFM ----------\n# TEST_1\n";
    int weight[] = { 7, 4, 5, 2 };
    int count = 4;
    HuffmanCode HFC(weight, count);
    HFC.DisplayCode();
    cout << "\nTEST_2\n";
    string input = "you are the apple in my eyes";
    HuffmanCode HFC_2(input);
    HFC_2.DisplayCode();
}
 void hard_test() {
    cout << "---------- test_HFM ----------\n# TEST_1\n";
    int count, weight_arr[20] = {0};
    cin >> count;
    for (int i = 0; i < count; i++) cin >> weight_arr[i];
    HuffmanCode HFC(weight_arr, count);
    HFC.DisplayCode();
    cout << "\nTEST_2\n";
    string input = "";
    cin >> input;
    HuffmanCode HFC_2(input);
    HFC_2.DisplayCode();
}
 int main() {
    int t;
    cin >> t;
    if (t == 0) {
        test_HFM();
    } else {
        hard_test();
    }
    return 0;
}
/*
 namespace HFM {
 class HuffmanCode {
   public:
    explicit
    HuffmanCode(const string &str)
    HuffmanCode(int w[], int n)
    void DisplayCode()
 };
}  // namespace HFM
*/
 
