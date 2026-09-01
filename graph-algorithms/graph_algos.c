/*
 * Graph algorithms.
 *
 * Author: Akshay Arun Bapat
 * Based on implementation from A. Tafliovich
 */

#include <limits.h>

#include "graph.h"

#include "minheap.h"

/*
 * A structure to keep record of the current running algorithm.
 */
typedef struct records {
  int numVertices; // total number of vertices in the graph
  // vertex IDs are 0, 1, ..., numVertices-1
  MinHeap * heap; // priority queue
  bool * finished; // finished[id] is true iff vertex id is finished
  //   i.e. no longer in the PQ
  int * predecessors; // predecessors[id] is the predecessor of vertex id
  Edge * tree; // keeps edges for the resulting tree
  int numTreeEdges; // current number of edges in mst
}
Records;

/*************************************************************************
 ** Provided helper functions -- part of starter code to help you debug!
 *************************************************************************/
void printRecords(Records * records) {
  if (records == NULL)
    return;

  int numVertices = records -> numVertices;
  printf("Reporting on algorithm's records on %d vertices...\n", numVertices);

  printf("The PQ is:\n");
  printHeap(records -> heap);

  printf("The finished array is:\n");
  for (int i = 0; i < numVertices; i++)
    printf("\t%d: %d\n", i, records -> finished[i]);

  printf("The predecessors array is:\n");
  for (int i = 0; i < numVertices; i++)
    printf("\t%d: %d\n", i, records -> predecessors[i]);

  printf("The TREE edges are:\n");
  for (int i = 0; i < records -> numTreeEdges; i++) printEdge( & records -> tree[i]);

  printf("... done.\n");
}

/*************************************************************************
 ** Suggested helper functions -- part of starter code
 *************************************************************************/
/*
 * Creates, populates, and returns a MinHeap to be used by Prim's and
 * Dijkstra's algorithms on Graph 'graph' starting from vertex with ID
 * 'startVertex'.
 * Precondition: 'startVertex' is valid in 'graph'
 */
MinHeap * initHeap(Graph * graph, int startVertex) {
  MinHeap * heap = newHeap(graph -> numVertices + 1);
  for (int i = 0; i < graph -> numVertices; i++) {
    if (i == startVertex) {
      insert(heap, 0, startVertex);
    } else {
      insert(heap, INT_MAX, i);
    }
  }
  return heap;
}

/*
 * Creates, populates, and returns all records needed to run Prim's and
 * Dijkstra's algorithms on Graph 'graph' starting from vertex with ID
 * 'startVertex'.
 * Precondition: 'startVertex' is valid in 'graph'
 */
Records * initRecords(Graph * graph, int startVertex) {
  Records * records = (Records * ) malloc(sizeof(Records));
  records -> numVertices = graph -> numVertices;
  records -> heap = initHeap(graph, startVertex);
  records -> finished = (bool * ) malloc(sizeof(bool) * graph -> numVertices);
  records -> predecessors = (int * ) malloc(sizeof(int) * graph -> numVertices);
  for (int i = 0; i < graph -> numVertices; i++) {
    records -> finished[i] = false;
    records -> predecessors[i] = -1;
  }
  records -> tree = (Edge * ) malloc(sizeof(Edge) * graph -> numEdges);
  records -> numTreeEdges = 0;
  return records;
}

/*
 * Returns true iff 'heap' is NULL or is empty.
 */
bool isEmpty(MinHeap * heap) {
  return heap == NULL || heap -> size == 0;
}

/*
 * Add a new edge to records at index ind.
 */
void addTreeEdge(Records * records, int ind, int fromVertex, int toVertex,
  int weight) {
  records -> tree[ind] = * newEdge(fromVertex, toVertex, weight);
  records -> numTreeEdges += 1;
}

/*
 * Creates and returns a path from 'vertex' to 'startVertex' from edges
 * in the distance tree 'distTree'.
 */
EdgeList * makePath(Edge * distTree, int vertex, int startVertex) {
  // If distTree is null or the vertex is the startVertex, return null
  if (distTree == NULL || vertex == startVertex) {
    return NULL;
  }

  // Initialize a counter to traverse the distTree
  int counter = 0;
  // Get the first vertex in the distTree
  int currentVertex = distTree[counter].toVertex;

  // Loop until the current vertex matches the target vertex
  while (currentVertex != vertex) {
    counter += 1;
    currentVertex = distTree[counter].toVertex;
  }

  // Create a new edge from the found vertex to its parent vertex with the given weight
  Edge * edge = newEdge(distTree[counter].toVertex, distTree[counter].fromVertex, distTree[counter].weight);
  EdgeList * next = NULL;

  // If the fromVertex is not the startVertex, recursively find the path
  if (distTree[counter].fromVertex != startVertex) {
    next = makePath(distTree, distTree[counter].fromVertex, startVertex);

    // Initialize a temporary edge list pointer and weight counter
    EdgeList * temp_edgelist = next;
    int temp_weight_counter = 0;

    // Loop through the edge list to sum up the weights
    while (temp_edgelist != NULL) {
      temp_weight_counter += temp_edgelist -> edge -> weight;
      temp_edgelist = temp_edgelist -> next;
    }

    // Adjust the weight of the current edge by subtracting the accumulated weights
    edge -> weight -= temp_weight_counter;
  }

  // Return a new edge list with the current edge and the next edge list
  return newEdgeList(edge, next);
}

