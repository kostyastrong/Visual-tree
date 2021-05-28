#include "splay_tree.h"

#include <iostream>

void ZigSplay(node_splay *& now, node_splay *& root) {  // zig only for root
    node_splay * right = now->right, * left = now->left;
    if (now == root->left) {
        root->left = right;
        now->right = root;
    } else {
        root->right = left;
        now->left = root;
    }
    root->parent = now;
    now->parent = nullptr;
    root = now;
}

void ZigZigSplay(node_splay *& now, node_splay *& root) {
    node_splay * par = now->parent, * par_of_par = par->parent, * god = nullptr;
    if (par_of_par->parent != nullptr) {
        god = par_of_par->parent;
        if (god->left == par_of_par) {
            god->left = now;
        } else {
            now->parent = nullptr;
            god->right = now;
        }
    }
    else {
        root = now;
    }
    now->parent = god;
    if (par->left == now) {  // hence, par_of_par->left = par
        node_splay  * right = now->right, * par_right = par->right;

        now->right = par;

        par->parent = now;
        par->right = par_of_par;
        par->left = right;

        par_of_par->parent = par;
        par_of_par->left = par_right;
    } else {
        node_splay * left = now->left, * par_left = par->left;

        now->left = par;

        par->parent = now;
        par->right = left;
        par->left = par_of_par;

        par_of_par->parent = par;
        par_of_par->right = par_left;
    }
}

void ZigZagSplay(node_splay * now, node_splay *& root) {
    node_splay * par = now->parent, * par_of_par = par->parent, * god = nullptr;
    if (par_of_par->parent != nullptr) {
        god = par_of_par->parent;
        if (god->left == par_of_par) {
            god->left = now;
        } else god->right = now;
        now->parent = god;
    }
    else {
        now->parent = nullptr;
        root = now;
    }

    node_splay * left = now->left, * right = now->right;

    if (par->left == now) {
        now->left = par_of_par;
        now->right = par;

        par->left = right;
        par->parent = now;

        par_of_par->right = left;
        par_of_par->parent = now;
    } else {
        now->left = par;
        now->right = par_of_par;

        par->right = left;
        par->parent = now;

        par_of_par->left = right;
        par_of_par->parent = now;
    }
}

void Splay(node_splay * now, node_splay *& root) {
    if (now == root) return;
    if (now->parent == root) ZigSplay(now, root);
    else {
        node_splay * par = now->parent, * par_of_par = par->parent;
        if (par_of_par->left == par && par->left == now ||
            par_of_par->right == par && par->right == now) {
            ZigZigSplay(now, root);
        } else ZigZagSplay(now, root);
    }
}

node_splay * InsertIterSplay(node_splay *& now, int num) {
    if (now == nullptr) { // root
        now = new node_splay;
        now->num = num;
        return now;
    }
    if (now->num > num) {
        if (now->left != nullptr) return InsertIterSplay(now->left, num);
        else {
            now->left = new node_splay;
            now->left->parent = now;
            now->left->num = num;
            return now->left;
        }
    } else if (now->num < num){
        if (now->right != nullptr) return InsertIterSplay(now->right, num);
        else {
            now->right = new node_splay;
            now->right->parent = now;
            now->right->num = num;
            return now->right;
        }
    } else {
        return now;
    }
}

void InsertSplay(node_splay *&root, int num) {
    node_splay * place = InsertIterSplay(root, num);
    Splay(place, root);
}

node_splay* FindNodeSplay(node_splay * now, int num) {
    if (!now) return nullptr;
    if (now->num == num) return now;
    if (now->num > num) return FindNodeSplay(now->left, num);
    return FindNodeSplay(now->right, num);
}

node_splay* FindMaxNodeSplay(node_splay *now) {
    if (!now) return nullptr;
    if (now->right == nullptr) return now;
    return FindMaxNodeSplay(now->right);
}

node_splay * FindMinNodeSplay(node_splay *now) {
    if (!now) return nullptr;
    if (now->left == nullptr) return now;
    return FindMinNodeSplay(now);
}

void DeleteSplay(node_splay*& root, int num) {
    node_splay * place = FindNodeSplay(root, num);
    Splay(place, root);  // place is now root
    node_splay * root_left = place->left, * root_right = place->right;
    if (root_left != nullptr) root_left->parent = nullptr;
    if (root_right != nullptr) root_right->parent = nullptr;
    delete(root);
    if (root_left == nullptr && root_right == nullptr) {
        root = nullptr;
        return;
    }


    node_splay  * top_left = FindMaxNodeSplay(root_left),
                * top_right = FindMinNodeSplay(root_right);

    if (top_left != nullptr) {
        Splay(top_left, root_left);
        top_left->right = root_right;
        if (root_right != nullptr) root_right->parent = top_left;
        root = top_left;
    } else {  // left root son is null, so we can easy assign
        root = root_right;
    }
}

