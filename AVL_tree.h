#ifndef AVL_TREE_H
#define AVL_TREE_H

#endif // AVL_TREE_H

#include "common_parts_trees.h"
#include <iostream>

struct node_avl {
    node_avl* left, * right;
    int h = 1;
};

void SmallTurn(node_avl *& now) {
    node_avl * left = now->left, * right = now->right;

    try{
        if (left->left->h >= left->right->h) {
            node_avl * c = left->right;
            left->right = now;
            now->left = c;
            now = left;
            return;
        } else if (right->right->h >= right->left->h) {
            node_avl * c = right->left;
            right->left = now;
            now->right = c;
            now = right;
        } else {
            throw 42;
        }
    } catch (int i) {
        std::cout << "NOT A SMALL TURN\n";
        exit(0);
    } catch (...) {
        std::cout << "WTF HAPPENED IN SMALL TURN\N";
        exit(0);
    }
}

void BigTurn(node_avl *& now) {

}
void Turn(node_avl *& now) {  // h and h+2, not more
    node_avl * left = now->left, * right = now->right;
    int bet = left->h - right->h;

    if (bet < 0) bet = -bet;
    if (bet <= 1) {
        return;
    }

    if (left->h > right->h) {
        if (left->left->h >= left->right->h) {
            SmallTurn(now);
        } else {
    }
}
