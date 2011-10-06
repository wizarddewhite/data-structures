// =====================================================================================
// 
//       Filename:  delete.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  10/01/2010 11:25:29 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  YOUR NAME (), 
//        Company:  
// 
// =====================================================================================
#include <iostream>
using namespace std;

#define null 0
struct node
{
    int data;
    node* next;
};

int main()
{
    node head;
    int i;
    head.data = 0;
    head.next = null;
    node* p = &head;
    
    /* init the link list */
    for(i = 0; i<6; i++)
    {
        p->next = new node;
        p = p->next;
        p->data = i;
    }
    p->next = head.next;

    /* delete one element every two elements */
    p = head.next;
    while(p!=p->next)
    {
        p->next->next = p->next->next->next;
        p=p->next->next;
    }
    cout << p->data << endl;
    return 0;
}
