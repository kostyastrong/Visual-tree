#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include <iostream>

struct node_splay{
    node_splay * left, * right;
    node_splay * parent = NULL; // for root
    int num;
};

void Zig(node_splay *& now, node_splay *& root) {
    node_splay * right = now->right;
    now->right = now->parent;
    now->parent->left = right;
    now->parent = now;
    // а как с parent быть и че по удалению
}

void ZigZig(node_splay *& now) {

}

#endif // SPLAY_TREE_H
