 #ifndef STACK_H
#define STACK_H

#include <iostream>
#include "Stack.h"

using namespace std;

template<typename T>

class Stack {  
    public:  
        Stack(){
            top_node = NULL;
            node_num = 0;
        }

        Stack(const Stack &stack){
            node_num = stack.node_num;
            if(stack.top_node == NULL)
            {
                top_node = NULL;
                return;
            }

            for(int i = 0; i < node_num; i++)
            {
                Node* temp1 = stack.top_node;
                for(int j = 0; j < node_num - i - 1; j++)
                {
                    temp1 = temp1->next;
                }
                Node* temp = new Node(temp1->element, NULL);
                if(i == 0)
                {
                    top_node = temp;
                }
                else
                {
                    temp->next = top_node;
                    top_node = temp;
                }
            }
        }

        ~Stack(){
            clear();
        }

        bool empty(){
            return (node_num == 0);
        }

        size_t size() const{
            return node_num;
        }

        T top() const{
            return top_node->element;
        }

        void push(T element){
            Node* temp = new Node(element, NULL);
            if(top_node == NULL)
            {
                top_node = temp;
            }
            else
            {
                temp->next = top_node;
                top_node = temp;
            }
            node_num++;
        }

        void pop(){
            if(top_node == NULL)
            {
                return;
            }

            Node* temp = top_node;
            top_node = top_node->next;
            delete temp;
            node_num--;
        }

        void swap(Stack& stack){
            Node* temp1 = stack.top_node;
            Node* temp2 = top_node;
            for(int i = 0; i < node_num; i++)
            {
                T temp = temp1->element;
                temp1->element = temp2->element;
                temp2->element = temp;
                temp1 = temp1->next;
                temp2 = temp2->next;
            }
        }

        void reverse(){
            T arr[node_num];
            Node* temp1 = top_node;
            for(int i = 0; i < node_num; i++)
            {
                arr[i] = temp1->element;
                temp1 = temp1->next;
            }
            for(int i = 0; i < node_num; i++)
            {
                Node* temp2 = top_node;
                for(int j = 0; j < node_num - i - 1; j++)
                {
                    temp2 = temp2->next;
                }
                temp2->element = arr[i];
            }
        } /*reverse the elements' order in the stack*/

        void clear(){
            while(top_node)
            {
                Node* temp = top_node;
                top_node = top_node->next;
                delete temp;
            }
            node_num = 0;
        }

    private:  
        struct Node {  
            T element;  
            Node* next;  
            Node(T ele, Node *n = NULL) {  
                element = ele;  
                next = n;  
            }  
        };  
        Node *top_node;  
        size_t node_num;  
};


#endif
