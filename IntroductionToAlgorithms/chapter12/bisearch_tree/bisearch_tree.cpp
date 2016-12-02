#include <iostream>
#include "bisearch_tree.h"

BisearchTree::BisearchTree() {
    root = NULL;
    maxDepth = 0;
}

BisearchTree::~BisearchTree() {
    deleteAll(root);
}

void BisearchTree::deleteAll(Node* nd) {
    // 设置NULL
    if (nd == NULL)
        return;
    deleteAll(nd->lchild);
    deleteAll(nd->rchild);
    delete nd;
}

void BisearchTree::inorderWalk(Node* nd) {
    if (nd == NULL)
        return;
    inorderWalk(nd->lchild);
    std::cout << nd->key << ", ";
    inorderWalk(nd->rchild);
    if (nd->parent == NULL) {
        std::cout << std::endl;
    }
}

void BisearchTree::preorderWalk(Node * nd) {
    if (nd == NULL)
        return;
    std::cout << nd->key << ", ";
    preorderWalk(nd->lchild);
    preorderWalk(nd->rchild);
    if (nd->parent == NULL) {
        std::cout << std:: endl;
    }
}

Node* BisearchTree::min(Node* nd) {
    Node* n = nd;
    while (n->lchild != NULL)
        n = n->lchild;
    return n;
}

Node* BisearchTree::max(Node* nd) {
    Node* n = nd;
    while (n->rchild != NULL)
        n = n->rchild;
    return n;
}

Node* BisearchTree::search(int k) {
    Node* nd = root;
    while (nd != NULL && nd->key != k) {
        if (nd->key < k)
	    nd = nd->rchild;
	else
	    nd = nd->lchild;
    }
    return nd;
}

Node* BisearchTree::successor(Node* nd) {
    Node* n = nd;
    if (n->rchild != NULL) {
        n = n->rchild;
	while (n->lchild != NULL)
	    n = n->lchild;
	return n;
    }
    Node* p = n->parent;
    while (p != NULL && p->rchild == n) {
        n = p;
	p = n->parent;
    }
    return p;
}

Node* BisearchTree::predecessor(Node* nd) {
    Node* n = nd;
    if (n->lchild != NULL) {
        n = n->lchild;
	while (n->rchild != NULL)
	    n = n->rchild;
	return n;
    }
    Node* p = n->parent;
    while (p != NULL && p->lchild == n) {
        n = p;
	p = n->parent;
    }
    return p;
}

void BisearchTree::insertNode(Node* nd) {
    Node* n = root;
    if (n == NULL) {
        root = nd;
	return;
    }
    while (true) {
        if (n->key > nd->key) {
	    if (n->lchild != NULL) {
	        n = n->lchild;
	    } else {
	        break;
	    }
	} else {
	    if (n->rchild != NULL) {
	        n = n->rchild;
	    } else {
	        break;
	    }
	}
    }
    if (n->key > nd->key) {
        n->lchild = nd;
    } else {
        n->rchild = nd;
    }
    nd->parent = n;
}

void BisearchTree:: deleteNode(Node* nd) {
    Node* y = nd;
    if (nd->lchild != NULL && nd->rchild != NULL) {
        y = successor(nd);
    }
    Node* x = y->lchild;
    if (y->lchild == NULL) {
        x = y->rchild;
    }
    if (x != NULL) {
        x->parent = y->parent;
    }
    if (y->parent == NULL) {
        root = x;
	return;
    }
    if (y->parent->lchild == y) {
        y->parent->lchild = x;
    } else {
        y->parent->rchild = x;
    }
    if (y != nd) {
        nd->key = y->key;
    }
}

void BisearchTree::printTree() {
    
}
