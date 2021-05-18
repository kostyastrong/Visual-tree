#ifndef AVL_TREE_H
#define AVL_TREE_H

#endif // AVL_TREE_H

#include "common_parts_trees.h"
#include <iostream>

struct node_avl {
    node_avl* left, * right;
    int h = 1;
    int num;
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
            throw 42;  // oop for fun
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
    node_avl * left = now->left, * right = now->right;
    if (left->h < right->h) {
        node_avl * goal = right->left, * goal_left = goal->left, * goal_right = goal->right;
        goal->left = now;
        goal->right = right;
        now->right = goal_left;
        right->left = goal_right;
        now = goal;
    } else {
        node_avl * goal = left->right, * goal_left = goal->left, * goal_right = goal->right;
        goal->left = left;
        goal->right = now;
        now->left = goal_right;
        left->right = goal_left;
        now = goal;
    }
}

int MaxHighOfChilds(node_avl * now) {
    return std::max(now->left == NULL ? 0 : now->left->h,
               now->right == NULL ? 0 : now->right->h);
}

node_avl * MaxChildDeleting(node_avl * now, bool dif_way = false) {
    if (!dif_way && now->right != NULL) {
        node_avl * x = MaxChildDeleting(now->right);
        if (now->right == x) {
            now->right = NULL;
        }
        now->h = 1 + MaxHighOfChilds(now);
        return x;
    } else if (dif_way && now->left != NULL) {
        node_avl * x = MaxChildDeleting(now->left);
        if (now->left == x) {
            now->left = NULL;
        }
        now->h = 1 + MaxHighOfChilds(now);
        return x;
    }
    return now;
}

node_avl * MinChildDeleting(node_avl * now, bool dif_way = false) {
    if (!dif_way && now->left != NULL) {
        node_avl * x = MinChildDeleting(now->left);
        if (now->left == x) {
            now->left = NULL;
        }
        now->h = 1 + MaxHighOfChilds(now);
        return x;
    } else if (dif_way && now->right != NULL) {
        node_avl * x = MinChildDeleting(now->left);
        if (now->right == x) {
            now->right = NULL;
        }
        now->h = 1 + MaxHighOfChilds(now);
        return x;
    }
    return now;
}

void Insert(node_avl * now, int new_num) {
    if (new_num < now->num) {
        if (now->left != NULL) {
            Insert(now->left, new_num);
            now->h = 1 + MaxHighOfChilds(now);
        } else {
            now->left = new node_avl;
            now->left->num = new_num;
            now->left->h = 1;
        }
    } else {
        if (now->right != NULL) {
            Insert(now->right, new_num);
            now->h = 1 + MaxHighOfChilds(now);
        } else {
            now->right = new node_avl;
            now->right->num = new_num;
            now->right->h = 1;
        }
    }
}

void DeleteIter(node_avl *& now, node_avl * deleting) {
    if (now == deleting) {
        if (now->left != NULL){
            node_avl * new_node = MinChildDeleting(now, true);
        } else if (now->right != NULL){
            node_avl * new_node = MaxChildDeleting(now, true);
        } else {
            delete(now);
            return;
        }
        delete(now);

    }
}

void DeleteNode(node_avl *& root, node_avl * deleting) {
    DeleteIter(root, deleting);

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
            BigTurn(now);
        }
    } else {
        if (right->right->h >= right->left->h) {
            SmallTurn(now);
        } else {
            BigTurn(now);
        }
    }
}
