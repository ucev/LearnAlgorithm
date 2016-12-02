#ifndef __MY_BISEARCH_TREE
#define __MY_BISEARCH_TREE

struct Node {
    int key;
    Node* parent;
    Node* lchild;
    Node* rchild;
};

class BisearchTree {
public:
    BisearchTree();
    ~BisearchTree();
    void inorderWalk(Node* nd);
    void preorderWalk(Node* nd);
    Node* min(Node* nd);
    Node* max(Node* nd);
    Node* search(int k);
    Node* successor(Node* nd);
    Node* predecessor(Node* nd);
    void insertNode(Node* nd);
    void deleteNode(Node* nd);
    inline Node* getRoot() { return root;}
    void printTree();
private:
    int maxDepth;
    Node* root;
    void deleteAll(Node* nd);
};

#endif
