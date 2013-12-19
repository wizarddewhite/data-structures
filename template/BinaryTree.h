/*
 * =====================================================================================
 *
 *       Filename:  BinaryTree.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/06/2010 05:15:42 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef    __BINARYTREE_H__
#define    __BINARYTREE_H__
#include	<iostream>
#include	<iomanip>
using namespace std;
#include	"Stack.h"
#include	"Queue.h"

enum visit
{
	no,
	once,
	twice
};

template <class C> class TNode
{
public:
    C        data;
    enum visit stat;
    TNode<C> *parent;
    TNode<C> *lchild;
    TNode<C> *rchild;
    TNode():stat(no),parent(NULL),lchild(NULL), rchild(NULL){}
    TNode(C elem, TNode<C> *p):stat(no),parent(p),lchild(NULL),rchild(NULL)
    {
        data = elem;
    }
};

template <class C> class BinaryTree
{
    TNode<C>    *root;
    void __inorder(TNode<C> *t, int level)
    {
        if (!t)
            return;

        if (t->lchild)
            __inorder(t->lchild, level + 1);
        
	cout.setf(ios::right);
        cout << setw(level*3) << t->data << "(" << level << ")" << endl;
        
        if (t->rchild)
            __inorder(t->rchild, level + 1);
    }
    void __preorder(TNode<C> *t)
    {
        if (!t)
            return;

        cout << t->data << " " << endl;
        
        if (t->lchild)
            __preorder(t->lchild);
        
        if (t->rchild)
            __preorder(t->rchild);
    }
    TNode<C>* min(TNode<C> *node)
    {
        while(node->lchild)
        {
            node = node->lchild;
        }
        return node;
    }
    TNode<C>* max(TNode<C> *node)
    {
        while(node->rchild)
        {
            node = node->rchild;
        }
        return node;
    }
public:
    BinaryTree(): root(NULL){}
    void insert(C leaf)
    {
        TNode<C>   *parent = root;
        
        if (!root)
        {
            root = new TNode<C>(leaf, NULL);
            return;
        }

        while (parent)
        {
            if (leaf < parent->data)
            {
                if (parent->lchild)
                    parent = parent->lchild;
                else
                {
                    parent->lchild = new TNode<C>(leaf, parent);
                    break;
                }
            }
            else
            {
                if (parent->rchild)
                    parent = parent->rchild;
                else
                {
                    parent->rchild = new TNode<C>(leaf, parent);
                    break;
                }
            }
        }
    }
    TNode<C> *dele(TNode<C> *node)
    {
        TNode<C>   *move_out, *move_out_child, *move_out_parent;

        if (node == NULL)
            return NULL;

        /* move_out is the real one will be moved */
        if ( (node->lchild == NULL) || (node->rchild == NULL))
            move_out = node;
        else
            move_out = successor(node);

        if (move_out->lchild != NULL)
            move_out_child = move_out->lchild;
        else
            move_out_child = move_out->rchild;

        /* child's parent points to child's grand-parent */
        if (move_out_child)
            move_out_child->parent = move_out->parent;

        /* now, make "move_out_child" a child of its grand-parent*/
        if (!move_out->parent)
            root = move_out_child;
        else
        {
            move_out_parent = move_out->parent;
            if (move_out == move_out_parent->lchild)
                move_out_parent->lchild = move_out_child;
            else
                move_out_parent->rchild = move_out_child;
        }

        /* exchange the data if necessary */
        if (move_out != node)
        {
            C    tmp   = node->data;
            node->data = move_out->data;
            move_out->data = tmp;
        }

        return move_out;
    }
    void inorder()
    {
        __inorder(root, 0);
    }
    void preorder()
    {
        __preorder(root);
    }
    void iter_inorder()
    {
        Stack<TNode<C>*>  stack;
        TNode<C>         *node   = root;

        while(1)
        {
            for(;node; node = node->lchild)
                stack.push(node);
            
            if (stack.isEmpty())
                break;
            node = stack.pop();
            cout << node->data << endl;
            node = node->rchild;
        }

        return;
    }
    void iter_preorder()
    {
        Stack<TNode<C>*>  stack;
        TNode<C>         *node   = root;

        while(1)
        {
            for(;node; node = node->lchild)
            {
                cout << node->data << endl;
                stack.push(node);
            }
            if (stack.isEmpty())
                break;
            node = stack.pop();
            node = node->rchild;
        }

        return;
    }
    void level_order()
    {
        Queue<TNode<C>*>   queue;
        TNode<C>          *node;

        if (!root)
            return;
        queue.enQueue(root);

        while(!queue.isEmpty())
        {
            node = queue.deQueue();
            cout << node->data << endl;
            if (node->lchild)
                queue.enQueue(node->lchild);
            if (node->rchild)
                queue.enQueue(node->rchild);
        }
        return;
    }
    TNode<C>* iter_search(C key)
    {
        TNode<C>  *node = root;

        while (node)
        {
            if (key == node->data)
                return node;
            if (key < node->data)
                node = node->lchild;
            else
                node = node->rchild;
        }
        return node;
    }
    TNode<C>* min()
    {
        TNode<C>   *node = root;

        if (node == NULL)
            return NULL;
        else
            return min(node);
    }
    TNode<C>* max()
    {
        TNode<C>   *node = root;

        if (node == NULL)
            return NULL;
        else
            return max(node);
    }
    TNode<C>* successor(TNode<C> *node)
    {
        TNode<C>   *y;
        if (node == NULL)
            return NULL;

        /* if node has rchild */
        if (node->rchild)
            return min(node->rchild);

        /* if node hasn't rchild */
        y = node->parent;
        /* go up the tree until node is the left child of y */
        while ((y != NULL) && (node == y->rchild))
        {
            node = y;
            y = node->parent;
        }
        return y;
    }
    TNode<C>* predecessor(TNode<C> *node)
    {
        TNode<C>    *y;
        if (node == NULL)
            return NULL;

        /* if node has lchild */
        if (node->lchild)
            return max(node->lchild);

        /* if node hasn't lchild */
        y = node->parent;
        /* go up the tree untill node is the rchild of y */
        while ((y != NULL) && (node == y->lchild))
        {
            node = y;
            y = node->parent;
        }
        return y;
    }
    void depth_first()
    {
        Stack<TNode<C>*>  stack;
        TNode<C>         *node   = root;

	for (;node || !stack.isEmpty();)
	{
		if (!node)
			node = stack.pop();

		switch (node->stat) {
		case no:
			node->stat = once;
			stack.push(node);
			node = node->lchild;
			break;
		case once:
			node->stat = twice;
			cout << node->data << endl;
			stack.push(node);
			node = node->rchild;
			break;
		case twice:
			node = NULL;
			break;
		default:
			cout << "Error state of node!" << endl;
			return;
		}
	}
    }
};
#endif      //__BINARYTREE_H__
