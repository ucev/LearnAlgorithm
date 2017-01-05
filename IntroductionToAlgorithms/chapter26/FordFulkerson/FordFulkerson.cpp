#include <iostream>
#include <iomanip>
#include <algorithm>
#include <climits>
#include <cstring>
#include <utility>
#include <vector>

#define MAX_SIZE 100

using namespace std;

class graph {
private:
    bool reachEnd;
    int nodeCount;
    int startNode;
    int endNode;
    int capacity[MAX_SIZE];
    int edges[MAX_SIZE][MAX_SIZE];
    int orders[MAX_SIZE][MAX_SIZE];
    int flow[MAX_SIZE][MAX_SIZE];
    int residue[MAX_SIZE][MAX_SIZE];
    struct node {
        int u;
	int v;
    };
    vector<node> paths;
    int colors[MAX_SIZE];
    int minMaxFlow;
public:
    graph(int nc, int sn, int en);
    ~graph();
    void addEdge(int u, int v, int w);
    void buildFlow();
    void printFlow();
    void setCapacity(int p, int v);
private:
    void initResidue();
    void residueAdd(int u, int v, int n);
    void residueSub(int u, int v, int n);
    void printArr(int (*arr)[MAX_SIZE], int sz);
    bool findPath();
    void dfs(int n);
    void arraySort(int *arr, int * tarr, int s);
};

graph::graph(int nc, int sn, int en) {
    nodeCount = nc;
    startNode = sn;
    endNode = en;
    memset(capacity, 0, sizeof(capacity));
    memset(edges, 0, sizeof(edges));
    memset(flow, 0, sizeof(flow));
    memset(residue, 0, sizeof(residue));
}

graph::~graph() {
}

void graph::addEdge(int u, int v, int w) {
    edges[u][v] = w;
}

void graph::buildFlow() {
    initResidue();
    while (findPath()) {
        vector<node>::iterator beg = paths.begin();
	for (; beg != paths.end(); beg++) {
	    node nd = *beg;
	    flow[nd.u][nd.v] += minMaxFlow;
	    residueSub(nd.u, nd.v, minMaxFlow);
	    residueAdd(nd.v, nd.u, minMaxFlow);
	    capacity[nd.v] -= minMaxFlow;
	}
    }
}

void graph::printFlow() {
    cout << "流网络结构为:" << endl;
    printArr(flow, nodeCount);
}

void graph::printArr(int (*arr)[MAX_SIZE], int len) {
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
	    cout << setw(4) << arr[i][j];
	}
	cout << endl;
    }
    cout << endl;
}

void graph::setCapacity(int p, int v) {
    capacity[p] = v;
}

void graph::initResidue() {
    for (int i = 0; i < nodeCount; i++) {
        for (int j = 0; j < nodeCount; j++)
	    residue[i][j] = edges[i][j];
    }
    for (int i = 0; i < nodeCount; i++) {
        for (int j = 0; j < nodeCount; j++) {
	    orders[i][j] = j;
	}
        arraySort(orders[i], residue[i], nodeCount);
    }
}

void graph::residueSub(int u, int v, int n) {
    residue[u][v] -= n;
    int i = nodeCount - 1;
    int pos = -1;
    for (; i > 0; i--) {
        if (orders[u][i] == v)
	    break;
    }
    for (; i > 0; i--) {
        int cp = orders[u][i-1];
	if (residue[u][cp] > residue[u][v])
	    swap(orders[u][i], orders[u][i - 1]);
	else
	    break;
    }
}

void graph::residueAdd(int u, int v, int n) {
    residue[u][v] += n;
    int i = 0;
    int pos = -1;
    for (; i < nodeCount - 1; i++) {
        if (orders[u][i] == v)
	    break;
    }
    for (; i < nodeCount - 1; i++) {
        int cp = orders[u][i + 1];
	if (residue[u][cp] < residue[u][v])
	    swap(orders[u][i], orders[u][i + 1]);
	else
	    break;
    }
}

bool graph::findPath() {
    minMaxFlow = INT_MAX;
    /*
    for (int i = 0; i < nodeCount; i++)
        colors[i] = 0;
	*/
    paths.clear();
    reachEnd = false;
    dfs(startNode);
    return reachEnd;
}

void graph::dfs(int nd) {
    if (nd == endNode) {
	reachEnd = true;
	return;
    }
    colors[nd] = 1;
    for (int i = 0; !reachEnd && i < nodeCount; i++) {
        int cn = orders[nd][i];
	if (colors[cn] == 1 || residue[nd][cn] <= 0 || capacity[cn] <=0)
	    continue;
	minMaxFlow = min(minMaxFlow, min(residue[nd][cn], capacity[cn]));
	node cnode;
	cnode.u = nd;
	cnode.v = cn;
	paths.push_back(cnode);
	int sizeBefore = paths.size();
	dfs(cn);
	if (reachEnd)
	    break;
	int sizeAfter = paths.size();
	if (sizeAfter == sizeBefore) {
	    paths.pop_back();
	}
    }
    colors[nd] = 0;
}

void graph::arraySort(int *arr, int *tarr, int s) {
    if (s <= 0)
        return;
    int en = tarr[arr[s - 1]];
    int j = 0;
    for (int i = 0; i < s - 1; i++) {
        if (tarr[arr[i]] < en) {
	    swap(arr[i], arr[j++]);
	}
    }
    swap(arr[j], arr[s - 1]);
    arraySort(arr, tarr, j);
    arraySort(arr + j + 1, tarr + j + 1, s - j - 1);
}

int main() {
    int ncnt, snode, enode, ecnt;
    int u, v, w;
    cin >> ncnt >> snode >> enode >> ecnt;
    graph graph(ncnt, snode, enode);
    for (int i = 0; i < ncnt; i++) {
        graph.setCapacity(i, INT_MAX);
    }
    for (int i = 0; i < ecnt; i++) {
        cin >> u >> v >> w;
	graph.addEdge(u, v, w);
    }
    graph.buildFlow();
    graph.printFlow();
    return 0;
}
