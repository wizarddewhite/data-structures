/*
 * =====================================================================================
 *
 *       Filename:  string_revert.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/05/2010 08:17:51 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include	<stdio.h>
#include	<string.h>

char A[] = "abcdefghijklmnopqrstuvwxyz";

void string_revert(char *A, int len)
{
    int i, j;
    char tmp;

    for(i=0, j=len-1; i < j; i++, j--)
    {
//        printf("i:%d, j:%d\n", i,j);
        tmp = A[j];
        A[j] = A[i];
        A[i] = tmp;
    }
}

int main()
{
    string_revert(A, strlen(A));
    printf("A is %s\n", A);
    return 0;
}

