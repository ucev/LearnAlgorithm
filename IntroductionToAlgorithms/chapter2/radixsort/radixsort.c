/**
  * 基数排列
  */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define ARRAY_LEN 20
#define MIN_VALUE 0
#define MAX_VALUE 99

#define TRUE  1
#define FALSE 0

void printArr(int* arr, int len) {
    for (int i = 0 ; i < len; i++) {
        printf("%5d,", arr[i]);
    }
    printf("\n");
}

int** malloc2DArr(int row, int col)
{
    int** arr = calloc(row, sizeof(int*));
    for (int i = 0; i < row; i++)
        arr[i] = calloc(col, sizeof(int));
    return arr;
    /*
    int sz = sizeof(int);
    int ptSz = sizeof(int*);
    int** arr = (int**)malloc(ptSz * row + sz * row * col);
    memset(arr, 0, sizeof(arr));
    int* head = (int*)((int)arr + ptSz * row);
    for (int i = 0 ; i < row; i++) {
    while (row--) {
        arr[row] = (int*)((int)head + sz * row * col);
    }
    return (int**)arr;
    */
}

void free2DArr(int** arr, int row, int col) {
    for (int i = 0; i < row; i++)
        free(arr[i]);
    //free(arr);
}

int getRadix(int num, int rad)
{
    return (num % (int)pow(10, rad + 1)) / (int)pow(10, rad);
}

void radixSort(int* arr, int len)
{
    int cnt[10];
    memset(cnt, 0, sizeof(cnt));
    int** cols = malloc2DArr(10, len);
    int finished = FALSE;
    for (int i = 0; finished == FALSE; i++) {
        int radix, preRadix;
	int allTheSame = TRUE;
        for (int j = 0; j < len; j++) {
	    radix = getRadix(arr[j], i);
	    int radixCnt = cnt[radix]++;
	    cols[radix][radixCnt] = arr[j];
	    if (allTheSame) {
	        if (j ==0) {
	            preRadix = radix;
	        } else {
	            if (preRadix != radix) {
		        allTheSame = FALSE;
		    }
		}
	    }
	}
	finished = allTheSame;
	int c = 0;
	for (int k = 0; k < 10; k++) {
	    for (int m = 0; m < cnt[k]; m++) {
	        arr[c++] = cols[k][m];
	    }
	}
	memset(cnt, 0, sizeof(cnt));
    }
    free2DArr(cols, 10, len);
    free(cols);
}

int main()
{
    srand((int)time(NULL));
    int arr[ARRAY_LEN];
    for (int i = 0; i < ARRAY_LEN; i++) {
        arr[i] = (rand() % (MAX_VALUE - MIN_VALUE)) + MIN_VALUE;
    }
    printf("before sort:\n\t");
    printArr(arr, ARRAY_LEN);
    radixSort(arr, ARRAY_LEN);
    printf("after sort:\n\t");
    printArr(arr, ARRAY_LEN);
    return 0;
}
