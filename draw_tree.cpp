#include "draw_tree.h"

void clearDraw(node_draw* now) {
    if (!now) return;
    clearDraw(now->left);
    clearDraw(now->right);
    delete(now);
}


int constructTreeDraw(node_draw * now,
                    node_splay * splay_now,
                    node_avl * avl_now,
                    node_treap * node_treap) {
    if (splay_now == nullptr && avl_now == nullptr && node_treap == nullptr)
        return 0;

    if (splay_now != nullptr) {
        now->num = splay_now->num;
        if (splay_now->left) {
            now->left = new node_draw;
        }
        if (splay_now->right) {
            now->right = new node_draw;
        }
        now->hight = std::max(constructTreeDraw(now->left, splay_now->left),
                         constructTreeDraw(now->right, splay_now->right));
    } else if (avl_now != nullptr) {
        now->num = avl_now->num;
        if (avl_now->left) {
            now->left = new node_draw;
        }
        if (avl_now->right) {
            now->right = new node_draw;
        }
        now->hight = std::max(constructTreeDraw(now->left, nullptr, avl_now->left),
                         constructTreeDraw(now->right, nullptr, avl_now->right));
    } else if (node_treap != nullptr) {
        now->num = node_treap->x;
        if (node_treap->left) {
            now->left = new node_draw;
        }
        if (node_treap->right) {
            now->right = new node_draw;
        }
        now->hight = std::max(constructTreeDraw(now->left, nullptr, nullptr, node_treap->left),
                         constructTreeDraw(now->right, nullptr, nullptr, node_treap->right));
    }
    return now->hight + 1;
}
