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

void bubblesort(int* arr, int s, int e)
{
    if (s >= e)
        return;
    for (int j = 1; j <= e - 1; j++) {
        if (arr[j] > arr[j - 1])
	    exchange(&arr[j], &arr[j - 1]);
    }
    bubblesort(arr, s , e - 1);
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
    bubblesort(arr, 0, ARRAY_LEN);
    printf(" after sort: ");
    print_arr(arr, ARRAY_LEN);
    return 0;
}

