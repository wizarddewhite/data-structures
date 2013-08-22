/*
 * =====================================================================================
 *
 *       Filename:  heap_sort.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  10/01/2010 07:48:07 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include	<stdio.h>

int A[10] = {1, 3, 6, 9, 8, 2, 5, 4, 7, 10};


/*
 *  MaxHeapify, O(h), h = O(lgn)
 *  make the subtree rooted at i, compile to max 
 *  heap property
 */
void MaxHeapify(int* A, int size, int i)
{
    int left, right;
    int largest;
    int tmp;
    left  = (i<<1) + 1;
    right = left + 1;

    if ( (left < size) && (A[left] > A[i]) )
        largest = left;
    else
        largest = i;
    if ( (right < size) && (A[right] > A[largest]) )
        largest = right;

    if (largest != i)
    {
        tmp = A[largest];
        A[largest] = A[i];
        A[i] = tmp;
        MaxHeapify(A, size, largest);
    }
}

/*
 *  BuildMaxHeap, O(n) algorithm
 *  Make the array A, length of len, compile to a max heap
 */
void BuildMaxHeap(int* A, int size)
{
    int start = (size >> 1) - 1;
    for(; start>=0; start--)
    {
        MaxHeapify(A, size, start);
    }
}

/*
 *  HeapSort
 *  A O(nlgn) in place sorting algorithm 
 */
void HeapSort(int* A, int len)
{
    int i, tmp;
    BuildMaxHeap(A, len);
    for(i=len; i>=2; i--)
    {
        tmp = A[0]; A[0] = A[len-1]; A[len-1] = tmp;

        len--;
        MaxHeapify(A, len, 0);
    }
}


int main()
{
    HeapSort(A, 10);
    return 0;
}
