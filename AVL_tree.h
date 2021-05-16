#ifndef AVL_TREE_H
#define AVL_TREE_H

#endif // AVL_TREE_H

#include "common_parts_trees.h"

struct node_avl {
    node_avl* left, * right;
    int h = 1;
};

void SmallTurn(node_avl *& now) {
    int bet = now->left->h - now->right->h;
    if (bet < 0) bet = -bet;
    if (bet <= 1) {
        return;

    } if (now->left->h > now->right->h) {
        if (now->left->left->h >= now->left->right->h) {
            node_avl
        }
    }
}
