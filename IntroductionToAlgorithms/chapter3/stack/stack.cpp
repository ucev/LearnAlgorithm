#include <iostream>
#include "stack.h"
#include <iostream>

MyStack::MyStack(int sz) :
    head(0),
    stackSize(sz)
{
    mStack = new int[sz];
    std::cout << "head: " << head << "\nstackSize: " << stackSize << std::endl;
}

MyStack::~MyStack()
{
    std::cout << "destructor" << std:: endl;
    delete [] mStack;
}

void MyStack::push(int num)
{
    if (!stackFull()) {
        mStack[head++] = num;
    }
}

int MyStack::pop()
{
    return mStack[--head];
}

int MyStack::getTop()
{
    return mStack[head - 1];
}

void MyStack::empty()
{
    head = 0;
}

int MyStack::size()
{
    return head;
}

bool MyStack::stackEmpty()
{
    return head == 0;
}

bool MyStack::stackFull()
{
    return head >= stackSize;
}
