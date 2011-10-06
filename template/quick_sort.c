/*
 * =====================================================================================
 *
 *       Filename:  quick_sort.c
 *
 *    Description:  A sorting algorithm with average O(nlgn)
 *                  A in place sorting.
 *
 *        Version:  1.0
 *        Created:  10/02/2010 09:46:14 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include	<stdio.h>

int A[10] = {1, 3, 6, 9, 8, 2, 15, 4, 7, 5};

/*
 *  A O(n) procedure to partition the array
 */
int Partition(int* A, int p, int r)
{
    int x, i, j;
    int tmp;
    
    x = A[r];
    i = p -1;

    for (j = p; j < r; j++)
    {
        if (A[j] <= x)
        {
            i++;
            tmp = A[j];
            A[j] = A[i];
            A[i] = tmp;
        }
    }
    A[r] = A[i+1];
    A[i+1] = x;
    return (i+1);
}

int Random_Partition(int* A, int p, int r)
{
    int x, i, j;
    int tmp, mid;

    mid = (p+r)/2;
    tmp = A[r]; A[r] = A[mid]; A[mid] = tmp;
    x = A[r];
    i = p -1;

    for (j = p; j < r; j++)
    {
        if (A[j] <= x)
        {
            i++;
            tmp = A[j];
            A[j] = A[i];
            A[i] = tmp;
        }
    }
    A[r] = A[i+1];
    A[i+1] = x;
    printf("partition is %d\n", i+1);
    return (i+1);
}

/*
 *  A in place sorting algorithm with 
 *  average run time of O(nlgn)
 */
void QuickSort(int* A, int p, int r)
{
    int q;
    if (p < r)
    {
//        q = Partition(A, p, r);
        q = Random_Partition(A, p, r);
        QuickSort(A, p, q-1);
        QuickSort(A, q+1, r);
    }
}

/*
 *  QuickSelect
 *  A average O(n) algorithm to select the kth element
 *  in array
 */
void QuickSelect(int* A, int p, int r, int k)
{
    int q;
    if (p < r)
    {
        q = Random_Partition(A, p, r);
        if (q == k)
            return;
        if (q < k)
            QuickSelect(A, q+1, r, k);
        else
            QuickSelect(A, p, q-1, k);
    }
}

int main()
{
    int i;
//    QuickSort(A, 0, 9);
    QuickSelect(A, 0, 9, 3);
    for (i=0; i<10; i++)
    {
        printf("%d,", A[i]);
    }
    printf("\n");

    return 0;
}
