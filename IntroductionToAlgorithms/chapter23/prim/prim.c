#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "limits.h"

#define MAX_COUNT 100

int graph[MAX_COUNT][MAX_COUNT];
int parent[MAX_COUNT];
int used[MAX_COUNT];
int key[MAX_COUNT];

int orderHeap[MAX_COUNT];
int heapItemCount;

void printData(int len) {
    for (int i = 0; i < len; i++) {
        printf("(i:%c  p:%c,  k:%2d)\n", i + 'a', parent[i] + 'a', key[i]);
    }
    printf("\n\n");
}

void printOrder() {
    printf("order\n");
    for (int i = 0; i < heapItemCount; i++) {
        int ro = orderHeap[i];
        printf("[order:%2d  node:%2d  key:%d]\n", i, ro + 1, key[ro]);
    }
    printf("\n\n");
}

void printArr(int* arr, int len) {
    for (int i = 0; i < len; i++) {
        printf("%4d ", arr[i]);
    }
    printf("\n\n");
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int heapParent(int i) {
    return (i + 1) / 2 - 1;
}

int heapLeft(int i) {
    return i * 2 + 1;
}

int heapRight(int i) {
    return i * 2 + 2;
}

void buildHeap(int pos) {
    int l = heapLeft(pos);
    int r = heapRight(pos);
    int min = pos;
    if (l < heapItemCount && key[orderHeap[l]] < key[orderHeap[min]]) {
        min = l;
    }
    if (r < heapItemCount && key[orderHeap[r]] < key[orderHeap[min]]) {
        min = r;
    }
    if (min == pos)
        return;
    swap(&orderHeap[pos], &orderHeap[min]);
    buildHeap(min);
}

int extractMin() {
    int i = orderHeap[0];
    swap(&orderHeap[0], &orderHeap[--heapItemCount]);
    buildHeap(0);
    return i;
}

void heapDecrease(int pos) {
    int p = heapParent(pos);
    while (p > 0 && key[pos] < key[p]) {
        swap(&orderHeap[p], &orderHeap[pos]);
	pos = p;
	p = heapParent(pos);
    }
}

void initHeap(int len) {
    heapItemCount = len;
    for (int i = 0; i < heapItemCount; i++) {
        orderHeap[i] = i;
    }
}

void itemDecrease() {
    /*
    for (int i = heapItemCount - 1; i >=0; i--) {
        int p = heapParent(i);
	if (p > 0) {
	    if (key[i] < key[p]) {
	        heapDecrease(i);
	    }
	}
    }*/
    for (int i = heapItemCount / 2; i >= 0; i--) {
        buildHeap(i);
    }
}

int heapEmpty() {
    return heapItemCount == 0;
}

void prim(int len) {
    memset(parent, -1, sizeof(parent));
    memset(used, 0, sizeof(used));
    memset(key, 0, sizeof(key));
    for (int i = 0; i < len; i++)
        key[i] = INT_MAX;
    initHeap(len);
    parent[0] = 0;
    key[0] = 0;
    itemDecrease();
    while(!heapEmpty()) {
        int k = extractMin();
	for (int i = 0; i < len; i++) {
	    if (!used[i] && graph[k][i] < key[i]) {
	        key[i] = graph[k][i];
		parent[i] = k;
	    }
	}
	itemDecrease();
	used[k] = 1;
    }
}

int main() {
    int nodecount, edgecount;
    scanf("%d %d", &nodecount, &edgecount);
    for (int i = 0; i < nodecount; i++)
        for (int j = 0; j < nodecount; j++)
	    graph[i][j] = graph[j][i] = INT_MAX;
    int u, v, l;
    for (int i = edgecount; i > 0; i--) {
        scanf("%d %d %d", &u, &v, &l);
	u -= 1;
	v -= 1;
	graph[u][v] = graph[v][u] = l;
    }
    prim(nodecount);
    printData(nodecount);
    return 0;
}
