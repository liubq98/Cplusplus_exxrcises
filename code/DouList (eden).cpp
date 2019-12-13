#include <string>
#include <iostream>
#include <sstream>
#include "DouList.h"

using namespace std;

DouList::DouList(){
    m_head = NULL;
    m_tail = NULL;
}

DouList::DouList(const DouList &src){
    if(src.m_head == NULL)
    {
        m_head = NULL;
        m_tail = NULL;
        return;
    }

    m_head = new DouListNode;
    m_head->elem = src.m_head->elem;
    m_head->prev = NULL;
    m_head->next = NULL;

    m_tail = m_head;

    DouListNode* ptr = src.m_head;
    if(ptr == src.m_tail)
    {
        return;
    }
    while(ptr != src.m_tail)
    {
        ptr = ptr->next;
        DouListNode* temp = new DouListNode;
        temp->elem = ptr->elem;
        temp->prev = m_tail;
        m_tail->next = temp;
        temp->next = NULL;

        m_tail = temp;
    }
}

DouList::~DouList(){
    clear();
}

void DouList::clear(){
    if (m_head != NULL) 
    {
        DouListNode* p = m_head;
        while (p != NULL) 
        {
            DouListNode* temp = p;
            p = p->next;
            delete temp;
            if(p != NULL)
            {
                p->prev = NULL;
            }
            
        }
        m_head = NULL;
        m_tail = NULL;
    }
}

bool DouList::empty() const{
    return (m_head == NULL);
}

string DouList::to_str() const{
    string str, str1;
    if(empty())
    {
        str = "[]";
    }
    else
    {
        stringstream ss;
        ss << m_head->elem;
        ss >> str1;
        str = "[" + str1;
        DouListNode* p = m_head->next;
        while(p != NULL)
        {
            ss.clear();
            ss << p->elem;
            ss >> str1;
            str = str + ", " + str1;
            p = p->next;
        }
        str = str + "]";
    }
return str;
}

int DouList::front() const{
    return m_head->elem;
}

int DouList::back() const{
    return m_tail->elem;
}

void DouList::push_front(const int &e){
    DouListNode* temp = new DouListNode(e, NULL, m_head);
    if(m_head != NULL)
    {
        m_head->prev = temp;
    }
    
    if(m_head == NULL)
    {
        m_tail = temp;
    }
    
    m_head = temp;
}

void DouList::push_back(const int &e){
    DouListNode* temp = new DouListNode(e, m_tail, NULL);
    if(m_tail != NULL)
    {
        m_tail->next = temp;
    }
    
    if(m_tail == NULL)
    {
        m_head = temp;
    }
    
    m_tail = temp;
}

void DouList::pop_front(){
    DouListNode* temp = m_head;
    m_head = m_head->next;
    delete temp;
    m_head->prev = NULL;
}

void DouList::pop_back(){
    DouListNode* temp = m_tail;
    m_tail = m_tail->prev;
    delete temp;
    m_tail->next = NULL;
}

DouList& DouList::operator=(const DouList &other){
    if(other.m_head == m_head)
    {
        return *this;
    }
    clear();
    if(other.m_head == NULL)
    {
        m_head = NULL;
        m_tail = NULL;
        return *this;
    }

    m_head = new DouListNode;
    m_head->elem = other.m_head->elem;
    m_head->prev = NULL;
    m_head->next = NULL;

    m_tail = m_head;

    DouListNode* ptr = other.m_head;
    if(ptr == other.m_tail)
    {
        return *this;
    }
    while(ptr != other.m_tail)
    {
        ptr = ptr->next;
        DouListNode* temp = new DouListNode;
        temp->elem = ptr->elem;
        temp->prev = m_tail;
        m_tail->next = temp;
        temp->next = NULL;

        m_tail = temp;
    }
return *this;
}

//friend 
ostream& operator<<(ostream &out, const DouList &list){
    out << list.to_str();
return out;
}

