/*
 * Our graph implementation.
 *
 * Author: Akshay Arun Bapat
 * Based on implementation from A. Tafliovich
 */

#include "graph.h"

/*********************************************************************
 ** Helper function provided in the starter code
 *********************************************************************/

void printEdge(Edge * edge) {
  if (edge == NULL)
    printf("NULL");
  else
    printf("(%d -- %d, %d)", edge -> fromVertex, edge -> toVertex, edge -> weight);
}

void printEdgeList(EdgeList * head) {
  while (head != NULL) {
    printEdge(head -> edge);
    printf(" --> ");
    head = head -> next;
  }
  printf("NULL");
}

void printVertex(Vertex * vertex) {
  if (vertex == NULL) {
    printf("NULL");
  } else {
    printf("%d: ", vertex -> id);
    printEdgeList(vertex -> adjList);
  }
}

void printGraph(Graph * graph) {
  if (graph == NULL) {
    printf("NULL");
    return;
  }
  printf("Number of vertices: %d. Number of edges: %d.\n\n", graph -> numVertices,
    graph -> numEdges);

  for (int i = 0; i < graph -> numVertices; i++) {
    printVertex(graph -> vertices[i]);
    printf("\n");
  }
  printf("\n");
}

/*********************************************************************
 ** Required functions
 *********************************************************************/

Edge * newEdge(int fromVertex, int toVertex, int weight) {
  Edge * newEdge = (Edge * ) malloc(sizeof(Edge));
  newEdge -> fromVertex = fromVertex;
  newEdge -> toVertex = toVertex;
  newEdge -> weight = weight;
  return newEdge;
}

EdgeList * newEdgeList(Edge * edge, EdgeList * next) {
  EdgeList * newEdgeList = (EdgeList * ) malloc(sizeof(EdgeList));
  newEdgeList -> edge = edge;
  newEdgeList -> next = next;
  return newEdgeList;
}

Vertex * newVertex(int id, void * value, EdgeList * adjList) {
  Vertex * newVertex = (Vertex * ) malloc(sizeof(Vertex));
  newVertex -> id = id;
  newVertex -> value = value;
  newVertex -> adjList = adjList;
  return newVertex;
}

Graph * newGraph(int numVertices) {
  Graph * newGraph = (Graph * ) malloc(sizeof(Graph));
  newGraph -> numVertices = numVertices;
  newGraph -> numEdges = 0; // is this correct?
  newGraph -> vertices = (Vertex ** ) malloc(numVertices * sizeof(Vertex * ));
  return newGraph;
}

void deleteEdgeList(EdgeList * head) {
  if (head == NULL) {
    return;
  }
  deleteEdgeList(head -> next);
  free(head -> edge);
  free(head);
  return;
}

void deleteVertex(Vertex * vertex) {
  deleteEdgeList(vertex -> adjList);
  free(vertex);
  return;
}

void deleteGraph(Graph * graph) {
  for (int i = 0; i < graph -> numVertices; i++) {
    deleteVertex(graph -> vertices[i]);
  }
  free(graph);
  return;
}