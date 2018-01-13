#ifndef _AVL_TREE_H
#define _AVL_TREE_H

typedef struct AvlTreeNode* Position;
typedef struct AvlTreeNode* AvlTree;
typedef int Element;
struct AvlTreeNode{
    Element element;
    AvlTree left;
    AvlTree right;
};

AvlTree make_empty(AvlTree root);

Position find_min(AvlTree root);
Position find_max(AvlTree root);
Position find(AvlTree root, Element x);

int height(AvlTree root);

Position single_rotate_left(Position root);
Position single_rotate_right(Position root);
Position double_rotate_left(Position root);
Position double_rotate_right(Position root);
Position insert(AvlTree root, Element x);
/* Position delete(AvlTree root, Element x); */

#endif
