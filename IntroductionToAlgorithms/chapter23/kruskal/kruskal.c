#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAX_CNT 100

int parent[MAX_CNT];

struct edge {
    int u;
    int v;
    int l;
};

int cmp(struct edge* a, struct edge* b) {
    return a->l - b->l;
}

void join(struct edge* a) {
    int u = a->u;
    int v = a->v;
    int t = parent[u] == -1 ? v : u;
    int ot = u == t ? v : u;
    //printf("join :u(%2d) v(%2d) l(%2d) pu(%2d) pv(%2d)\n", a->u, a->v, a->l, parent[a->u], parent[a->v]);
    if (parent[t] == -1) {
        parent[t] = t;
	parent[ot] = t;
	printf("%c  %c  %4d\n", u + 'a' - 1, v + 'a' - 1, a->l);
    } else if(parent[t] != parent[ot]){
        int pot = parent[ot];
	// MAX_CNT
	for (int i = 0; i < MAX_CNT; i++) {
	    if (parent[i] == pot && parent[i] != -1) {
	        parent[i] = parent[t];
	    }
	}
	parent[ot] = parent[t];
	printf("%c  %c  %4d\n", u + 'a' - 1, v + 'a' - 1, a->l);
    } else {
    }
}

int main() {
    memset(parent, -1, sizeof(parent));
    struct edge edges[MAX_CNT];
    int nodecnt, edgecnt;
    scanf("%d %d", &nodecnt, &edgecnt);
    for (int i = 0; i < edgecnt; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].l);
    }
    qsort(edges, edgecnt, sizeof(struct edge), cmp);
    for (int i = 0; i < edgecnt; i++) {
        join(&edges[i]);
    }
    return 0;
}
