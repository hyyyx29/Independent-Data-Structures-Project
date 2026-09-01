/*
 * Our Priority Queue implementation.
 *
 * Author: Akshay Arun Bapat
 * Based on implementation from A. Tafliovich
 */

#include "minheap.h"

#define ROOT_INDEX 1
#define NOTHING - 1

/*************************************************************************
 ** Suggested helper functions -- part of starter code
 *************************************************************************/

/*
 * Swaps contents of heap->arr[index1] and heap->arr[index2] if both
 * 'index1' and 'index2' are valid indices for minheap 'heap'.
 * Has no effect otherwise.
 */
void swap(MinHeap * heap, int index1, int index2) {
  // check if two indexes are bigger than 0 and smaller than size
  if (index1 < 0 || index2 < 0 || index1 > heap -> size || index2 > heap -> size) {
    return;
  }
  // use node1 and node2 to store the two nodes
  HeapNode * node1 = & heap -> arr[index1];
  HeapNode * node2 = & heap -> arr[index2];
  // use temp to temporarily store the priority and id of node1
  int temp_p = node1 -> priority;
  int temp_i = node1 -> id;
  // swap the priority and id of node1 and node2
  node1 -> priority = node2 -> priority;
  node2 -> priority = temp_p;
  node1 -> id = node2 -> id;
  node2 -> id = temp_i;
  // modify the index map
  heap -> indexMap[node1 -> id] = index1;
  heap -> indexMap[node2 -> id] = index2;
}

/*
 * Returns the index of the left child of a node at index 'nodeIndex',
 * assuming it exists.
 * Precondition: 'nodeIndex' is a valid index of minheap 'heap'
 */
int getLeftChildIdx(int nodeIndex) {
  return 2 * nodeIndex;
}

/*
 * Returns the index of the right child of a node at index 'nodeIndex',
 * assuming it exists.
 * Precondition: 'nodeIndex' is a valid index of minheap 'heap'
 */
int getRightChildIdx(int nodeIndex) {
  return 2 * nodeIndex + 1;
}

/*
 * Returns the index of the parent of a node at index 'nodeIndex',
 * assuming it exists.
 * Precondition: 'nodeIndex' is a valid index of minheap 'heap'
 */
int getParentIdx(int nodeIndex) {
  return nodeIndex / 2;
}

/*
 * Returns True if 'nodeIndex' is currently a valid index in minheap 'heap'.
 * False otherwise.
 */
bool isValidIndex(MinHeap * heap, int nodeIndex) {
  return (0 < nodeIndex) && (nodeIndex <= heap -> size);
}

/*
 * Returns priority of node at index 'nodeIndex' in minheap 'heap'.
 * Precondition: 'nodeIndex' is a valid index of minheap 'heap'
 *               'heap' is non-empty
 */
int priorityAt(MinHeap * heap, int nodeIndex) {
  return heap -> arr[nodeIndex].priority;
}

/*
 * Floats up the element at index 'nodeIndex' in minheap 'heap' such that
 * 'heap' is still a minheap.
 * Precondition: 'nodeIndex' is a valid index of minheap 'heap'
 */
void floatUp(MinHeap * heap, int nodeIndex) {
  // check if the nodeIndex is valid
  if (isValidIndex(heap, getParentIdx(nodeIndex))) {
    // check if the priority of the nodeIndex is smaller than the priority of the parent
    if (priorityAt(heap, nodeIndex) < priorityAt(heap, getParentIdx(nodeIndex))) {
      // swap the nodeIndex and the parent
      // check the parent (which was the nodeIndex) and the parent's parent again
      swap(heap, nodeIndex, getParentIdx(nodeIndex));
      floatUp(heap, getParentIdx(nodeIndex));
    }
  }
  return;
}

/*
 * Returns node at index 'nodeIndex' in minheap 'heap'.
 * Precondition: 'nodeIndex' is a valid index in 'heap'
 *               'heap' is non-empty
 */
HeapNode nodeAt(MinHeap * heap, int nodeIndex) {
  return heap -> arr[nodeIndex];
}

/*
 * Returns ID of node at index 'nodeIndex' in minheap 'heap'.
 * Precondition: 'nodeIndex' is a valid index in 'heap'
 *               'heap' is non-empty
 */
int idAt(MinHeap * heap, int nodeIndex) {
  return heap -> arr[nodeIndex].id;
}

/*
 * Returns index of node with ID 'id' in minheap 'heap'.
 * Precondition: 'id' is a valid ID in 'heap'
 *               'heap' is non-empty
 */
int indexOf(MinHeap * heap, int id) {
  return heap -> indexMap[id];
}

/*********************************************************************
 * Required functions
 ********************************************************************/
