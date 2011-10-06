/*
 * =====================================================================================
 *
 *       Filename:  Stack.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/06/2010 05:13:00 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef     __STACK_H__
#define     __STACK_H__
#include	<iostream>
using namespace std;
#define MAX_STACK_SIZE 1024

template <class C> class Stack
{
    C stack[MAX_STACK_SIZE];
    int top;
public:
    Stack():top(-1){};
    ~Stack(){ cout << "release Stack" << endl;}
    int push(C item)
    {
        if (top >= (MAX_STACK_SIZE -1))
        {
            cout << "stack overflow" << endl;
            return -1;
        }
//        cout << top << endl;
        stack[++top] = item;
    }
    C pop()
    {
        if (top == -1)
        {
            cout << "empty stack" << endl;
            return C(0);
        }
        return stack[top--];
    }
    bool isEmpty()
    {
        if (top == -1)
            return true;
        else
            return false;
    }
};
#endif    // __STACK_H__
