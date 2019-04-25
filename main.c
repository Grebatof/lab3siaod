#include <stdio.h>

#include "graph.h"
#include "Dijkstra.h"
#include "queue_array.h"

#define SIZE 20

int main() {
  struct graph *g = graph_create(SIZE);

  int d[SIZE];
  int prev[SIZE];

  double time;

  generate_graph( g, 35);

  printf("   ");
  for (int k = 0; k < g->nvertices; k++) {
    printf("%2.d ", k + 1);
  }
  printf("\n");

  for (int i = 0; i < g->nvertices; i++) {
    printf("\n%2.d ", i + 1);
    for (int j = 0; j < g->nvertices; j++) {
      printf("%2.d ", g->m[i * g->nvertices + j]);
    }
    printf("\n");
  }

  time = wtime();

  ShortestPathDijkstra(g, 1 - 1, d, prev);

  time = wtime() - time;

  printf("\ntime: %f\n", time);

  printf("\n   i:");
  for (int i = 0; i < SIZE; i++) {
    printf("%4.d| ", i + 1);
  }
  printf("\nprev:");
  for (int i = 0; i < SIZE; i++) {
    if (prev[i] != -1) {
      printf("%4.d| ", prev[i]);
    } else {
      printf("  no| ");
    }
  }
  printf("\npath:");
  //printf("   0| ");
  for (int i = 0; i < SIZE; i++) {
    if (d[i] == 0) {
      printf("   0| ");
      continue;
    }
    if (d[i] != 100000) {
      printf("%4.d| ", d[i]);
    } else {
      printf("  no| ");
    }
  }

  printf("\n");

  SSShortestPathDijkstra(g, 8 - 1, d, prev);

  struct graph *grr = graph_create(100 * 100);
  int drr[100 * 100];
  int prevrr[100 * 100];

  generate_matrix_graph(grr);

  time = wtime();

  ShortestPathDijkstra(grr, 1 - 1, drr, prevrr);

  time = wtime() - time;

  printf("\ntime: %f\n", time);

  SSShortestPathDijkstra(grr, 256 - 1, drr, prevrr);

  return 0;
}
