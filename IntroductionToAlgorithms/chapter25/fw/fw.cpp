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
    void printArr(int (*arr)[MAX_SIZE]);
    void floydWarshall();
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

void graph::floydWarshall() {
    memcpy(shortestPaths, edges, sizeof(edges));
    for (int k = 0; k < nodeSize; k++) {
        for (int i = 0; i < nodeSize; i++) {
	    for (int j = 0; j < nodeSize; j++) {
	        if (shortestPaths[i][k] == INT_MAX || shortestPaths[k][j] == INT_MAX || shortestPaths[i][j] < shortestPaths[i][k] + shortestPaths[k][j]) {
		    temp[i][j] = shortestPaths[i][j];
		} else {
		    temp[i][j] = shortestPaths[i][k] + shortestPaths[k][j];
		}
	    }
	}
	swap(temp, shortestPaths);
    }
    printArr(shortestPaths);
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
    g->floydWarshall();
    delete g;
    return 0;
}
