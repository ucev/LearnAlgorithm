#include <iostream>
#include <ctime>
#include "rb_tree.h"

using namespace std;

#define ARRAY_LEN 20
#define MIN_VALUE 0
#define MAX_VALUE 100

void printArr(int* arr, int len) {
    for (int i = 0; i < len; i++) {
        cout << i << ":" << arr[i] << ", ";
    }
    cout << endl;
}

int main() {
    int arr[ARRAY_LEN] = {25, 11, 65, 40, 54, 31, 1, 89, 26, 22, 67, 2, 21, 52, 79, 99, 47, 74, 43, 5};
    printArr(arr, ARRAY_LEN);
    Node *(nodeArr)[ARRAY_LEN];
    RBTree* tree = new RBTree();
    for (int i = 0; i < ARRAY_LEN; i++) {
        nodeArr[i] = new Node(arr[i]);
	tree->insertNode(nodeArr[i]);
    }
    int nodeCount = ARRAY_LEN;
    int code;
    int od;
    bool exitLoop = false;
    while (true) {
        cout << "Enter code:[0: 退出 1: inorderWalk 2: preorderWalk 3: min 4: max 5: deleteNode 6: successor 7: predecessor] ";
	cin >> code;
	switch (code) {
	    case 0:
	        exitLoop = true;
	        break;
	    case 1:
	        tree->inorderWalk(tree->getRoot());
		cout << endl;
		break;
	    case 2:
	        tree->preorderWalk(tree->getRoot());
		cout << endl;
		break;
	    case 3:
	        //cout << "min: " << tree->min(tree->getRoot())->key << endl;
		break;
	    case 4:
	        //cout << "max: " << tree->max(tree->getRoot())->key << endl;
		break;
	    case 5:
	        cout << "输入删除节点的初始标记:";
		cin >> od;
		tree->deleteNode(nodeArr[od]);
		tree->inorderWalk(tree->getRoot());
		break;
	    case 6:
	        cout << "输入查找后继的节点的初始标记:";
		cin >> od;
		cout << "后继：" << tree->successor(nodeArr[od])->key << endl;
	        break;
	    case 7:
	        cout << "输入查找前驱的节点的初始标记:";
		cin >> od;
		//cout << "前驱：" << tree->predecessor(nodeArr[od])->key << endl;
	    default:
	        break;
	}
	if (exitLoop) {
	    break;
	}

    }
    cout << "Hello World!" << endl;
    return 0;
}
