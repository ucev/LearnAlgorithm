#include <iostream>
#include <ctime>
using namespace std;

#define ARRAY_LEN 20
#define MIN_VALUE 0
#define MAX_VALUE 30

void printArr(int* arr, int len) {
    cout << "arr(";
    for (int i = 0; i < len; i++) {
        cout << arr[i] << ", ";
    }
    cout << ")" << endl;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void reverse(int* arr, int start, int end) {
    for (int i = start, j = end; i < j; i++, j--) {
        swap(arr + i, arr + j);
    }
}

void vectorRotate(int* arr, int len, int cnt) {
    reverse(arr, 0, cnt - 1);
    reverse(arr, cnt, len - 1);
    reverse(arr, 0, len - 1);
}

int main() {
    srand((int)time(NULL));
    int arr[ARRAY_LEN];
    for (int i = 0; i < ARRAY_LEN; i++) {
        int num = rand() % (MAX_VALUE - MIN_VALUE + 1) + MIN_VALUE;
	arr[i] = num;
    }
    printArr(arr, ARRAY_LEN);
    vectorRotate(arr, ARRAY_LEN, 5);
    printArr(arr, ARRAY_LEN);
}
