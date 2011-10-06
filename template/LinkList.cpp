// =====================================================================================
// 
//       Filename:  LinkList.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  10/03/2010 06:23:22 PM
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
    Node *next;
public:
    Node():  next(NULL) {}
    Node(C elem):next(NULL) { data = elem; }
    Node(C elem, Node<C> *pnext)
    {
        next = pnext;
        data = elem;
    }
};

template <class C> class LinkList
{
    Node<C> head, *tail;
public:
    LinkList():tail(NULL){ }
    void insert(C element)
    {
        Node<C> *elem = new Node<C>(element, head.next);
        if (!head.next)
            tail = elem;
        head.next = elem;
    }
    void append(C element)
    {
        tail->next = new Node<C>(element);
        tail = tail->next;
    }
    void invert()
    {
        Node<C> *first, *middle, *last;
        first = &head;
        while(first && first->next && first->next->next)
        {
            middle = first->next;
            last   = first->next->next;

            /* Adjust first middle last */
            first->next = last;
            middle->next = last->next;
            last->next = middle;

            /* point to next */
            first = first->next->next;
        }
        /* List contain more than 2 elements and 
         * the list have even elements*/
        if (!first->next && first != &head)
            tail = middle;
    }
    void show_tail()
    {
        cout << "last element in list is: " << tail->data << endl;
    }
    void show()
    {
        Node<C> *elem = head.next;
        while(elem)
        {
            cout << elem->data << endl;
            elem = elem->next;
        }
    }
};

int main()
{
    LinkList<int> list;
    int i;
    
    for(i = 0; i < 3; i++)
    {
        list.insert(i);
    }
    list.show();
    list.show_tail();
    list.invert();
    cout << "after invert" << endl;
    list.show();
    list.show_tail();
    list.append(98);
    list.show();
    list.show_tail();
    list.invert();
    cout << "after invert" << endl;
    list.show();
    list.show_tail();

    return 0;
}
