/*
 * =====================================================================================
 *
 *       Filename:  Queue.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/06/2010 05:20:14 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#ifndef      __QUEUE_H__
#define      __QUEUE_H__
#include	<iostream>
using namespace std;

#define MAX_QUEUE_SIZE 5 

template <class C> class Queue
{
    C queue[MAX_QUEUE_SIZE];
    int rear;
    int front;
public:
    Queue():rear(0), front(0){/* cout << "Queue is initialized" << endl; */}
    ~Queue(){/* cout << "release Queue" << endl; */}
    bool isFull()
    {
        if (front == (rear+1)%MAX_QUEUE_SIZE)
            return true;
        else
            return false;
    }
    bool isEmpty()
    {
        if (front == rear)
            return true;
        else
            return false;
    }
    int enQueue(C element)
    {
        if (isFull())
            return -1;

        queue[rear] = element;
        rear = (rear+1)%MAX_QUEUE_SIZE;
        return rear;
    }
    C deQueue()
    {
        int tmp;
        if (isEmpty())
            return C(0);

        tmp = front;
        front = (front+1)%MAX_QUEUE_SIZE;
        return queue[tmp];
    }

};
#endif      //__QUEUE_H__
