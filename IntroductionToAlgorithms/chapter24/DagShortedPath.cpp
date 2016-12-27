#include <iostream>
#include <iomanip>
#include <list>
#include <queue>
#include <climits>
#include <cstring>

using namespace std;

struct node {
    int order;
    int len;
};

class Graph {
private:
    list<node*>* adj;
    list<int> sortedNode;
    queue<int>*  tempNode;
    int nodeCount;
    int* parent;
    int* distance;
    int start;
    enum COLOR{WHITE, BLACK, GREY};
    COLOR* colors;
public:
    Graph(int nodecnt);
    ~Graph();
    void add(int u, int v, int w);
    void getPath(int s);
    void printPath(int v);
    void getResult();
private:
    void relax(int u, int v, int w);
    void sort();
    void dfs();
};

Graph::Graph(int nodecnt) {
    nodeCount = nodecnt;
    adj = new list<node*>[nodeCount];
    parent = new int[nodeCount];
    distance = new int[nodeCount];
    start = -1;
    for (int i = 0; i < nodecnt; i++) {
        parent[i] = -1;
	distance[i] = INT_MAX;
    }
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
    sort();
    parent[start] = start;
    distance[start] = 0;
    list<int>::iterator nbeg = sortedNode.begin();
    list<int>::iterator nend = sortedNode.end();
    for(; nbeg != nend; nbeg++) {
        int n = *nbeg;
	cout << setw(3) << n;
	list<node*>::iterator beg = adj[n].begin();
	list<node*>::iterator end = adj[n].end();
	for(; beg != end; beg++) {
	    relax(n, (*beg)->order, (*beg)->len);
	}
    }
    cout << endl;
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
    list<int>::iterator beg = sortedNode.begin();
    list<int>::iterator end = sortedNode.end();
    cout << "节点顺序为： ";
    for (; beg != end; beg++) {
        cout << setw(4) << *beg;
    }
    cout << endl << endl;
    cout << "根结点是: " << start << endl;
    cout << setw(7) << "节点" << setw(7) << "父节点" << setw(5) << "距离" << endl;
    for (int i = 0; i < nodeCount; i++) {
        cout << setw(7) << i << setw(7) << parent[i] << setw(5) << distance[i] << endl;
    }
    cout << endl;
}

void Graph::sort(){
    tempNode = new queue<int>;
    sortedNode.clear();
    colors = new COLOR[nodeCount];
    for (int i = 0; i < nodeCount; i++) {
        colors[i] = WHITE;
    }
    colors[start] = GREY;
    tempNode->push(start);
    dfs();
    delete tempNode;
    tempNode = NULL;
    delete colors;
    colors = NULL;
}

void Graph::dfs() {
    while (!tempNode->empty()) {
        int s = tempNode->front();
	tempNode->pop();
	sortedNode.push_back(s);
	list<node*>::iterator beg = adj[s].begin();
	list<node*>::iterator end = adj[s].end();
	for(; beg != end; beg++) {
	    int v = (*beg)->order;
	    if (colors[v] == WHITE) {
	        colors[v] = GREY;
		tempNode->push(v);
	    }
	}
	dfs();
	colors[s] = BLACK;
    }
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
    g->getPath(1);
    g->getResult();
    delete g;
    return 0;
}
