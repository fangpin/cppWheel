#ifndef _BINARY_SEARCH_TREE_H
#define _BINARY_SEARCH_TREE_H

typedef struct TreeNode* Position;
typedef struct TreeNode* SearchTree;
typedef int Element;
struct TreeNode{
    Element element;
    SearchTree left;
    SearchTree right;
};

SearchTree make_empty(SearchTree root);
Position find_min(SearchTree root);
Position find_max(SearchTree root);
Position find(SearchTree root, Element x);
Position insert(SearchTree root, Element x);
Position delete(SearchTree root, Element x);

#endif
