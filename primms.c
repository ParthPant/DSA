#include <limits.h> 
#include <stdbool.h> 
#include <stdio.h> 
#define V 5

int getMin(int key[], bool visited[]) {
  int min = INT_MAX, min_index;

  for (int v = 0; v < V; v++)
    if (visited[v] == false && key[v] < min)
      min = key[v], min_index = v;

  return min_index;
}

void printTree(int parent[], int graph[V][V]) {
  printf("Edge \tWeight\n");
  for (int i = 1; i < V; i++)
    printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
}

void createMST(int graph[V][V]) {
  int parent[V];
  int key[V];
  bool visited[V];

  for (int i = 0; i < V; i++)
    key[i] = INT_MAX, visited[i] = false;

  key[0] = 0;

  for (int count = 0; count < V - 1; count++) {
    int u = getMin(key, visited);
    visited[u] = true;

    for (int v = 0; v < V; v++)
      if (graph[u][v] && visited[v] == false && graph[u][v] < key[v])
        parent[v] = u, key[v] = graph[u][v];
  }

  printTree(parent, graph);
}

int main() 
{ 
    int graph[V][V] = { { 0, 2, 0, 6, 0 }, 
                        { 2, 0, 3, 8, 5 }, 
                        { 0, 3, 0, 0, 7 }, 
                        { 6, 8, 0, 0, 9 }, 
                        { 0, 5, 7, 9, 0 } }; 
  
    createMST(graph);
    return 0; 
} 

