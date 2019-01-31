#ifndef _B_TREE_H
#define _B_TREE_H

#include <vector>
#include <memory>

template<typename T>
class BTree;

template<typename T>
class BTreeNode {
public:
    // constructors
    BTreeNode() = delete;
    BTreeNode(const BTreeNode&) = default;
    BTreeNode(BTreeNode&&) = default;
    BTreeNode& operator=(const BTreeNode&) = default;
    BTreeNode& operator=(BTreeNode&&) = default;
    BTreeNode(int t, bool leaf):t_(t), leaf_(leaf){};

    ~BTreeNode() {}

    T* search(const T& rhs) {
        size_t i = 0;
        for (; i<keys_.size() && keys_[i] < rhs; ++i);
        if (i<keys_.size() && keys_[i]==rhs)
            return &keys_[i];
        if (leaf_) return nullptr;
        return children_[i].search(rhs);
    }

    void traverse(std::vector<T>& rhs) {
        size_t i = 0;
        for (; i<keys_.size(); ++i) {
            if (!leaf_) {
                children_[i]->traverse(rhs);
            }
            rhs.push_back(keys_[i]);
        }
        if (!leaf_) {
            children_[i]->traverse(rhs);
        }
    }
private:
    int t_; // minimal degree of B Tree
    // int n_; // current number of elements in this node.
    bool leaf_; // wheather is leaf node
    std::vector<T> keys_; // store keys in this node.
    std::vector<BTreeNode<T>*> children_;  // children pointers

friend class BTree<T>;
};

template<typename T>
class BTree {
public:
    // constructors
    BTree(int t): t_(t) {
        root_ = std::make_shared<BTreeNode<T>>(t_, true);
    }
    BTree() = delete;
    BTree(const BTree&) = default;
    BTree(BTree&&) = default;
    BTree& operator=(const BTree&) = default;
    BTree& operator=(BTree&&) = default;

    ~BTree() {}

    T* search(const T& rhs) {
        return root_->search(rhs);
    }

    void traverse(std::vector<BTreeNode<T>>& rhs) {
        root_->traverse(rhs);
    }

private:
    std::shared_ptr<BTreeNode<T>> root_;
    int t_; // minimal degree of B Tree
};



#endif // #ifndef _B_TREE_H
