#include <iostream>
#include <ctime>

using namespace std;

#define ARRAY_LEN 36
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

int gcd(int a, int b) {
    if (a == b) return a;
    if (a == 0) return b;
    if (b == 0) return a;
    if ( ~a & 1) {
        if (b & 1)
	    return gcd(a >> 1, b);
	else
	    return gcd(a >> 1, b >> 1) << 1;
    }
    if (~b & 1) {
        return gcd(a, b >> 1);
    }
    if (a > b) {
        return gcd((a - b) >> 1, b);
    }
    return gcd((b - a) >> 1, a);
}

int nextPos(int pos, int len, int cnt) {
    return (pos + cnt) % len;
}

void vectorRotate(int* arr, int len, int cnt) {
    int startPos = 0;
    int curPos = startPos;
    int val = arr[startPos];
    int temp;
    for (int i = 0; i < len; i++) {
        temp = nextPos(curPos, len, cnt);
	if (temp == startPos) {
	    arr[len - cnt + startPos] = val;
	    ++startPos;
	    curPos = startPos;
	    val = arr[startPos];
	} else {
	    arr[curPos] = arr[temp];
	    curPos = temp;
	}
    }
    arr[len - cnt + startPos] = val;
}

int main() {
    srand((int)time(NULL));
    int arr[ARRAY_LEN];
    for (int i = 0; i < ARRAY_LEN; i++) {
        int num = rand() % (MAX_VALUE - MIN_VALUE + 1) + MIN_VALUE;
	arr[i] = num;
    }
    printArr(arr, ARRAY_LEN);
    vectorRotate(arr, ARRAY_LEN, 8);
    printArr(arr, ARRAY_LEN);
}
