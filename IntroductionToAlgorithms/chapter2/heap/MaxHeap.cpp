#ifndef __HEAP_FILE__
#define __HEAP_FILE__

#include <iostream>
#include <cmath>

#define HEAP_MAX_SIZE 100

class MaxHeap{
private:
    int mData[HEAP_MAX_SIZE];
    int mMax;

public:
    MaxHeap() {
        mMax = 0;
    }

    ~MaxHeap() {
        std::cout << "destruct" << std::endl;
    }

    void add(int data) {
        if (mMax < HEAP_MAX_SIZE) {
            mData[mMax++] = data;
	}
    }

    void set(int pos, int data) {
        if (pos < mMax) {
	    mData[pos] = data;
	}
    }

    void maxHeapify(int pos) {
        int l = left(pos);
	int r = right(pos);
	int max = pos;
	//std::cout << "vp: "<< mData[pos] << "\tvleft:" << mData[l] << "\tvright:" << mData[r] << std::endl;
	if (l < mMax && mData[l] > mData[max])
	    max = l;
	if (r < mMax && mData[r] > mData[max])
	    max = r;
	//std::cout << "pos:" << pos + 1 <<"\tleft:" << l  + 1<< "\tright:" << r + 1 << "\tmax: " << max + 1<< std::endl;
	if (max != pos) {
	    swap(&mData[pos], &mData[max]);
	    //std::cout << "MAX HEAPIFY: ";
	    //getData();
	    maxHeapify(max);
	}
    }

    void buildHeap() {
        for (int i = floor((float)mMax / 2); i >= 0; i--) {
	    maxHeapify(i);
	}
    }

    int getMax() {
        return mData[0];
    }

    int extractMax() {
        int max = mData[0];
	swap(&mData[0], &mData[mMax - 1]);
	mMax--;
	maxHeapify(0);
	return max;
    }

    void getMaxQueue() {
        while (hasData()) {
	    std::cout << extractMax() <<", ";
	}
	std::cout << std::endl;
    }

    void getData() {
        for (int i = 0; i < mMax; i++)
	    std::cout << mData[i] <<", ";
        std::cout << std::endl;
    }
    
private:
    int left(int pos) {
        return (pos + 1) * 2 - 1;
    }

    int right(int pos) {
        return (pos + 1) * 2;
    }

    int parent(int pos) {
        return floor((float)(pos + 1) / 2);
    }
    
    void swap(int * a, int * b) {
        int temp = *a;
	*a = *b;
	*b = temp;
    }

    bool hasData() {
        return mMax > 0;
    }
};

#endif
