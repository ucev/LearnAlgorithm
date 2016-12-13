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

void insertsort(int* arr, int len) {
    for (int i = 1; i < len; i++) {
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
    insertsort(arr, ARRAY_LEN);
    printf(" after sort: ");
    print_arr(arr, ARRAY_LEN);
    return 0;
}