HeapNode getMin(MinHeap * heap) {
  return heap -> arr[1];
}

void heapify(MinHeap * heap, int nodeIndex) {
  // check if there are two subtrees
  if (isValidIndex(heap, getRightChildIdx(nodeIndex))) { // check if left < right
    if (priorityAt(heap, getLeftChildIdx(nodeIndex)) < priorityAt(heap, getRightChildIdx(nodeIndex))) { // check if left < nodeIndex
      if (priorityAt(heap, nodeIndex) > priorityAt(heap, getLeftChildIdx(nodeIndex))) {
        // swap the nodeIndex and the smaller child
        // check the child (which was the nodeIndex) and the child's children again
        swap(heap, nodeIndex, getLeftChildIdx(nodeIndex));
        heapify(heap, getLeftChildIdx(nodeIndex));
      }
    }
    // if left > right
    else { // check if right < nodeIndex
      if (priorityAt(heap, nodeIndex) > priorityAt(heap, getRightChildIdx(nodeIndex))) {
        // swap the nodeIndex and the smaller child
        // check the child (which was the nodeIndex) and the child's children again
        swap(heap, nodeIndex, getRightChildIdx(nodeIndex));
        heapify(heap, getRightChildIdx(nodeIndex));
      }
    }
  }
  // if there is no right subtree
  else { // check if there is left subtree
    if (isValidIndex(heap, getLeftChildIdx(nodeIndex))) { // check if left < nodeIndex
      if (priorityAt(heap, nodeIndex) > priorityAt(heap, getLeftChildIdx(nodeIndex))) {
        // swap the nodeIndex and the smaller child
        // check the child (which was the nodeIndex) and the child's children again
        swap(heap, nodeIndex, getLeftChildIdx(nodeIndex));
        heapify(heap, getLeftChildIdx(nodeIndex));
      }
    }
  }
  return;
}

HeapNode extractMin(MinHeap * heap) {
  // store the min node
  HeapNode result = getMin(heap);
  // swap the min node (the first node) with the last node
  swap(heap, 1, heap -> size);
  // decrease the size of the heap, indicating that the last node is no longer in the heap
  heap -> size -= 1;
  // adjust the place of the first node (which was the last node)
  heapify(heap, 1);

  return result;
}

bool insert(MinHeap * heap, int priority, int id) {
  // check if the heap is full
  if (heap -> size == heap -> capacity) {
    return false;
  }
  // create a new node with given priorty and id
  HeapNode * new_node = (HeapNode * ) malloc(sizeof(HeapNode));
  new_node -> priority = priority;
  new_node -> id = id;
  // add the new node to the end of the array and update the heap size
  heap -> size += 1;
  heap -> arr[heap -> size] = * new_node;
  heap -> indexMap[id] = heap -> size;
  // float up the new node if necessary
  floatUp(heap, heap -> size);

  return true;
}

int getPriority(MinHeap * heap, int id) {
  return heap -> arr[indexOf(heap, id)].priority;
}

bool decreasePriority(MinHeap * heap, int id, int newPriority) {
  if (getPriority(heap, id) <= newPriority) {
    return false;
  }

  int nodeIndex = indexOf(heap, id);
  // update the priority of the node at the given index
  heap -> arr[nodeIndex].priority = newPriority;
  // update the place of the node if necessary
  floatUp(heap, nodeIndex);
  heapify(heap, nodeIndex);
  return true;
}

/*********************************************************************
 ** Helper function provided in the starter code
 *********************************************************************/
void printHeap(MinHeap * heap) {
  printf("MinHeap with size: %d\n\tcapacity: %d\n\n", heap -> size,
    heap -> capacity);
  printf("index: priority [ID]\t ID: index\n");
  for (int i = 0; i < heap -> capacity; i++)
    printf("%d: %d [%d]\t\t%d: %d\n", i, heap -> arr[i].priority,
      heap -> arr[i].id, i, heap -> indexMap[i]);
  printf("\n\n");
}

/***** Memory management (sample solution) **********************************/
MinHeap * newHeap(int capacity) {
  // allocate memory for the heap
  // set its size and capacity
  // finally allocate memory for its array
  MinHeap * minheap = (MinHeap * ) malloc(sizeof(MinHeap));
  minheap -> size = 0;
  minheap -> capacity = capacity;
  minheap -> arr = (HeapNode * ) malloc(sizeof(HeapNode) * capacity);
  minheap -> indexMap = (int * ) malloc(sizeof(int) * capacity);

  return minheap;
}

void deleteHeap(MinHeap * heap) {
  // free the memory of array first
  // then free the memory of the heap
  free(heap -> arr);
  free(heap -> indexMap);
  free(heap);
}