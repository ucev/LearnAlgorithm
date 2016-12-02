#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_LEN 20
#define MIN_VALUE 0
#define MAX_VALUE 100

void exchange(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void print_arr(int* arr, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d, ", arr[i]);
    }
    printf("\n");
}

int partition(int* arr, int s, int e)
{
    int r = arr[e];
    int i = s - 1;
    for (int j = s; j <= e - 1; ++j) {
        if (arr[j] < r) {
	    ++i;
	    exchange(&arr[i], &arr[j]);
	}
    }
    exchange(&arr[i + 1], &arr[e]);
    return i + 1;
}

void quicksort(int* arr, int s, int e)
{
    if (s < e) {
        int i = partition(arr, s, e);
	quicksort(arr, s, i - 1);
	quicksort(arr, i + 1, e);
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
    quicksort(arr, 0, ARRAY_LEN - 1);
    printf(" after sort: ");
    print_arr(arr, ARRAY_LEN);
    return 0;
}
