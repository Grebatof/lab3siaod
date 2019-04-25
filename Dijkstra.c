#include "graph.h"
#include "Dijkstra.h"

#define LCHILD(x) 2 * (x + 1) - 1
#define RCHILD(x) 2 * (x + 1)
#define PARENT(x) (x - 1) / 2

/////////////MISC//////////
int getrand(int min, int max) {
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}
double wtime() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}
//////////////////////////
minHeap *heap_create(int maxsize) {
    minHeap *h;
    h = malloc(sizeof(*h));
    if (h != NULL) {
        h->maxsize = maxsize;
        h->size = 0;
        h->nodes = malloc(sizeof(*h->nodes) * (maxsize + 1));
        if (h->nodes == NULL) {
            free(h);
            return NULL;
        }
    }
    return h;
}

void swap(node *n1, node *n2) {
    node temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}
void heapify(minHeap *hp, int i) {
    int smallest = (LCHILD(i) < hp->maxsize && hp->nodes[LCHILD(i)].data < hp->nodes[i].data) ? LCHILD(i) : i;
    if (RCHILD(i) < hp->maxsize && hp->nodes[RCHILD(i)].data < hp->nodes[smallest].data) {
        smallest = RCHILD(i);
    }
    if (smallest != i) {
        swap(&(hp->nodes[i]), &(hp->nodes[smallest]));
        heapify(hp, smallest);
    }
}

void insertNode(minHeap *hp, int key, int data) {
    if (hp->size >= hp->maxsize) {
        return;
    }
    hp->nodes[hp->size].key = key;
    hp->nodes[hp->size].data = data;

    for (int i = hp->size; i > 0 && hp->nodes[i].data < hp->nodes[PARENT(i)].data; i = PARENT(i)) {
        swap(&hp->nodes[i], &hp->nodes[PARENT(i)]);
    }
    hp->size++;
}

node extractMinNode(minHeap *hp) {
    node minNode;
    if (hp->size) {
        minNode.key = hp->nodes[0].key;
        minNode.data = hp->nodes[0].data;
        //hp->nodes[0].data = hp->nodes[--(hp->size)].data + 1;
        hp->nodes[0].data = 1000000 + 1;
        --(hp->size);
        heapify(hp, 0);
    } else {
        printf("\nMin Heap is empty!\n");
    }
    return minNode;
}

int decrease_key(struct minHeap *h, int key, int data, int numOfPoints) {
    int index;
    for (index = 0; index < numOfPoints; ++index) {
        if (h->nodes[index].key == key) {
            break;
        }
    }

    h->nodes[index].data = data;

    while (index > 0 && h->nodes[index].data < h->nodes[PARENT(index)].data) {
        swap(&h->nodes[index], &h->nodes[PARENT(index)]);
        index = PARENT(index);
    }
    return index;
}



void ShortestPathDijkstra(struct graph *g, int src, int *d, int *prev) {
  minHeap *hp = heap_create(g->nvertices);
  //printf("\n");

  for (int i = 0; i < g->nvertices; i++) { // Помещаем вершины в очередь с приоритетом
    if (i == src) {
      continue;
    }
    d[i] = 1000000;
    prev[i] = -1;
    insertNode(hp, i, d[i]);
  }

  d[src] = 0;
  prev[src] = -1;
  insertNode(hp, src, d[src]);

  node minNode;

  for (int i = 0; i < g->nvertices; i++) {
    // for (int t = 0; t < g->nvertices ; t++) {
    //   printf("|%2.d %6.d|", hp->nodes[t].key + 1, hp->nodes[t].data);
    // }
    // printf("\n");
    minNode = extractMinNode(hp); // Извлекаем узел, ближайший к начальному
    // for (int t = 0; t < g->nvertices ; t++) {
    //   printf("|%2.d %6.d|", hp->nodes[t].key + 1, hp->nodes[t].data);
    // }
     //printf("\n\n");
     //printf("|%d %d|", minNode.key + 1, minNode.data);
     //printf("\n\n");
    g->visited[minNode.key] = 1; // Отмечаем v как посещённый
    // for (int k = 0; k < i*17; k++) {
    //   printf(" ");
    // }
    for (int j = 0; j < g->nvertices; j++) { // Цикл по смежным непосещённым вершинам узла v
      //printf("|%6.d %6.d %2.d ", d[j], minNode.data, g->m[minNode.key * g->nvertices + j]);
      if ((minNode.data + g->m[minNode.key * g->nvertices + j] < d[j]) && (g->m[minNode.key * g->nvertices + j] > 0) && (g->visited[j] == 0)) { // Путь через u короче текущего пути?
        d[j] = minNode.data + g->m[minNode.key * g->nvertices + j];
        //printf("%2.d -> %3.d -> %2.d ", i + 1, d[j], j + 1);
        decrease_key(hp, j, d[j], g->nvertices);
        // for (int i = 0; i < 10; i++) {
        //   printf("|%d ", hp->nodes[i].key + 1);
        // }
        // printf("\n");
        prev[j] = minNode.key + 1;
      }
      if ((minNode.data == 1000000) && (d[minNode.key] == 1000000) && (g->m[minNode.key * g->nvertices + j] > 0) && (g->visited[j] == 0)) {
        //printf("%d %d\n", d[j] + g->m[minNode.key * g->nvertices + j], j);
        d[minNode.key] = d[j] + g->m[minNode.key * g->nvertices + j];
        decrease_key(hp, minNode.key, d[minNode.key], g->nvertices);
        prev[minNode.key] = j + 1;
      }
    }
    //printf("\n");
  }

  //printf("\n");
}

void SSShortestPathDijkstra(struct graph *g, int src, int *d, int *prev)
{
  printf("\n%d ", src + 1);
  while (prev[src] != -1) {
    printf("(%d) -> %d ", graph_get_edge(g, src + 1, prev[src]) ,prev[src]);
    src = prev[src] - 1;
  }
  printf("\n");
}
