#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"

#define ARR_LEN 100000
#define MAX_VAL 1000
#define MIN_VAL 0

int max(int a, int b) {
    return a > b ? a : b;
}

void printArr(int* arr, int len) {
    for (int i = 0; i < len; i++) {
        printf("%4d", arr[i]);
    }
    printf("\n");
}

/**
 * 动态规划
 */
int getMaxSubSum(int* arr, int len) {
    int sum[ARR_LEN];
    memset(sum, 0, sizeof(sum));
    int maxsum = 0;
    if (arr[0] > 0) {
        sum[0] = arr[0];
	maxsum = sum[0];
    }
    for (int i = 1; i < len; i++) {
        int s = sum[i - 1] + arr[i];
	s = s > 0 ? s : 0;
	sum[i] = s;
	maxsum = maxsum > s ? maxsum : s;
    }
    //printArr(sum, len);
    return maxsum;
}

/**
 * 分治算法
 */
int subquadratic(int* arr, int l, int r) {
    if (l > r) return 0;
    if (l == r) {
        return arr[l] > 0 ? arr[l] : 0;
    }
    int m = (l + r) / 2;
    int lmax = 0;
    int lr = m;
    int sum = 0;
    for (int i = m; i >= l; i--) {
        sum += arr[i];
	if (sum > lmax) {
	    lmax = sum;
	    lr = i;
	}
    }
    int rmax = 0;
    int rl = m + 1;
    sum = 0;
    for (int i = m + 1; i <= r; i++) {
        sum += arr[i];
	if (sum > rmax) {
	    rmax = sum;
	    rl = i;
	}
    }
    return max(lmax + rmax, max(subquadratic(arr, l, lr - 1), subquadratic(arr, rl + 1, r)));
}

int main() {
    int arr[ARR_LEN];
    srand((int)time(NULL));
    int l = MAX_VAL - MIN_VAL;
    for (int j = 0; j < 5; j++) {
        for (int i = 0; i < ARR_LEN; i++) {
            arr[i] = rand() % l - l / 2;
        }
        //printArr(arr, ARR_LEN);
	int maxsum = getMaxSubSum(arr, ARR_LEN);
	int m = subquadratic(arr, 0, ARR_LEN - 1);
	printf("maxsum is : %4d %4d\n\n", maxsum, m);
    }
    return 0;
}
