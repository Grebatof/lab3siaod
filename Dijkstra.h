#pragma once
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct node {
    int key;
    int data;
} node;

typedef struct minHeap {
    int maxsize;
    int size;
    node *nodes;
} minHeap;

double wtime();
minHeap *heap_create(int maxsize);
void swap(node *n1, node *n2);
void heapify(minHeap *hp, int i);
void insertNode(minHeap *hp, int key, int data);
node extractMinNode(minHeap *hp);
int decrease_key(struct minHeap *h, int index, int key, int numOfPoints);

void ShortestPathDijkstra(struct graph *g, int src, int *d, int *prev);
void SSShortestPathDijkstra(struct graph *g, int src, int *d, int *prev);
