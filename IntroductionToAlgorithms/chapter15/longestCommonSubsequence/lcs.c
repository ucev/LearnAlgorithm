#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAX_LEN 50

int max(int a, int b) {
    return a > b ? a : b;
}

int lcsMatrix[MAX_LEN][MAX_LEN];
char lcsWord[MAX_LEN];

void printArr(int** a, int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
	    printf("%4d", lcsMatrix[i][j]);
	}
	printf("\n");
    }
}

int find(char* a, char* b, int posA, int posB) {
    if (lcsMatrix[posA][posB] >= 0) {
        return lcsMatrix[posA][posB];
    }
    int c = a[posA] == b[posB] ? 1 : 0;
    int val;
    if (a[posA] == b[posB]) {
        val = 1 + find(a, b, posA + 1, posB + 1);
    } else {
        val = max(find(a, b, posA + 1, posB), find(a, b, posA, posB + 1));
    }
    lcsMatrix[posA][posB] = val;
    return val;
}

int findLcs(char* a, char* b) {
    int lenA = strlen(a);
    int lenB = strlen(b);
    for (int i = lenA - 1; i >= 0; i--) {
        lcsMatrix[i][lenB - 1] = lcsMatrix[i + 1][lenB - 1] == -1 ? 0 : lcsMatrix[i + 1][lenB - 1];
	if (a[i] == b[lenB - 1]) {
	    lcsMatrix[i][lenB - 1] = 1;
	}
    }
    for (int i = lenB - 1; i >= 0; i--) {
        lcsMatrix[lenA - 1][i] = lcsMatrix[lenA - 1][i + 1] == -1 ? 0 : lcsMatrix[lenA - 1][i + 1];
	if (a[lenA - 1] == b[i]) {
	    lcsMatrix[lenA - 1][i] = 1;
	}
    }
    return find(a, b, 0, 0);
}

void getSub(char* a, char* b, char* word) {
    int i = 0;
    int j = 0;
    int p = 0;
    while (lcsMatrix[i][j] > 0) {
        if(a[i] == b[j]) {
	    word[p++] = a[i];
	    i++;
	    j++;
	} else {
	    int val = lcsMatrix[i][j];
	    if (lcsMatrix[i + 1][j] >= lcsMatrix[i][j + 1]) {
	        while (lcsMatrix[i + 1][j] == val) {
		    i++;
		}
	    } else {
	        while (lcsMatrix[i][j + 1] == val) {
		    j++;
		}
	    }
	}
    }
    word[p] = '\0';
}

int main() {
    char wordA[MAX_LEN], wordB[MAX_LEN];
    while (scanf("%s %s", wordA, wordB) != EOF) {
        memset(lcsMatrix, -1, sizeof(lcsMatrix));
	findLcs(wordA, wordB);
	printf("\n%s %s\n", wordA, wordB);
	//printArr(lcsMatrix, strlen(wordA), strlen(wordB));
	//printf("\n");
	char sub[MAX_LEN];
	getSub(wordA, wordB, sub);
	printf("sub: %s\n", sub);
    }
    return 0;
}
