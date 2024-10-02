/*
 * Our MinHeap implementation.
 *
 * Author (starter code): Akshay Arun Bapat.
 * Based on implementation from A. Tafliovich and F. Estrada
 */

#include "minheap.h"

/*************************************************************************
 ** Suggested helper functions -- part of starter code
 *************************************************************************/

/*
 * Swaps contents of heap->arr[index1] and heap->arr[index2] if both
 * 'index1' and 'index2' are valid indices for minheap 'heap'.
 * Has no effect otherwise.
 */
void swap(MinHeap* heap, int index1, int index2);

/*
 * Floats up the element at index 'nodeIndex' in minheap 'heap' such that
 * 'heap' is still a minheap.
 * Precondition: 'nodeIndex' is a valid index of minheap 'heap'
 */
void floatUp(MinHeap* heap, int nodeIndex);

/*
 * Returns the index of the left child of a node at index 'nodeIndex',
 * assuming it exists.
 * Precondition: 'nodeIndex' is a valid index of minheap 'heap'
 */
int getLeftChildIdx(int nodeIndex);

/*
 * Returns the index of the right child of a node at index 'nodeIndex',
 * assuming it exists.
 * Precondition: 'nodeIndex' is a valid index of minheap 'heap'
 */
int getRightChildIdx(int nodeIndex);

/*
 * Returns the index of the parent of a node at index 'nodeIndex',
 * assuming it exists.
 * Precondition: 'nodeIndex' is a valid index of minheap 'heap'
 */
int getParentIdx(int nodeIndex);

/*
 * Returns True if 'nodeIndex' is currently a valid index in minheap 'heap'.
 * False otherwise.
 */
bool isValidIndex(MinHeap* heap, int nodeIndex);

/*
 * Returns priority of node at index 'nodeIndex' in minheap 'heap'.
 * Precondition: 'nodeIndex' is a valid index of minheap 'heap'
 *               'heap' is non-empty
 */
int priorityAt(MinHeap* heap, int nodeIndex);

/*********************************************************************
 * Required functions
 ********************************************************************/

HeapNode getMin(MinHeap* heap)
{
  HeapNode something;
  return something;
}

void heapify(MinHeap* heap, int nodeIndex)
{
  return;
}

HeapNode extractMin(MinHeap* heap)
{
  HeapNode something;
  return something;
}

bool insert(MinHeap* heap, int priority, int id)
{
  return false;
}

void changePriority(MinHeap* heap, int nodeIndex, int newPriority)
{
  return;
}

MinHeap* newHeap(int capacity)
{
  return NULL;
}

void deleteHeap(MinHeap* heap)
{
  return;
}

/*********************************************************************
 ** Helper function provided in the starter code
 *********************************************************************/
void printHeap(MinHeap* heap)
{
  printf("MinHeap with size: %d\n\tcapacity: %d\n\n", heap->size,
         heap->capacity);
  printf("index: priority [ID]\n");
  for (int i = 1; i <= heap->size; i++)
    printf("%d: %d [%d]\n", i, heap->arr[i].priority, heap->arr[i].id);
  printf("\n\n");
}

/****************************************************
** Experiments and Analysis
****************************************************/

/*
 * Both the following functions build a heap from scratch based on the input
 * array of priorites for IDs '0' to 'size-1'.
 *
 * You can assume both implementations are correct.
 */

MinHeap* buildHeap_Sajad(int values[], int size)
{
  MinHeap* heap = newHeap(size);
  heap->size = size;

  for (int i=0; i<size; i++)
  {
    heap->arr[i+1].priority = values[i];
    heap->arr[i+1].id = i;
  }

  for (int i=size/2; i>=1; i--)
  {
    heapify(heap, i);
  }

  return heap;
}

MinHeap* buildHeap_Elaheh(int values[], int size)
{
  MinHeap* heap = newHeap(size);

  for (int i=0; i<size; i++)
  {
    if (!insert(heap, values[i], i))
      return NULL;
  }

  return heap;
}
