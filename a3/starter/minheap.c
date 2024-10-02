/*
 * Our Priority Queue implementation.
 *
 * Author: Akshay Arun Bapat
 * Based on implementation from A. Tafliovich
 */

#include "minheap.h"

#define ROOT_INDEX 1
#define NOTHING -1

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

/*
 * Returns node at index 'nodeIndex' in minheap 'heap'.
 * Precondition: 'nodeIndex' is a valid index in 'heap'
 *               'heap' is non-empty
 */
HeapNode nodeAt(MinHeap* heap, int nodeIndex);

/*
 * Returns ID of node at index 'nodeIndex' in minheap 'heap'.
 * Precondition: 'nodeIndex' is a valid index in 'heap'
 *               'heap' is non-empty
 */
int idAt(MinHeap* heap, int nodeIndex);

/*
 * Returns index of node with ID 'id' in minheap 'heap'.
 * Precondition: 'id' is a valid ID in 'heap'
 *               'heap' is non-empty
 */
int indexOf(MinHeap* heap, int id);

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

int getPriority(MinHeap* heap, int id)
{
  return 0;
}

bool decreasePriority(MinHeap* heap, int id, int newPriority)
{
  return false;
}

/*********************************************************************
 ** Helper function provided in the starter code
 *********************************************************************/
void printHeap(MinHeap* heap)
{
  printf("MinHeap with size: %d\n\tcapacity: %d\n\n", heap->size,
         heap->capacity);
  printf("index: priority [ID]\t ID: index\n");
  for (int i = 0; i < heap->capacity; i++)
    printf("%d: %d [%d]\t\t%d: %d\n", i, heap->arr[i].priority,
           heap->arr[i].id, i, heap->indexMap[i]);
  printf("\n\n");
}

/***** Memory management (sample solution) **********************************/
MinHeap* newHeap(int capacity)
{
  return NULL;
}

void deleteHeap(MinHeap* heap)
{
  return;
}
