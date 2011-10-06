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

int main()
{
    int i;
    BinaryTree<int> T;
    TNode<int>      *node;
    T.insert(5);
    T.insert(4);
    T.insert(2);
    T.insert(3);
    T.insert(10);
    T.insert(6);
    T.insert(11);
    T.inorder();
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
    node = T.iter_search(5);
    node = T.dele(node);
    if (node)
        cout << "node " << node->data << " is deleted" << endl;
    T.inorder();
    T.level_order();
    return 0;
}
