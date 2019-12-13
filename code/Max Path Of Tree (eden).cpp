#include <iostream>

#define MAX_INIT 100

using namespace std;


namespace MP {
struct TreeNode{
	int val;
	int id;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x, int i){
		val = x;
		i = id;
		left = NULL;
		right = NULL;
	}
}; 

class MaxPath {
private:
    int max;
public:
    MaxPath() : max(MAX_INIT) {}
    int findMaxPath(TreeNode *root);
    int find(TreeNode* node, int num);
};
 }  // namespace MP


#include <iostream>
//#include "MP.hpp"

using namespace std;
using namespace MP;

int MaxPath::findMaxPath(TreeNode *root){
	if(root == NULL)
	{
		return 0;
	}
	
	if(root != NULL)
	{
		int lnum = find(root->left, root->val);
		int rnum = find(root->right, root->val);
		return (lnum > rnum ? lnum : rnum);
	}
}

int MaxPath::find(TreeNode* node, int num){
	if(node == NULL)
	{
		return num;
	}
	
	if(node != NULL)
	{
		int ltemp = find(node->left, node->val);
		int rtemp = find(node->right, node->val);
		return (num + (ltemp > rtemp ? ltemp : rtemp));
	}
}



#include <iostream>
#include <cstring>
#include <string>
//#include "MP.hpp"
using namespace std;
using namespace MP;
 void test_MP() {
    cout << "---------- test_MP ----------\n";
    TreeNode *n[9];
    n[0] = new TreeNode(1, 0);
    n[1] = new TreeNode(1, 1);
    n[2] = new TreeNode(3, 2);
    n[0]->left = n[1];
    n[0]->right = n[2];
    n[3] = new TreeNode(0, 3);
    n[4] = new TreeNode(1, 4);
    n[1]->left = n[3];
    n[1]->right = n[4];
    n[5] = new TreeNode(1, 5);
    n[6] = new TreeNode(1, 6);
    n[2]->left = n[5];
    n[2]->right = n[6];
    n[7] = new TreeNode(1, 7);
    n[8] = new TreeNode(0, 8);
    n[4]->left = n[7];
    n[4]->right = n[8];
    MaxPath tree;
    cout << "MaxPathValue: ";
    cout << tree.findMaxPath(n[0]) << "\n";
    for (int i = 0; i < 9; i++) delete n[i];
}

 void hard_test() {
    cout << "---------- test_MP ----------\n";
    TreeNode *n[9];
    int weight;
    for (int i = 0; i < 9; i++) {
        cin >> weight;
        n[i] = new TreeNode(weight, i);
    }
    n[0]->left = n[1];
    n[0]->right = n[2];
    n[1]->left = n[3];
    n[2]->left = n[5];
    n[2]->right = n[6];
    n[4]->left = n[7];
    n[4]->right = n[8];
    MaxPath tree;
    cout << "MaxPathValue: ";
    cout << tree.findMaxPath(n[0]) << "\n";
    for (int i = 0; i < 9; i++) delete n[i];
}
 int main() {
    int t;
    cin >> t;
    if (t == 0) {
        test_MP();
    } else {
        hard_test();
    }
    return 0;
}
  /**
 * Hope you can enjoy this problem.
 * - by Carson 2016.4.24
 namespace MP {
 struct TreeNode;
 class MaxPath {
private:
    int max;
public:
    MaxPath() : max(MAX_INIT) {}
    int findMaxPath(TreeNode *root)
};
 }  // namespace MP

*/
 
