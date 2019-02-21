#ifndef _B_TREE_H
#define _B_TREE_H

#include <vector>
#include <memory>
#include <algorithm>

template<typename T>
class BTree;

template<typename T>
struct BTreeNode {
public:
    // constructors
    BTreeNode() = delete;
    BTreeNode(const BTreeNode&) = delete;
    BTreeNode(BTreeNode&&) = delete;
    BTreeNode& operator=(const BTreeNode&) = delete;
    BTreeNode& operator=(BTreeNode&&) = delete;
    BTreeNode(bool leaf, BTreeNode<T>* parent=nullptr): leaf_(leaf), parent_(parent){}

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

    // erase rhs in B-Tree, rhs should be in the B-Tree
    void erase(BTreeNode<T>* parent, const T& rhs, size_t t) {
        auto it = std::lower_bound(keys_.begin(), keys_.end(), rhs);
        // found rhs in this node
        if (it != keys_.end() && *it == rhs) {
            // leaf node: erase directly and then check wheather need to adjust the tree.
            if (leaf_) {
                    keys_.erase(it);
                    checkAdjust(parent, t);
            }
            // nonleaf: replace by its succssor and erase recursively.
            else {
                *it = findSucc(children_[it - keys_.begin()]);
                children_[it - keys_.begin()]->erase(this, rhs);
            }
        }
        // go on to find rhs in the child of this node
        else {
            children_[it - keys_.begin()]->erase(this, rhs, t);
        }
    }

private:
    static T findSucc(BTreeNode<T>* node) {
        while (!node->leaf_)
            node = node->children_[0];
        return node->keys_.[0];
    }

    // adjust this node if needed: the number of keys <= t-1
    void checkAdjust(BTreeNode<T>* parent, const size_t& t) {
        if (keys_.size() <= t-1) {
            auto it = std::find(parent->children_.begin(), parent->children_.end(), this);
            // choose the left sibling except the last one.
            auto itSibling = (it == parent->children_.begin() ? it + 1 : it - 1 );
            BTreeNode<T>* sibling = *itSibling;
            // auto itParentKey = it - parent->children_.begin() - 1;
            size_t thisOffset = it - parent->children_.begin();
            // borrow
            if (sibling->keys_.size() > t - 1) {
                // borrow left
                if (itSibling < it) {
                    
                }
                // borrow right
                else {
                    
                }
            }
            // merge left
            else if (itSibling < it) {
                sibling->keys_.insert(sibling->keys_.end(), parent->keys_.[thisOffset - 1]);
                sibling->keys_.insert(sibling->keys_.end(), keys_.begin(), keys_.end());
                sibling->children_.insert(children_.begin(), children_.end());
                parent->children_.erase(it);
                parent->keys_.erase(parent->keys_.begin() + thisOffset - 1);
                delete this;
            }
            // merge right
            else {
                
            }
        }
    }

    bool leaf_; // wheather is leaf node
    std::vector<T> keys_; // store keys in this node.
    std::vector<BTreeNode<T>*> children_;  // children pointers
    BTreeNode<T>* parent_; // pointer to parent

    friend class BTree<T>;
};

template<typename T>
class BTree {
public:
    // constructors
    BTree(size_t t): t_(t), root_(nullptr) {}
    BTree() = delete;
    BTree(const BTree&) = delete;
    BTree(BTree&&) = delete;
    BTree& operator=(const BTree&) = delete;
    BTree& operator=(BTree&&) = delete;

    ~BTree() {}

    T* search(const T& rhs) {
        return root_ == nullptr ? nullptr : root_->search(rhs);
    }

    void traverse(std::vector<T>& rhs) {
        root_->traverse(rhs);
    }

    // a new key is always inserted at leave node.
    void insert(const T& rhs) {
        // empty B-Tree
        if (root_ == nullptr) {
            root_ = new BTreeNode<T>(true, nullptr);
            root_->keys_.push_back(rhs);
        }
        else {
            BTreeNode<T>* node = root_;
            // find the leaf node to insert the value
            while (!node->leaf_) {
                auto it = std::lower_bound(node->keys_.begin(), node->keys_.end(), rhs);
                // the value to be inserted is already in this B-Tree.
                if (it != node->keys_.end() && *it == rhs)
                    return ;
                node = node->children_[it - node->keys_.begin()];
            }
            splitInsert(node, rhs, t_, nullptr);
        }
    }

    // erase a value, return false if the value is not in this B-Tree
    bool erase(const T& rhs) {
        if (!search(rhs))
            return false;
        root_->erase(nullptr, rhs);
        return true;
    }

private:
    void splitInsert(BTreeNode<T>* node, const T& rhs, const size_t t, BTreeNode<T>* rchild=nullptr) {
        auto it = std::lower_bound(node->keys_.begin(), node->keys_.end(), rhs);
        if (!node->leaf_ && rchild!=nullptr) {
            node->children_.insert(node->children_.begin() + (it - node->keys_.begin() + 1), rchild);
            rchild->parent_ = node;
        }
        node->keys_.insert(it, rhs);
        if (node->keys_.size() == 2 * t) {
            BTreeNode<T>* parent = node->parent_;
            if (parent == nullptr) {
                parent = new BTreeNode<T>(false, nullptr);
                node->parent_ = parent;
                parent->children_.push_back(node);
                root_ = parent;
            }
            BTreeNode<T>* sibling = new BTreeNode<T>(node->leaf_, node->parent_);
            sibling->keys_.assign(node->keys_.begin() + t + 1, node->keys_.end());
            if (!node->leaf_) {
                sibling->children_.assign(node->children_.begin() + t + 1, node->children_.end());
                for (auto it = sibling->children_.begin(); it!=sibling->children_.end(); ++it) {
                    (*it)->parent_ = sibling;
                }
            }
            T midKey = std::move(node->keys_[t]);
            node->keys_.erase(node->keys_.begin() + t, node->keys_.end());
            node->children_.erase(node->children_.begin() + t + 1, node->children_.end());
            splitInsert(parent, midKey, t, sibling);
        }
    }

    BTreeNode<T>* root_;
    size_t t_; // degree of B Tree: the number of keys in a node must be in range: [t-1, 2*t-1].
}; // class BTree

#endif // #ifndef _B_TREE_H
