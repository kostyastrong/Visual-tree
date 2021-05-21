#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>


struct node_avl {
    node_avl * left = nullptr, * right = nullptr;
    int h = 1;
    int num;
};

int h_node(node_avl * now);  // returning high of node
void RecalcHigh(node_avl * now);
void SmallTurn(node_avl *& now);  // now is the top of vertexes
void BigTurn(node_avl *& now);
int MaxHighOfChilds(node_avl * now);

node_avl * MaxChildDeleting(node_avl * now, bool dif_way = false);
// finding max child for replacement in left subtree
node_avl * MinChildDeleting(node_avl * now, bool dif_way = false);

void Turn(node_avl *& now);  // now is a parent where we call
void InsertIter(node_avl * now, int new_num);
void InsertNode(node_avl *& root, int new_num);

void DeleteIter(node_avl *& now, node_avl * deleting);
void DeleteNode(node_avl *& root, node_avl * deleting);

int h_node(node_avl * now) {
    return now == nullptr ? 0 : now->h;
}

void RecalcHigh(node_avl* now) {
    if (now == nullptr) return;
    if (now->left != nullptr) now->left->h = 1 + MaxHighOfChilds(now->left);
    if (now->right != nullptr) now->right->h = 1 + MaxHighOfChilds(now->right);
    now->h = 1 + MaxHighOfChilds(now);
}

void SmallTurn(node_avl *& now) {
    node_avl * left = now->left, * right = now->right;

    try{
        if (left->left->h >= left->right->h) {
            node_avl * c = left->right;
            left->right = now;
            now->left = c;
            now = left;
            now->left->h = 1 + MaxHighOfChilds(now->left);
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
        std::cout << "WTF HAPPENED IN SMALL TURN\n";
        exit(0);
    }

    RecalcHigh(now);
}

void BigTurn(node_avl *& now) {
    node_avl * left = now->left, * right = now->right;
    if (h_node(left) < h_node(right)) {
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

    RecalcHigh(now);
}

int MaxHighOfChilds(node_avl * now) {
    return std::max(h_node(now->left), h_node(now->right));
}

node_avl * MaxChildDeleting(node_avl * now, bool dif_way) {
    if (!dif_way && now->right != nullptr) {
        node_avl * x = MaxChildDeleting(now->right);
        if (now->right == x) {
            now->right = now->right->left;
        }
        now->h = 1 + MaxHighOfChilds(now);
        return x;
    } else if (dif_way && now->left != nullptr) {
        node_avl * x = MaxChildDeleting(now->left);
        if (now->left == x) {
            now->left = now->left->left;
        }
        now->h = 1 + MaxHighOfChilds(now);
        return x;
    }
    return now;
}

node_avl * MinChildDeleting(node_avl * now, bool dif_way) {
    if (!dif_way && now->left != nullptr) {
        node_avl * x = MinChildDeleting(now->left);
        if (now->left == x) {
            now->left = now->left->right;
        }
        now->h = 1 + MaxHighOfChilds(now);
        return x;
    } else if (dif_way && now->right != nullptr) {
        node_avl * x = MinChildDeleting(now->right);
        if (now->right == x) {
            now->right = now->right->right;
        }
        now->h = 1 + MaxHighOfChilds(now);
        return x;
    }
    return now;
}

void InsertIter(node_avl * now, int new_num) {
    if (now->num == new_num) return;
    if (new_num < now->num) {
        if (now->left != nullptr) {
            InsertIter(now->left, new_num);
        } else {
            now->left = new node_avl;
            now->left->num = new_num;
        }
    } else {
        if (now->right != nullptr) {
            InsertIter(now->right, new_num);
        } else {
            now->right = new node_avl;
            now->right->num = new_num;
        }
    }
    now->h = 1 + MaxHighOfChilds(now);
}

node_avl * FindByNum(node_avl * now, int finding) {
    if (now == nullptr) return nullptr;
    if (now->num == finding) return now;
    if (now->num < finding) return FindByNum(now->right, finding);
    else return FindByNum(now->left, finding);
}

void DeleteIter(node_avl *& now, node_avl * deleting) {
    node_avl * new_node;
    if (now == deleting) {
        if (now->left != nullptr){
            new_node = MinChildDeleting(now, true);
        } else if (now->right != nullptr){
            new_node = MaxChildDeleting(now, true);
        } else {
            delete(now);
            now = nullptr;
            return;
        }
        node_avl * left = now->left, * right = now->right;
        delete(now);
        now = new_node;
        now->left = left; now->right = right;              // при удалении корректируй сыновей
        now->h = 1 + MaxHighOfChilds(now);
        return;
    }
    if (now->num > deleting->num) {
        DeleteIter(now->left, deleting);
    } else {
        DeleteIter(now->right, deleting);
    }
    now->h = 1 + MaxHighOfChilds(now);
}

void DeleteNode(node_avl *& root, node_avl * deleting) {
    DeleteIter(root, deleting);
    Turn(root);
}

void Turn(node_avl *& now) {  // h and h+2, not more
    node_avl * left = now->left, * right = now->right;
    int bet = h_node(left) - h_node(right);

    if (bet < 0) bet = -bet;
    if (bet <= 1) {
        return;
    }

    if (h_node(left) > h_node(right)) {
        if (h_node(left->left) >= h_node(left->right)) {
            SmallTurn(now);
        } else {
            BigTurn(now);
        }
    } else {
        if (h_node(right->right) >= h_node(right->left)) {
            SmallTurn(now);
        } else {
            BigTurn(now);
        }
    }
}

void InsertNode(node_avl *& root, int new_num) {
    InsertIter(root, new_num);
    Turn(root);
}

#endif // AVL_TREE_H
