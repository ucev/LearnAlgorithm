#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_VALUE 0
#define MAX_VALUE 100
#define ITEM_COUNT 20

void printArr(int* arr, int len)
{
    for (int i = 0; i < len; i++) {
        printf("%5d, ", arr[i]);
    }
    printf("\n");
}

void countsort(int* originArr, int* sortedArr, int len)
{
    int cnt = MAX_VALUE - MIN_VALUE + 1;
    int* carr = calloc(cnt, sizeof(int));
    for (int i = 0; i < cnt; i++)
        carr[i] = 0;
    for (int i = 0; i < len; i++)
        carr[originArr[i]] += 1;
    for (int i = 1; i < cnt; i++)
        carr[i] = carr[i] + carr[i - 1];
    for (int i = 0; i < len; i++) {
        int pos = carr[originArr[i]] - 1;
	sortedArr[pos] = originArr[i];
	carr[originArr[i]] -= 1;
    }
    free(carr);
}

int main()
{
    int originArr[ITEM_COUNT], sortedArr[ITEM_COUNT];
    srand((int)time(NULL));
    for (int i = 0; i < ITEM_COUNT; i++) {
        originArr[i] = rand() % (MAX_VALUE - MIN_VALUE + 1) + MIN_VALUE;
    }
    printArr(originArr, ITEM_COUNT);
    countsort(originArr, sortedArr, ITEM_COUNT);
    printArr(sortedArr, ITEM_COUNT);
    return 0;
}
