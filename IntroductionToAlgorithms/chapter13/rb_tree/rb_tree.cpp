#include <iostream>
#include "rb_tree.h"

using namespace std;

Node::Node(int k, NodeColor c, Node* p, Node* l, Node* r):
    key(k), color(c), parent(p), lchild(l), rchild(r) {
}

RBTree::RBTree() {
    snode = new Node(0, BLACK);
    root = snode;
}

RBTree::~RBTree() {
    deleteAll(root);
    delete snode;
}

void RBTree::insertNode(Node* n) {
    int k = n->key;
    Node* x = root;
    Node* y = snode;
    while (!isNull(x)) {
        y = x;
        if (x->key > k) {
	    x = x->lchild;
	} else {
	    x = x->rchild;
	}
    }
    n->parent = y;
    if (isNull(y)) {
        root = n;
    } else {
        if (y->key > k) {
            y->lchild = n;
        } else {
            y->rchild = n;
        }
    }
    n->lchild = snode;
    n->rchild = snode;
    insertFixup(n);
}

void RBTree::deleteNode(Node* n) {
    Node* y = n;
    if (n->lchild != snode && n->rchild != snode) {
        y = successor(n);
    }
    Node* x = y->lchild;
    if (y->lchild == snode) {
        x = y->rchild;
    }
    if (x != snode) {
        x->parent = y->parent;
    }
    if (y->parent == snode) {
        root = x;
    } else {
        if (y == y->parent->lchild) {
	    y->parent->lchild = x;
	} else {
	    y->parent->rchild = x;
	}
    }
    if (y != n) {
        n->key = y->key;
    }
    cout << (y->color == BLACK ? "B" : "R") << "   key:" << y->key << endl;
    if (y->color == BLACK) {
        cout << "delete" << endl;
        deleteFixup(x);
    }
    delete y;
}

void RBTree::inorderWalk(Node* n) {
    if (isNull(n))
        return;
    inorderWalk(n->lchild);
    std::cout << n;
    inorderWalk(n->rchild);
}

void RBTree::preorderWalk(Node* n) {
    if (isNull(n))
        return;
    std::cout << n << "   ";
    preorderWalk(n->lchild);
    preorderWalk(n->rchild);
}

Node* RBTree::getRoot() {
    return root;
}

Node* RBTree::successor(Node* n) {
    if (n == snode) {
        return NULL;
    }
    if (n->rchild != snode) {
        Node* x = n->rchild;
	while (x->lchild != snode) {
	    x = x->lchild;
	}
	return x;
    }
    Node* p = n->parent;
    while (p != snode && p != p->parent->lchild) {
        p = p->parent;
    }
    return p == snode ? NULL : p;
}

void RBTree::leftRotate(Node* n) {
    if (isNull(n))
        return;
    Node* r = n->rchild;
    if (isNull(r))
        return;
    r->parent = n->parent;
    if (n == root) {
        root = r;
	root->color = BLACK;
    } else {
        if (n == n->parent->lchild) {
	    n->parent->lchild = r;
	} else {
	    n->parent->rchild = r;
	}
    }
    n->parent = r;
    n->rchild = r->lchild;
    if (!isNull(n->rchild)) {
        n->rchild->parent = n;
    }
    r->lchild = n;
}

void RBTree::rightRotate(Node* n) {
    if (isNull(n))
        return;
    Node* l = n->lchild;
    if (isNull(l))
        return;
    l->parent = n->parent;
    if (isNull(n->parent)) {
        root = l;
	root->color = BLACK;
    } else {
        if (n == n->parent->lchild) {
	    n->parent->lchild = l;
	} else {
	    n->parent->rchild = l;
	}
    }
    n->parent = l;
    n->lchild = l->rchild;
    if (!isNull(n->lchild)) {
        n->lchild->parent = n;
    }
    l->rchild = n;
}

void RBTree::insertFixup(Node* n) {
    if (n == root) {
        n->color = BLACK;
	return;
    }
    if (n->parent->color == BLACK) {
        return;
    }
    Node* np = n->parent;
    if (np == np->parent->lchild) {
        Node* y = np->parent->rchild;
	if (y->color == RED) {
	    np->color = BLACK;
	    y->color = BLACK;
	    np->parent->color = RED;
	    insertFixup(np->parent);
	} else {
	    if (n == np->rchild) {
	        leftRotate(np);
		n = np;
		np = n->parent;
	    }
	    np->parent->color = RED;
	    np->color = BLACK;
	    rightRotate(np->parent);
	}
    } else {
        Node* y = np->parent->lchild;
	if (y->color == RED) {
	    np->color = BLACK;
	    y->color = BLACK;
	    np->parent->color = RED;
	    insertFixup(np->parent);
	} else {
	    if (n == np->lchild) {
	        rightRotate(np);
		n = np;
		np = n->parent;
	    }
	    np->parent->color = RED;
	    np->color = BLACK;
	    leftRotate(np->parent);
	}
    }
}

void RBTree::deleteFixup(Node* n) {
    if (isNull(n)) {
        return;
    }
    if (n == root || n->color == RED) {
        n->color = BLACK;
	return;
    }
    if (n == n->parent->lchild) {
        Node* w = n->parent->rchild;
	if (w->color == RED) {
	    w->color = BLACK;
	    n->parent->color = RED;
	    leftRotate(n->parent);
	    w = n->parent->rchild;
	}
	if (w->lchild->color == BLACK && w->rchild->color == BLACK) {
	    w->color = RED;
	    deleteFixup(n->parent);
	} else {
	    if (w->rchild->color == BLACK) {
	        w->lchild->color = BLACK;
		w->color = RED;
		rightRotate(w);
		w = n->parent->rchild;
	    }
	    w->color = n->parent->color;
	    n->parent->color = BLACK;
	    w->rchild->color = BLACK;
	    leftRotate(n->parent);
	    deleteFixup(root);
	}
    } else {
        Node* w = n->parent->lchild;
	if (w->color == RED) {
	    w->color = BLACK;
	    n->parent->color = RED;
	    rightRotate(n->parent);
	    w = n->parent->lchild;
	}
	if (w->lchild->color == BLACK && w->rchild->color == BLACK) {
	    w->color = RED;
	    deleteFixup(n->parent);
	} else {
	    if (w->lchild->color == BLACK) {
	        w->rchild->color = BLACK;
		w->color = RED;
		leftRotate(w);
		w = n->parent->lchild;
	    }
	    w->color = n->parent->color;
	    n->parent->color = BLACK;
	    w->lchild->color = BLACK;
	    rightRotate(n->parent);
	    deleteFixup(root);
	}
    }
}

void RBTree::deleteAll(Node* n) {
    if (isNull(n))
        return;
    deleteAll(n->lchild);
    deleteAll(n->rchild);
    delete n;
}

bool RBTree::isNull(Node* n) {
    return n == NULL || n == snode;
}

std::ostream& operator<<(std::ostream& os, const Node* const n) {
    os << "Node(key: " << n->key << " , color: " << (n->color == BLACK ? "B" : "R") << " , parent: " << n->parent->key << " , l:" << n->lchild->key << " ,r:" << n->rchild->key << ")" << std::endl;
    return os;
}
