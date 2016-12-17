#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define __DEBUG

#define MAX_WEIGHT 1000
#define MAX_SIZE 20

struct obj {
    int weight;
    int value;
};

int optVal[MAX_WEIGHT];
int tempVal[MAX_WEIGHT];
struct obj objArr[MAX_SIZE];

void printArr(int* arr, int len) {
    for (int i = 0; i < len; i++)
        printf("%2d:%-5d", i, arr[i]);
    printf("\n\n");
}

/**
 * pw 背包容量
 */
void process(int pw, int objcnt) {
    int i;
    for (i = 0; i < objArr[0].weight; i++)
        optVal[i] = 0;
    for (; i <= pw; i++)
        optVal[i] = objArr[0].value;
    int totalweight = objArr[0].weight;
#ifdef __DEBUG
    printArr(optVal, pw + 1);
#endif
    for (int j = 1; j < objcnt; j++) {
        memcpy(tempVal, optVal, sizeof(optVal));
        int curweight = objArr[j].weight;
	int curval = objArr[j].value;
	totalweight += curweight;
	int w = curweight;
	for (; w <= pw && w <= totalweight; w++) {
	    int nw = tempVal[w - curweight] + curval;
	    if (nw > tempVal[w - 1])
	        optVal[w] = nw;
	    else
	        optVal[w] = tempVal[w - 1];
	}
	for (; w <= pw; w++) {
	    optVal[w] = optVal[w - 1];
	}
#ifdef __DEBUG
	printArr(optVal, pw + 1);
#endif
    }
}

int main() {
    int pw;
    scanf("%d", &pw);
    int w, v;
    int cnt = 0;
    while(scanf("%d %d", &w, &v) != EOF) {
        struct obj o;
	o.weight = w;
	o.value = v;
	objArr[cnt++] = o;
    }
    for (int i = 0; i < cnt; i++) {
        printf("obj%d     weight:%d    value:%d\n", i, objArr[i].weight, objArr[i].value);
    }
    process(pw, cnt);
    printArr(optVal, pw + 1);
    return 0;
}
