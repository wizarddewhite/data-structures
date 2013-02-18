// =====================================================================================
// 
//       Filename:  BinaryTree.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  10/06/2010 03:06:12 PM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  YOUR NAME (), 
//        Company:  
// 
// =====================================================================================
#include	<iostream>
#include	"BinaryTree.h"
using namespace std;

void create_bt(BinaryTree<int> *T)
{
    T->insert(5);
    T->insert(4);
    T->insert(2);
    T->insert(3);
    T->insert(10);
    T->insert(6);
    T->insert(11);
}

TNode<int>* search(BinaryTree<int> *T, int val)
{
	return T->iter_search(val);
}

int main()
{
    BinaryTree<int> T;
    create_bt(&T);
//    cout << "iter inorder" << endl;
//    T.iter_preorder();
//    T.level_order();
//    node = T.min();
//    cout << "found node " << node->data << endl;
//    while (node)
//    {
//        node = T.successor(node);
//        if (node)
//        cout << "found node " << node->data << endl;
//    }
//    node = T.max();
//    cout << "found node " << node->data << endl;
//    while (node)
//    {
//        node = T.predecessor(node);
//        if (node)
//        cout << "found node " << node->data << endl;
//    }
    T.inorder();
    return 0;
}
