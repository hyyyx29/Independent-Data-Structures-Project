/*
 * Header file for our MinHeap implementation.
 *
 * You will NOT be submitting this file. Your code will be tested with
 * our own version of this file, so make sure you do not modify it!
 *
 * Author: Akshay Arun Bapat
 * Based on implementation from A. Tafliovich and F. Estrada
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef __MinHeap_header
#define __MinHeap_header

#define ROOT_INDEX 1
#define NOTHING -1

typedef struct heap_node {
  int priority;  // priority of this node
  int id;        // the unique ID of this node
} HeapNode;

typedef struct min_heap {
  int size;       // the number of nodes in this heap; 0 <= size <= capacity
  int capacity;   // the number of nodes that can be stored in this heap
  HeapNode* arr;  // the array that stores the nodes of this heap
} MinHeap;

/*
 * Returns the node with minimum priority in minheap 'heap'.
 * Precondition: heap is non-empty
 */
HeapNode getMin(MinHeap* heap);

/*
 * If 'nodeIndex' is the only node where heap property is not satisfied
 * in the minheap rooted at 'nodeIndex', then
 * Perform operations such that 'heap' becomes a valid minheap.
 * 
 * Note: This is equivalent to floatUp but in the opposite direction.
 * Precondition: 'nodeIndex' is a valid index in 'heap'
 *               child subtrees of 'nodeIndex' are valid minheaps
 */
void heapify(MinHeap* heap, int nodeIndex);

/*
 * Removes and returns the node with minimum priority in minheap 'heap'.
 * Precondition: heap is non-empty
 */
HeapNode extractMin(MinHeap* heap);

/*
 * Inserts a new node with priority 'priority' and ID 'id' into minheap 'heap'.
 * Returns: true if insert was successful, false otherwise
 * Precondition: 'id' is unique within this minheap
 */
bool insert(MinHeap* heap, int priority, int id);

/*
 * Sets priority of node at index 'nodeIndex' in minheap 'heap'
 * to 'newPriority'.
 * Precondition: 'newPriority' is different from old priority
 *               'nodeIndex' index is valid in minheap 'heap'
 *
 * Note: this function should still maintain 'heap' to be a minheap.
 *
 * Usually we would want to qchange priority of an ID with 'id'.
 * If we had to search for an 'id' however, we would need O(n) time.
 * Here we are making a simplifying assumption that the node is already
 * found for us. Usually, there is a hashmap to find corresponding node
 * of which priority is to be changed.
 */
void changePriority(MinHeap* heap, int nodeIndex, int newPriority);

/*
 * Prints the contents of this heap, including size and capacity. For
 * each non-empty element of the heap array, that node's ID and priority.
 */
void printHeap(MinHeap* heap);

/*
 * Returns a newly created empty minheap with initial capacity 'capacity'.
 * Precondition: capacity >= 0
 */
MinHeap* newHeap(int capacity);

/*
 * Frees all memory allocated for minheap 'heap'.
 */
void deleteHeap(MinHeap* heap);

/*
 * Build a heap for priorities 'values' for IDs '0' to 'size-1'.
 */
MinHeap* buildHeap_Sajad(int values[], int size);
MinHeap* buildHeap_Elaheh(int values[], int size);

#endif
