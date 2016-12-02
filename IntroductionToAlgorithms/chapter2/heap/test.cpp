#include <iostream>
#include "MaxHeap.cpp"
#include <cstdlib>
#include <ctime>

#define MAX 100
#define MIN 0
#define NUM_COUNT 20

int main()
{
    srand((unsigned int)time(NULL));
    MaxHeap *heap = new MaxHeap();
    /*
    for (int i = 0; i < NUM_COUNT; i++) {
        heap->add(rand() % (MAX - MIN) + MIN);
    }*/
    int num[20] = {30, 53, 23, 18, 30, 80, 23, 50, 25, 43, 38, 77, 75, 47, 2, 55, 81, 27, 96, 29};
    for (int i = 0; i < 20; i++ ) {
        heap->add(num[i]);
    }
    heap->buildHeap();
    heap->getMaxQueue();
    delete heap;
    return 0;
}
