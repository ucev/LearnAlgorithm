#include <iostream>
#include <string>
#include "stack.h"

using namespace std;

#define PUSH_CODE 1
#define POP_CODE 2
#define CHECK_EMPTY_CODE 3

int main()
{
    bool opeFinished = false;
    MyStack* myStack = new MyStack();
    while (!opeFinished) {
        cout << "选择你要的操作：\n"
             << "\t1、添加"
	     << "\t0、结束操作"
	     << endl;
        int ope;
        cin >> ope;
        switch(ope) {
           case 1:
	       int num;
	       cout << "输入要添加的数字：";
	       cin >> num;
	       myStack->push(num);
	       break;
	   case 0:
	       opeFinished = true;
	       break;
        }
    }
    cout << "当前栈为：";
    while (!myStack->stackEmpty()) {
	cout << myStack->pop() << ", ";
    }
    cout << endl;
    delete myStack;
    return 0;
}
