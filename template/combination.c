/*
 * =====================================================================================
 *
 *       Filename:  combination.c
 *
 *    Description:  Çó×éºÏ
 *
 *        Version:  1.0
 *        Created:  10/01/2010 10:09:23 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include	<stdio.h>
#define     STACK_SIZE 4

int pop(int *);
int push(int);
void combination(int, int);

int stack[STACK_SIZE] = {0};
int top = -1;

int main()
{
    combination(5, STACK_SIZE);
    printf("\n");
}


void combination(int m, int n)
{
    int temp = m;
    push(temp);
    
    while(1)
    {
        if ( 1 == temp)
        {
            /* stack is empty and is the least elemtn, break */
            if (pop(&temp) && stack[0] == n)
                break;
        }
        else if (push(--temp))
        {
            printf("%d%d%d%d, ", stack[0], stack[1], stack[2], stack[3]);
            pop(&temp);
        }
    }
}

int push(int i)
{
    stack[++top] = i;
    if (top < (STACK_SIZE - 1))
        return 0;
    else
        return 1;
}

int pop(int *i)
{
    *i = stack[top--];
    if (top >= 0)
        return 0;
    else
        return 1;
}
