#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "limits.h"

#define MAX_SIZE 100
#define MAX_DIS  INT_MAX

enum Color {WHITE, GREY, BLACK};

// 邻接矩阵
int vertex[MAX_SIZE][MAX_SIZE];
// distance
int distance[MAX_SIZE];
// parent
int parent[MAX_SIZE];
// color
enum Color color[MAX_SIZE];

void printArr(int** arr, int cnt) {
    for (int i = 0; i < cnt; i++) {
        for (int j = 0; j < cnt; j++) {
	    printf("%4d", arr[i][j]);
	}
        printf("\n");
    }
    printf("\n\n");
}

int qpos;
int queue[MAX_SIZE];
void initQueue() {
    qpos = 0;
}

void enqueue(int p) {
    if (qpos < MAX_SIZE) {
        queue[qpos++] = p;
    }
}

int dequeue() {
    if (qpos > 0)
        return queue[--qpos];
    else
        return -1;
}

int queueEmpty() {
    return qpos == 0;
}

void bfs(int s, int cnt) {
    memset(distance, MAX_DIS, sizeof(distance));
    memset(parent, -1, sizeof(parent));
    memset(color, WHITE, sizeof(color));
    distance[s] = 0;
    color[s] = GREY;
    initQueue();
    enqueue(s);
    while (!queueEmpty()) {
        int p = dequeue();
	for (int i = 0; i < cnt; i++) {
	    if (vertex[p][i] == 1 && color[i] == WHITE) {
	        distance[i] = distance[p] + 1;
		color[i] = GREY;
		enqueue(i);
	    }
	}
	color[p] = BLACK;
    }
}

int main() {
    memset(vertex, 0, sizeof(vertex));
    int v, u;
    int cnt = 0;
    while (scanf("%d %d", &v, &u) != EOF) {
        vertex[v][u] = 1;
	vertex[u][v] = 1;
	cnt++;
    }
    bfs(0, cnt);
    printArr(vertex, cnt);
    return 0;
}
