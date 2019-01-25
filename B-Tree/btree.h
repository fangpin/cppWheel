#ifndef _B_TREE_H
#define _B_TREE_H

#include <vector>

template<typename T>
class BTree;

template<typename T>
class BTreeNode {
public:
    BTreeNode() = delete;
    BTreeNode(int t, bool leaf);
    ~BTreeNode() {}
    typename std::vector<T>::iterator search(const T&);
    void traverse();
private:
    int t_; // minimal degree of B Tree
    int n_; // current number of elements in this node.
    bool leaf_; // wheather is leaf node
    std::vector<T> keys_; // store keys in this node.
    std::vector<BTreeNode<T>*> children_;  // children pointers

friend class BTree<T>;
};

template<typename T>
class BTree {
    
};



#endif // #ifndef _B_TREE_H
