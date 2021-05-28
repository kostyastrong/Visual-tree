#ifndef DRAW_TREE_H
#define DRAW_TREE_H

#include "avl_tree.h"
#include "splay_tree.h"
#include "treap.h"

struct node_draw{
    node_draw * left = nullptr, *right = nullptr;
    int num;
    int hight = 0; // max_hight of childs
};

void clearDraw(node_draw* now);

int constructTreeDraw(node_draw * now,
                    node_splay * splay_now = nullptr,
                    node_avl * avl_now = nullptr,
                    node_treap * node_treap = nullptr);

#endif // DRAW_TREE_H

