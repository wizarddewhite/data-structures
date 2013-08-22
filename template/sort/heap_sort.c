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


int parent(int i)
{
	return (i -1)/2;
}

int left_child(int i)
{
	return (i<<1) + 1;
}

int right_child(int i)
{
	return (i<<1) + 2;
}

#ifdef DEBUG
void dump_heap(int* A, int size, int idx, int level, char *msg)
{
	/* Oops, out of the range */
	if (idx >= size)
		return;

	if (level == 0)
		printf("%s\n", msg);

	/* print this element */
	printf("%*c%d\n", level*2, ' ', A[idx]);

	/* print the left child */
	dump_heap(A, size, left_child(idx), level+1, msg);

	/* print the right child */
	dump_heap(A, size, right_child(idx), level+1, msg);
}
#else
void dump_heap(int* A, int size, int idx, int level, char *msg)
{}
#endif

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
	left  = left_child(i);
	right = right_child(i);

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
	dump_heap(A, len, 0, 0, "=== Dump the Heap ===");
	for(i=len; i>=2; i--)
	{
		tmp = A[0]; A[0] = A[len-1]; A[len-1] = tmp;

		dump_heap(A, len, 0, 0, "=== Exchange the biggest ===");
		len--;
		MaxHeapify(A, len, 0);
		dump_heap(A, len, 0, 0, "=== After Heapify ===");
	}
}


int main()
{
	int i;

	HeapSort(A, 10);
	printf("=== This final sorted array ===\n");
	for (i = 0; i< 10; i++)
		printf("%d ", A[i]);
	printf("\n");
	return 0;
}
