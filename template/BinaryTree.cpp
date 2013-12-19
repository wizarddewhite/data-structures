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

void BT_traverse()
{
    BinaryTree<int> T;
    create_bt(&T);
    cout << "BinaryTree inorder traverse" << endl;
    T.inorder();
}

void BT_depth_first()
{
    BinaryTree<int> T;

    T.insert(5);
    T.insert(104);
    T.insert(2);
    T.insert(3);
    T.insert(10);
    T.insert(130);
    T.insert(60);
    T.insert(9);
    T.insert(78);
    T.insert(11);
    T.insert(8);

    cout << "BinaryTree inorder traverse" << endl;
    T.inorder();

    /* You see the depth-first traverse result
     * is ordered
     */
    cout << "BinaryTree depth-first traverse" << endl;
    T.depth_first();
}

int main()
{
	BT_depth_first();
	return 0;
}
