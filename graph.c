#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

#include "queue_array.h"

struct graph *graph_create(int nvertices)
{
  struct graph *g;
  g = malloc(sizeof(*g));
  g->nvertices = nvertices;
  g->m = malloc(sizeof(int) * nvertices * nvertices);
  g->visited = malloc(sizeof(int) * nvertices);
  graph_clear(g); // Опционально, O(n^2)
  return g;
}

void graph_clear(struct graph *g)
{
  int i, j;
  for (i = 0; i < g->nvertices; i++) {
    g->visited[i] = 0;
    for (j = 0; j < g->nvertices; j++) {
      g->m[i * g->nvertices + j] = 0;
    }
  }
}

void graph_free(struct graph *g)
{
  free(g->m);
  free(g->visited);
  free(g);
}

void graph_set_edge(struct graph *g, int i, int j, int w)
{
  g->m[(i - 1) * g->nvertices + j - 1] = w;
  g->m[(j - 1) * g->nvertices + i - 1] = w;
}

int graph_get_edge(struct graph *g, int i, int j)
{
  return g->m[(i - 1) * g->nvertices + j - 1];
}

void generate_graph(struct graph *g, int k)
{
  int j1, j2, drr, brr;
  g->visited[0] = 1;

  for (int i = 0; i < g->nvertices - 1; i++) {
    while (1) {
      j1 = (rand() % g->nvertices);
      if (g->visited[j1] == 1) {
        break;
      }
    }
    while (1) {
      j2 = (rand() % g->nvertices);
      if (g->visited[j2] == 0) {
        g->visited[j2] = 1;
        g->m[j1 * g->nvertices + j2] = g->m[j2 * g->nvertices + j1] = 1 + rand() % 99;
        break;
      }
    }
  }

  for (int i = (g->nvertices - 1); i < k; i++) {
    while (1) {
      drr = rand() % g->nvertices;
      brr = rand() % g->nvertices;
      if ((brr == drr) || (g->m[drr * g->nvertices + brr] != 0)) {
        continue;
      }
      g->m[drr * g->nvertices + brr] = g->m[brr * g->nvertices + drr] = 1 + rand() % 99;
      break;
    }
  }

  for (int i = 0; i < g->nvertices; i++) {
    g->visited[i] = 0;
  }
}

void generate_matrix_graph(struct graph *g)
{
  for (int i = 0; i < (100 * 100 - 1); i++) {
    if ((i + 1) % 100 == 0) {
      continue;
    }
    g->m[i * g->nvertices + (i + 1)] = g->m[(i + 1) * g->nvertices + i] = 1 + rand() % 99;
  }
  for (int i = 0; i < (100 * 100 - 100); i++) {
    g->m[i * g->nvertices + (i + 100)] = g->m[(i + 100) * g->nvertices + i] = 1 + rand() % 99;
  }
}
