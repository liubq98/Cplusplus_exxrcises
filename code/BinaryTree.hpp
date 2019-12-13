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
    // �˴��ĸ�������Ϊ��������
    static void MemoryDelete(node* p);  // �ڴ洦��ĸ�������
    static void BuildTree(const node* Source_Root, node* &Target_Root);  // �������캯���ĸ�������
    static void BuildTree(const int* arr,int len, node* &root);  // ���鹹�����ĸ�������
    static void preorder(const node* p);    // ����ĸ�������
  public:
    BinaryTree();
    BinaryTree(const BinaryTree&);
    BinaryTree(const int* arr, int len);
    void ResetTree(const int* arr, int len);  // ��յ�ǰ��������
    ~BinaryTree();
    void clear();  // ���
    void insert(int ele);  // ��ֵ����
    void Delete(int ele);  // ��ֵɾ��
    void print();
};
#endif
