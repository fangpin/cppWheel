#ifndef _B_TREE_H
#define _B_TREE_H

#include <vector>
#include <memory>
#include <algorithm>

template<typename T>
class BTree;

template<typename T>
struct BTreeNode {
    // constructors
    BTreeNode() = delete;
    BTreeNode(const BTreeNode&) = default;
    BTreeNode(BTreeNode&&) = default;
    BTreeNode& operator=(const BTreeNode&) = default;
    BTreeNode& operator=(BTreeNode&&) = default;
    BTreeNode(bool leaf): leaf_(leaf){}

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

    void splitChild(int i, int t) {
        BTreeNode<T>* child = children_[i];
        BTreeNode<T>* rightNode = new BTreeNode<T>(child->leaf_);
        rightNode->keys_.assign(child->keys_.begin()+t, child->keys_.end());
        if (!child->leaf_)
            rightNode->children_.assign(child->children_.begin()+t, child->children_.end());
        keys_.insert(keys_.begin()+i, child->keys_[t-1]);
        children_.insert(children_.begin()+i+1, rightNode);
        child->keys_.erase(child->keys_.begin()+t-1, child->keys_.end());
        if (!child->leaf_)
            child->children_.erase(child->children_.begin()+t, child->children_.end());
    }

    void insertNonFull(int k, int t) {
        auto it = std::lower_bound(keys_.begin(), keys_.end(), k);
        // key already in this node.
        if (it != keys_.end() && *it == k)
            return;
        if (leaf_) {
            keys_.insert(it, k);
        }
        else {
            int i = it - keys_.begin();
            if (children_[i]->keys_.size() == 2 * t - 1 ) {
                splitChild(i, t);
                // k already in btree
                if (keys_[i] == k)
                    return ;
                if (keys_[i] < k)
                    ++i;
            }
            children_[i]->insertNonFull(k, t);
        }
    }

    bool leaf_; // wheather is leaf node
    std::vector<T> keys_; // store keys in this node.
    std::vector<BTreeNode<T>*> children_;  // children pointers

friend class BTree<T>;
};

template<typename T>
class BTree {
public:
    // constructors
    BTree(int t): t_(t), root_(nullptr) {}
    BTree() = delete;
    BTree(const BTree&) = default;
    BTree(BTree&&) = default;
    BTree& operator=(const BTree&) = default;
    BTree& operator=(BTree&&) = default;

    ~BTree() {}

    T* search(const T& rhs) {
        return root_->search(rhs);
    }

    void traverse(std::vector<T>& rhs) {
        root_->traverse(rhs);
    }

    // a new key is always inserted at leave node.
    void insert(const T& rhs) {
        if (root_ == nullptr) {
            root_ = new BTreeNode<T>(true);
            root_->keys_.push_back(rhs);
        }
        else {
            if (root_->keys_.size() == 2 * t_ - 1) {
                BTreeNode<T>* newRoot = new BTreeNode<T>(false);
                newRoot->children_.push_back(root_);
                newRoot->splitChild(0, t_);
                root_ = newRoot;
                if (root_->keys_[0] == rhs)
                    return;
                int i=0;
                if (root_->keys_[0] < rhs)
                    ++i;
                root_->children_[i]->insertNonFull(rhs, t_);
            }
            else
                root_->insertNonFull(rhs, t_);
        }
    }

private:
    BTreeNode<T>* root_;
    size_t t_; // minimal degree of B Tree
};



#endif // #ifndef _B_TREE_H
