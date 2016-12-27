#include <iostream>
#include <iomanip>
#include <list>
#include <queue>
#include <climits>

using namespace std;

struct node {
    int order;
    int len;
};

class Graph {
private:
    list<node*>* adj;
    int nodeCount;
    int* parent;
    int* distance;
    int start;
    bool hasNegative;
public:
    Graph(int nodecnt);
    ~Graph();
    void add(int u, int v, int w);
    void relax(int u, int v, int w);
    void getPath(int s);
    void printPath(int v);
    void getResult();
};

Graph::Graph(int nodecnt) {
    nodeCount = nodecnt;
    adj = new list<node*>[nodecnt];
    parent = new int[nodecnt];
    distance = new int[nodecnt];
    start = -1;
    for (int i = 0; i < nodecnt; i++) {
        parent[i] = -1;
	distance[i] = INT_MAX;
    }
    hasNegative = false;
}

Graph::~Graph() {
    delete [] adj;
    delete [] parent;
    delete [] distance;
}

void Graph::add(int u, int v, int w) {
    node* nd = new node;
    nd->order = v;
    nd->len = w;
    adj[u].push_back(nd);
}

void Graph::relax(int u, int v, int w) {
    if (distance[v] > distance[u] + w) {
        distance[v] = distance[u] + w;
	parent[v] = u;
    }
}

void Graph::getPath(int s) {
    start = s;
    parent[start] = start;
    distance[start] = 0;
    for (int i = 0; i < nodeCount; i++) {
        for (int j = 0; j < nodeCount; j++) {
	    list<node*>::iterator beg = adj[j].begin();
	    list<node*>::iterator end = adj[j].end();
	    for(; beg != end; beg++) {
	        relax(j, (*beg)->order, (*beg)->len);
	    }
	}
    }
    for (int j = 0; j < nodeCount; j++) {
	list<node*>::iterator beg = adj[j].begin();
	list<node*>::iterator end = adj[j].end();
	for(; beg != end; beg++) {
	    if (distance[(*beg)->order] > distance[j] + (*beg)->len) {
		hasNegative = true;
		break;
	    }
	}
    }
}

void Graph::printPath(int v) {
    int n = v;
    while(parent[v] != v) {
        cout << "(v:" << setw(2) << v << " ,d:" << setw(2) << distance[v] << ") <- ";
	v = parent[v];
    }
    cout << "(v:" << setw(2) << v << " ,d:" << setw(2) << distance[v] << endl;
}

void Graph::getResult() {
    cout << "根结点是: " << start << endl;
    cout << setw(7) << "节点" << setw(7) << "父节点" << setw(5) << "距离" << endl;
    for (int i = 0; i < nodeCount; i++) {
        cout << setw(7) << i << setw(7) << parent[i] << setw(5) << distance[i] << endl;
    }
    cout << endl;
}

int main() {
    int nodecnt, edgecnt;
    cin >> nodecnt >> edgecnt;
    Graph* g = new Graph(nodecnt);
    int u, v, w;
    for (int i = 0; i < edgecnt; i++) {
        cin >> u >> v >> w;
	g->add(u, v, w);
    }
    g->getPath(0);
    g->printPath(4);
    delete g;
    return 0;
}
