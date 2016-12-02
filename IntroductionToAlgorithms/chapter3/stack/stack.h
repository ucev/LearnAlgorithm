#ifndef __STACK_HEADER__
#define __STACK_HEADER__

#define STACK_DEFAULT_SIZE 100

class MyStack {
private:
    int head;
    int stackSize;
    int* mStack;
public:
    MyStack(int sz = STACK_DEFAULT_SIZE);
    ~MyStack();
    void push(int num);
    int pop();
    int getTop();
    void empty();
    int size();
    bool stackEmpty();
    bool stackFull();
};

#endif
