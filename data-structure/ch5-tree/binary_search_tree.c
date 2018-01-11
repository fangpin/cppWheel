#include <stdlib.h>
#include <stdio.h>
#include "binary_search_tree.h"

SearchTree
make_empty(SearchTree root){
    if(!root){
        make_empty(root->left);
        make_empty(root->right);
        free(root);
    }
    return NULL;
}

Position
find_min(SearchTree root){
    if(!root)
        return NULL;
    while(!root->left)
        root = root->left;
    return root;
}

Position
find_max(SearchTree root){
    if(!root)
        return NULL;
    while(!root->right)
        root = root->right;
    return root;
}

Position
find(SearchTree root, Element x){
    if(!root)
        return NULL;
    else if(x < root->element)
        return find(root->left, x);
    else if(x > root->element)
        return find(root->right, x);
    else
        return root;
}

Position
insert(SearchTree root, Element x){
    if(!root){
        if((root=(SearchTree)malloc(sizeof(SearchTree))) == NULL)
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
        root->left = insert(root->left, x);
    else if (x > root->element)
        root->right = insert(root->right, x);
    return root;
}

static Element
_delete_min(SearchTree root)
{
    if(!root)
    {
        fprintf(stderr, "empyt tree.\n");
        exit(1);
    }
    Element ret;
    while(root->left)
        root = root->left;
    ret = root->element;
    free(root);
    return ret;
}

Position
delete(SearchTree root, Element x)
{
    if (!root)
        fprintf(stderr, "element can not found.\n");
    else if (x < root->element)
        root->left = delete(root->left, x);
    else if ( x > root->element)
        root->right = delete(root->right, x);
    else
    {
        if (root->left && root->right)
            root->element = _delete_min(root->right);
        else
        {
            SearchTree tmp = root;
            if(root->left)
                root = root->left;
            else if (root->right)
                root = root->right;
            free(tmp);
        }

    }
    return root;
}
