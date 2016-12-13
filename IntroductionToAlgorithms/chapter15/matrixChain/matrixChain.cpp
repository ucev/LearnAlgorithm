#include <iostream>
#include <cmath>
#include <climits>
#include <iomanip>

#define MATRIX_COUNT 20

using namespace std;

int data[] = {
     3,  5,  5, 21, 21,  8,  8, 54, 54,  6, 
     6,  3,  3,  7,  7,  5,  5,  8,  8, 34, 
    34,  5,  5,  9,  9,  5,  5, 13, 13,  8,
     8,  3,  3,  2,  2, 10, 10,  6,  6,  9
};

struct matrix {
    int row;
    int col;
};

matrix chain[MATRIX_COUNT];

/*
int getRow(int i) {
    return i * 2;
}

int getCol(int i) {
    return i * 2 + 1;
}
*/

int minLen[MATRIX_COUNT][MATRIX_COUNT];
int minKey[MATRIX_COUNT][MATRIX_COUNT];

void printArr(int arr[20][20], int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++)
	    cout << setw(5) << arr[i][j];
	cout << endl;
    }
}

void matrixChainOrder() {
    for (int i = 0; i < MATRIX_COUNT; i++) {
        minLen[i][i] = 0;
	minKey[i][i] = i;
    }
    int minNum;
    int key;
    for (int l = 2; l <= MATRIX_COUNT; l++) {
        for (int i = 0; i <= MATRIX_COUNT - l; i++) {
	    int j = i + l - 1;
	    minNum = INT_MAX;
	    key = -1;
	    for (int k = i; k < j; k++) {
	        int cur = minLen[i][k] + minLen[k][j] + chain[i].row * chain[k].col * chain[j].col;
		//int cur = minLen[i][k] + minLen[k + 1][j] + data[getRow(i)] * data[getCol(k)] * data[getCol(j)];
		if (cur < minNum) {
		    minNum = cur;
		    key = k;
		}
	    }
	    minLen[i][j] = minNum;
	    minKey[i][j] = key;
	}
    }
}

void printOptimalParens(int s, int e) {
    if (s > e)
        return;
    if (s == e) {
        cout << s << " ";
	return;
    }
    cout << "(";
    int key = minKey[s][e];
    printOptimalParens(s, key);
    printOptimalParens(key + 1, e);
    cout << ")";
}

int main() {
    memset(minLen, 0, sizeof(minLen));
    memset(minKey, 0, sizeof(minKey));
    for (int i = 0; i < MATRIX_COUNT; i++) {
        int s = i * 2;
	int e = s + 1;
	matrix m;
	m.row = data[s];
	m.col = data[e];
	chain[i] = m;
    }
    matrixChainOrder();
    /*
    printArr(minLen, MATRIX_COUNT, MATRIX_COUNT);
    cout << endl << endl;
    printArr(minKey, MATRIX_COUNT, MATRIX_COUNT);
    cout << endl << endl;
    */
    printOptimalParens(0, MATRIX_COUNT - 1);
    cout << endl << endl;
    return 0;
}
