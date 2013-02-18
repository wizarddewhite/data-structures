// =====================================================================================
// 
//       Filename:  MultiTree.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  02/18/2013 11:01:37 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  YOUR NAME (), 
//        Company:  
// 
// =====================================================================================
#include	<iostream>
#include	"MultiTree.h"
using namespace std;

/*
 * create a tree like:
 *               1
 *              /
 *             2 -- 3 -- 4
 *            /
 *           5 -- 6
 *               /
 *              7
 */
void create_mt(MultiTree<int> *T)
{
	TNode<int> *parent = NULL;
	TNode<int> *parent1 = NULL;

	parent = T->insert(NULL, 1);
	parent1 = T->insert(parent, 2);
	T->insert(parent, 3);
	T->insert(parent, 4);

	T->insert(parent1, 5);
	parent = T->insert(parent1, 6);

	T->insert(parent, 7);
}

int main()
{
	MultiTree<int> T;

	create_mt(&T);
	T.inorder();
	return 0;
}
