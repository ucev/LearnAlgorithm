#include <iostream>
#include <iomanip>
#include <algorithm>
#include <climits>
#include <cstring>

#define MAX_SIZE 1000

using namespace std;

class graph {
private:
    int nodeSize;
    int edges[MAX_SIZE][MAX_SIZE];
    int shortestPaths[MAX_SIZE][MAX_SIZE];
    int temp[MAX_SIZE][MAX_SIZE];
    int parent[MAX_SIZE][MAX_SIZE];
public:
    graph(int nodesize);
    ~graph();
    void add(int u, int v, int w);
    void slowAllParisShortestPaths();
    void fasterAllParisShortestPaths();
    void printArr(int (*arr)[MAX_SIZE]);
private:
    void extendShortestPaths(int (*L)[MAX_SIZE], int (*w)[MAX_SIZE]);
};

graph::graph(int nodesize) {
    nodeSize = nodesize;
    for (int i = 0; i < nodeSize; i++) {
        for (int j = 0; j < nodeSize; j++) {
	    if (i == j) {
	        edges[i][j] = 0;
		parent[i][j] = i;
	    } else {
	        edges[i][j] = INT_MAX;
	        parent[i][j] = -1;
            }
	}
    }
}

graph::~graph() {
}

void graph::add(int u, int v, int w) {
    edges[u][v] = w;
}

void graph::extendShortestPaths(int (*L)[MAX_SIZE], int (*w)[MAX_SIZE]) {
    for (int i = 0; i < nodeSize; i++) {
        for (int j = 0; j < nodeSize; j++) {
	    temp[i][j] = L[i][j];
	    for (int k = 0; k < nodeSize; k++) {
	        if (L[i][k] == INT_MAX || w[k][j] == INT_MAX || temp[i][j] < L[i][k] + w[k][j]) {
		} else {
	            temp[i][j] = L[i][k] + w[k][j];
		    parent[i][j] = k;
		}
	    }
	}
    }
    swap(temp, shortestPaths);
    printArr(shortestPaths);
}

void graph::slowAllParisShortestPaths() {
    memcpy(shortestPaths, edges, sizeof(edges));
    printArr(shortestPaths);
    for (int i = 0; i < nodeSize - 1; i++) {
	extendShortestPaths(shortestPaths, edges);
    }
}

void graph::fasterAllParisShortestPaths() {
    memcpy(shortestPaths, edges, sizeof(edges));
    printArr(shortestPaths);
    for (int i = 1; i < nodeSize; i *= 2) {
        extendShortestPaths(shortestPaths, shortestPaths);
    }
}

void graph::printArr(int (*arr)[MAX_SIZE]) {
    for (int i = 0; i < nodeSize; i++) {
        for (int j = 0; j < nodeSize; j++) {
	    if (arr[i][j] == INT_MAX) {
	        cout << "  ∞";
	    } else {
	        cout << setw(3) << arr[i][j];
	    }
	}
	cout << endl;
    }
    cout << endl;
}

int main() {
    int nodeSize, edgeSize;
    cin >> nodeSize >> edgeSize;
    graph* g = new graph(nodeSize);
    int u, v, w;
    for (int i = 0; i < edgeSize; i++) {
        cin >> u >> v >> w;
	g->add(u, v, w);
    }
    //g->slowAllParisShortestPaths();
    g->fasterAllParisShortestPaths();
    delete g;
    return 0;
}
