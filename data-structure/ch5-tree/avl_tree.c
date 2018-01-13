#include <stdlib.h>
#include <stdio.h>
#include "avl_tree.h"

AvlTree
make_empty(AvlTree root)
{
    if(!root){
        make_empty(root->left);
        make_empty(root->right);
        free(root);
    }
    return NULL;
}

Position
find_min(AvlTree root)
{
    if(!root)
        return NULL;
    while(!root->left)
        root = root->left;
    return root;
}

Position
find_max(AvlTree root)
{
    if(!root)
        return NULL;
    while(!root->right)
        root = root->right;
    return root;
}

Position
find(AvlTree root, Element x)
{
    if(!root)
        return NULL;
    else if(x < root->element)
        return find(root->left, x);
    else if(x > root->element)
        return find(root->right, x);
    else
        return root;
}

#define _MAX(a,b) (a)>(b)?(a):b

int
height(AvlTree root)
{
    if(!root)
        return -1;
    return _MAX(height(root->left), height(root->right)) + 1;
}

Position
single_rotate_left(Position root)
{
    AvlTree lson = root->left;
    root->left = lson->right;
    lson->right = root;
    return lson;
}

Position
single_rotate_right(Position root)
{
    AvlTree rson = root->right;
    root->right = rson->left;
    rson->left = rson;
    return rson;
}

Position
double_rotate_left(Position root)
{
    root->left = single_rotate_right(root->left);
    return single_rotate_left(root);
}

Position
double_rotate_right(Position root)
{
    root->right = single_rotate_left(root->left);
    return single_rotate_right(root);
}

Position
insert(AvlTree root, Element x)
{
    if(!root){
        if((root=(AvlTree)malloc(sizeof(AvlTree))) == NULL)
        {
            fprintf(stderr, "malloc error\n");
            exit(1);
        }
        else
        {
            root->left = root->right = NULL;
            root->element = x;
        }
    }
    else if (x < root->element)
    {
        root->left = insert(root->left, x);
        if (height(root->left) - height(root->right) == 2)
        {
            if(x < root->left->element)
                root = single_rotate_left(root);
            else
                root = double_rotate_left(root);
        }
    }
    else if (x > root->element)
    {
        root->right = insert(root->right, x);
        if (height(root->right) - height(root->left) == 2)
        {
            if (x < root->left->element)
                root = double_rotate_right(root);
            else
                root = single_rotate_right(root);
        }
    }
    return root;
}

/* static Element */
/* _delete_min(AvlTree root) */
/* { */
/*     if(!root) */
/*     { */
/*         fprintf(stderr, "empyt tree.\n"); */
/*         exit(1); */
/*     } */
/*     Element ret; */
/*     while(root->left) */
/*         root = root->left; */
/*     ret = root->element; */
/*     free(root); */
/*     return ret; */
/* } */

/* Position */
/* delete(AvlTree root, Element x) */
/* { */
/*     if (!root) */
/*         fprintf(stderr, "element can not found.\n"); */
/*     else if (x < root->element) */
/*         root->left = delete(root->left, x); */
/*     else if ( x > root->element) */
/*         root->right = delete(root->right, x); */
/*     else */
/*     { */
/*         if (root->left && root->right) */
/*             root->element = _delete_min(root->right); */
/*         else */
/*         { */
/*             AvlTree tmp = root; */
/*             if(root->left) */
/*                 root = root->left; */
/*             else if (root->right) */
/*                 root = root->right; */
/*             free(tmp); */
/*         } */

/*     } */
/*     return root; */
/* } */
