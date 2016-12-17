#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"
#include "limits.h"

#define ARR_LEN 1000
#define MAX_VAL 100
#define MIN_VAL 0

int subsum[ARR_LEN][ARR_LEN];

int max(int a, int b) {
    return a > b ? a : b;
}

void printArr(int* arr, int len) {
    for (int i = 0; i < len; i++) {
        printf("%4d", arr[i]);
    }
    printf("\n\n");
}

/**
 * 动态规划
 */
void getMostAppSubSum(int* arr, int len, int tnum) {
    memset(subsum, 0, sizeof(subsum));
    int al = -1, ar = -1;
    int minsub = INT_MAX;
    int minsum = 0;
    int sub, sum;
    for (int k = 0; k < len; k++) {
        for (int i = 0; i < len - k; i++) {
	    int j = i + k;
	    if (i == j) {
	        sum = arr[i];
	    } else {
	        sum = subsum[i][j - 1] + arr[j];
	    }
	    sub = sum - tnum;
	    sub = sub > 0 ? sub : -sub;
	    if (sub < minsub) {
	        minsub = sub;
		minsum = sum;
		al = i;
		ar = j;
	    }
	    subsum[i][j] = sum;
	}
    }
    printf("minsub: %4d minsum: %4d left: %4d right: %4d\n", minsub, minsum, al, ar);
}

int main() {
    int arr[ARR_LEN];
    srand((int)time(NULL));
    int l = MAX_VAL - MIN_VAL;
    int tnum;
    for (int j = 0; j < 5; j++) {
        for (int i = 0; i < ARR_LEN; i++) {
            arr[i] = rand() % l - l / 2;
        }
	scanf("%d", &tnum);
	getMostAppSubSum(arr, ARR_LEN, tnum);
    }
    return 0;
}