/*************************************************************************
 ** Required functions
 *************************************************************************/
Edge * getMSTprim(Graph * graph, int startVertex) {
  // Initialize records for the graph starting from startVertex
  Records * records = initRecords(graph, startVertex);

  // Process nodes in the heap until it is empty
  while (!isEmpty(records -> heap)) {
    // Extract the node with the minimum distance from the heap
    HeapNode u = extractMin(records -> heap);

    // Mark this node as finished
    records -> finished[u.id] = true;

    // If the node has a predecessor, add the edge to the tree
    if (records -> predecessors[u.id] != -1) {
      // Find the edge weight between the node and its predecessor
      EdgeList * u_pred_adj_edgelist = graph -> vertices[records -> predecessors[u.id]] -> adjList;
      while (u_pred_adj_edgelist -> edge -> toVertex != u.id) {
        u_pred_adj_edgelist = u_pred_adj_edgelist -> next;
      }
      // Add the edge to the spanning tree
      addTreeEdge(records, records -> numTreeEdges, records -> predecessors[u.id], u.id, u_pred_adj_edgelist -> edge -> weight);
    }

    // Traverse all adjacent edges of the current node
    EdgeList * u_adj_edgelist = graph -> vertices[u.id] -> adjList;
    while (u_adj_edgelist != NULL) {
      Edge * u_adj_edge = u_adj_edgelist -> edge;
      int v = u_adj_edge -> toVertex;

      // If the adjacent node is not finished, update its priority in the heap if necessary
      if (records -> finished[v] == false) {
        if (u_adj_edge -> weight < getPriority(records -> heap, v)) {
          decreasePriority(records -> heap, v, u_adj_edge -> weight);
          records -> predecessors[v] = u.id;
        }
      }
      u_adj_edgelist = u_adj_edgelist -> next;
    }
  }

  // Return the constructed spanning tree
  return records -> tree;
}

Edge * getDistanceTreeDijkstra(Graph * graph, int startVertex) {
  // Initialize records for the graph starting from startVertex
  Records * records = initRecords(graph, startVertex);

  // Process nodes in the heap until it is empty
  while (!isEmpty(records -> heap)) {
    // Extract the node with the minimum distance (or priority) from the heap
    HeapNode u = extractMin(records -> heap);

    // Mark this node as finished
    records -> finished[u.id] = true;

    // Add the edge to the tree
    if (records -> predecessors[u.id] != -1) {
      // If the node has a predecessor, add the edge from predecessor to the node
      addTreeEdge(records, records -> numTreeEdges, records -> predecessors[u.id], u.id, getPriority(records -> heap, u.id));
    } else {
      // If the node does not have a predecessor (i.e., it is the start node), add a self-loop edge
      addTreeEdge(records, records -> numTreeEdges, u.id, u.id, getPriority(records -> heap, u.id));
    }

    // Traverse all adjacent edges of the current node
    EdgeList * u_adj_edgelist = graph -> vertices[u.id] -> adjList;
    while (u_adj_edgelist != NULL) {
      Edge * u_adj_edge = u_adj_edgelist -> edge;
      int v = u_adj_edge -> toVertex;

      // If the adjacent node is not finished (i.e., still in the priority queue)
      if (!records -> finished[v]) {
        // Calculate the new distance (or priority) to the adjacent node
        int d = u.priority + u_adj_edge -> weight;

        // If the new distance is less than the current priority, update the priority
        if (d < getPriority(records -> heap, v)) {
          decreasePriority(records -> heap, v, d);
          records -> predecessors[v] = u.id;
        }
      }
      u_adj_edgelist = u_adj_edgelist -> next;
    }
  }

  // Return the constructed spanning tree
  return records -> tree;
}

EdgeList ** getShortestPaths(Edge * distTree, int numVertices, int startVertex) {
  // Allocate memory for an array of EdgeList pointers to store the paths
  EdgeList ** result = (EdgeList ** ) malloc(sizeof(EdgeList * ) * numVertices);

  // Iterate over all vertices to compute the path from the startVertex
  for (int i = 0; i < numVertices; i++) {
    // Generate the path from the current vertex to the startVertex
    result[i] = makePath(distTree, i, startVertex);
  }

  // Return the array of EdgeList pointers containing the paths
  return result;
}