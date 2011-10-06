// =====================================================================================
// 
//       Filename:  DlinkList.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  10/05/2010 04:38:14 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  YOUR NAME (), 
//        Company:  
// 
// =====================================================================================

#include	<iostream>
using namespace std;

template <class C> class Node
{
public:
    C data;
    Node *prior;
    Node *next;
public:
    Node():  prior(NULL),next(NULL) {}
    Node(C elem):prior(NULL),next(NULL) { data = elem; }
    Node(C elem, Node<C> *pnext)
    {
        next = pnext;
        data = elem;
    }
};

template <class C> class DlinkList
{
    Node<C> *head;
public:
    DlinkList():head(NULL) {}
    void insert(C element)
    {
        Node<C> *tmp ;
        Node<C> *node = new Node<C>(element);
        if (!head)
        {
            head = node;
            node->prior = node;
            node->next  = node;
        }
        else
        {
            tmp = head;
            node->next = head;
            node->prior = head->prior;
            
            head->prior->next = node;
            head->prior = node;

            head = node;
        }
    }
    void show()
    {
        Node<C> *tmp = head;
        do
        {
            cout << tmp->data << endl;
            tmp = tmp->next;
        }while(tmp!=head);
    }
};

int main()
{
    int i;
    DlinkList<int> list;
    for(i = 0; i < 3; i++)
    {
        list.insert(i);
    }
    list.show();
    return 0;
}
