#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#define ARRAY_LEN 20
#define MIN_VALUE 0
#define MAX_VALUE 100

void print_arr(int* arr, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d, ", arr[i]);
    }
    printf("\n");
}

void merge(int* arr, int s, int e) {
    for (int i = (s + e) / 2 + 1; i <= e; i++) {
        int temp = arr[i];
        int j = i;
	for (; j - 1 >= 0; j--) {
	    if (arr[j - 1] > temp) {
	        arr[j] = arr[j - 1];
	    } else {
	        break;
	    }
	}
	arr[j] = temp;
    }
}

void merge_sort(int* arr, int s, int e) {
    if (s == e) return;
    int m = (s + e) / 2;
    merge_sort(arr, s, m);
    merge_sort(arr, m + 1, e);
    merge(arr, s, e);
}

int main()
{
    srand((int)time(NULL));
    int arr[ARRAY_LEN];
    for (int i = 0; i < ARRAY_LEN; i++) {
        int num = rand();
	num = num % (MAX_VALUE - MIN_VALUE) + MIN_VALUE;
	arr[i] = num;
    }
    printf("before sort: ");
    print_arr(arr, ARRAY_LEN);
    merge_sort(arr, 0, ARRAY_LEN - 1);
    printf(" after sort: ");
    print_arr(arr, ARRAY_LEN);
    return 0;
}
