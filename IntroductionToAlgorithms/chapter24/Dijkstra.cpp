#include <iostream>
#include <iomanip>
#include <algorithm>
#include <list>
#include <queue>
#include <climits>

using namespace std;

struct node {
    int order;
    int distance;
};

class graph {
private:
    int nodeCount;
    int startNode;
    list<node*>* edges;
    int* distance;
    int* posToken;
    int* nodeOrder;
    int* parent;
    int heapSize;
public:
    graph(int nodeCount);
    ~graph();
    void add(int u, int v, int w);
    void buildPath(int s);
    void printPath();
private:
    void decreaseDistance(int i, int dis);
    int extractMin();
    void relax(int u, int v, int w);
    int heapParent(int i);
    int heapLeft(int i);
    int heapRight(int i);
    void minHeapify(int i);
};

graph::graph(int ncnt) {
    nodeCount = ncnt;
    edges = new list<node*>[nodeCount];
    distance = new int[nodeCount];
    parent = new int[nodeCount];
    posToken = new int[nodeCount];
    nodeOrder = new int[nodeCount];
    for (int i = 0; i < nodeCount; i++) {
        distance[i] = INT_MAX;
	parent[i] = -1;
	posToken[i] = i;
	nodeOrder[i] = i;
    }
    heapSize = nodeCount;
}

graph::~graph() {
    //
    delete [] edges;
    delete [] distance;
    delete [] parent;
}

void graph::add(int u, int v, int w) {
    node* nd = new node;
    nd->order = v;
    nd->distance = w;
    edges[u].push_back(nd);
}

void graph::buildPath(int s) {
    startNode = s;
    parent[s] = 0;
    decreaseDistance(s, 0);
    for (int i = 0; i < nodeCount; i++) {
        int n = extractMin();
	cout << "min : " << n << endl;
	list<node*>::iterator beg = edges[n].begin();
	list<node*>::iterator end = edges[n].end();
	for (; beg != end; beg++) {
	    relax(n, (*beg)->order, (*beg)->distance);
	}
    }
}

void graph::printPath() {
    cout << "最短路径图是：" << endl;
    for (int i = 0; i < nodeCount; i++) {
        cout << "node:" << setw(3) << i << "    parent:" << setw(3) << parent[i] << "    distance:" << setw(3) << distance[i] << endl;
    }
}

void graph::relax(int u, int v, int w) {
    if (distance[v] > distance[u] + w) {
        decreaseDistance(v, distance[u] + w);
	parent[v] = u;
    }
}

void graph::decreaseDistance(int ord, int dis) {
    if (distance[ord] <= dis) return;
    distance[ord] = dis;
    int opos = posToken[ord];
    int ppos = heapParent(opos);
    while(ppos >= 0) {
        if (distance[nodeOrder[opos]] < distance[nodeOrder[ppos]]) {
	    swap(nodeOrder[opos], nodeOrder[ppos]);
	    swap(posToken[nodeOrder[opos]], posToken[nodeOrder[ppos]]);
	    opos = ppos;
	    ppos = heapParent(opos);
	} else {
	    break;
	}
    }
}

int graph::extractMin() {
    int mpos = nodeOrder[0];
    swap(nodeOrder[0], nodeOrder[heapSize - 1]);
    swap(posToken[nodeOrder[0]], posToken[nodeOrder[heapSize - 1]]);
    heapSize--;
    minHeapify(0);
    return mpos;
}

void graph::minHeapify(int s) {
    int l = heapLeft(s);
    int r = heapRight(s);
    int min = s;
    if (l < heapSize && distance[nodeOrder[min]] > distance[nodeOrder[l]]) {
        min = l;
    }
    if (r < heapSize && distance[nodeOrder[min]] > distance[nodeOrder[r]]) {
        min = r;
    }
    if (min != s) {
        swap(nodeOrder[s], nodeOrder[min]);
	swap(posToken[nodeOrder[s]], posToken[nodeOrder[min]]);
	minHeapify(min);
    }
}

int graph::heapParent(int i) {
    return (i + 1) / 2 - 1;
}

int graph::heapLeft(int i) {
    return i * 2 + 1;
}

int graph::heapRight(int i) {
    return i * 2 + 2;
}

int main() {
    int nodecnt, edgecnt;
    cin >> nodecnt >> edgecnt;
    graph* g = new graph(nodecnt);
    int u, v, w;
    for (int i = 0; i < edgecnt; i++) {
        cin >> u >> v >> w;
	g->add(u, v, w);
    }
    g->buildPath(0);
    g->printPath();
    delete g;
    return 0;
}
