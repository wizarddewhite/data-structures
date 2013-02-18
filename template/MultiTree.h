/*
 * =====================================================================================
 *
 *       Filename:  MultiTree.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/18/2013 11:02:07 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef    __MULTITREE_H__
#define    __MULTITREE_H__
#include	<iostream>
#include	<iomanip>
using namespace std;
#include	"Stack.h"
#include	"Queue.h"

template <class C> class TNode
{
public:
    C        data;
    TNode<C> *parent;
    TNode<C> *child;
    TNode<C> *peer;
    TNode():parent(NULL),child(NULL), peer(NULL) {}
    TNode(C elem, TNode<C> *p):parent(p),child(NULL), peer(NULL) 
    {
        data = elem;
    }
};

template <class C> class MultiTree
{
	TNode<C> *root;

	void __inorder(TNode<C> *t, int level)
	{
		if (!t)
			return;

		if (t->child)
			__inorder(t->child, level + 1);
		    
		cout.setf(ios::right);
		cout << setw(level*3) << t->data << "(" << level << ")" << endl;
		    
		if (t->peer)
			__inorder(t->peer, level + 1);
	}

public:
	MultiTree(): root(NULL) {}

	TNode<C>* insert(TNode<C> *parent, C leaf)
	{
		TNode<C> *node;

		if (!parent) {
			if (!root) {
				/* This is an empty tree */
				root = new TNode<C>(leaf, NULL);
				return root;
			}
			else {
				cout << "Error inserting a node without parent!" << endl;
				return NULL;
			}
		}

		node = parent->child;

		if (!node){
			parent->child = new TNode<C>(leaf, parent);
			return parent->child;
		}

		while (node->peer)
			node = node->peer;

		node->peer = new TNode<C>(leaf, parent);
		return node->peer;
	}

	void inorder()
	{
		__inorder(root, 0);
	}
	
};
#endif 
