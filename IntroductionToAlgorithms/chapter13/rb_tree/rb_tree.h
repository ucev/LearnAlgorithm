#ifndef __MY_RED_BLACK_TREE
#define __MY_RED_BLACK_TREE

enum NodeColor { RED, BLACK};

class Node {
public:
    int key;
    NodeColor color;
    Node* parent;
    Node* lchild;
    Node* rchild;
    Node(int k = 0, NodeColor c = RED, Node* p = NULL, Node* l = NULL, Node* r = NULL);
    friend std::ostream& operator<<(std::ostream&, const Node* const);
};

class RBTree {
public:
    RBTree();
    ~RBTree();
    void insertNode(Node*);
    void deleteNode(Node*);
    void inorderWalk(Node*);
    void preorderWalk(Node*);
    Node* getRoot();
    Node* successor(Node*);
private:
    Node* root;
    // 终止标记
    Node* snode;
    void leftRotate(Node*);
    void rightRotate(Node*);
    void insertFixup(Node*);
    void deleteFixup(Node*);
    void deleteAll(Node*);
    bool isNull(Node*);
};

std::ostream & operator<<(std::ostream&, const Node* const);

#endif
