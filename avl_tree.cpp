#include "avl_tree.h"

int h_nodeAVL(node_avl * now) {
    return now == nullptr ? 0 : now->h;
}

void RecalcHighAVL(node_avl* now) {
    if (now == nullptr) return;
    if (now->left != nullptr) now->left->h = 1 + MaxHighOfChildsAVL(now->left);
    if (now->right != nullptr) now->right->h = 1 + MaxHighOfChildsAVL(now->right);
    now->h = 1 + MaxHighOfChildsAVL(now);
}

void SmallTurnAVL(node_avl *& now) {
    node_avl * left = now->left, * right = now->right;

    if (h_nodeAVL(left) < h_nodeAVL(right)) {  // delta is more than 2
        node_avl * c = right->left;
        right->left = now;
        now->right = c;
        now = right;
    } else {
        node_avl * c = left->right;
        left->right = now;
        now->left = c;
        now = left;
        now->left->h = 1 + MaxHighOfChildsAVL(now->left);
    }
    RecalcHighAVL(now);
}


void BigTurnAVL(node_avl *& now) {
    node_avl * left = now->left, * right = now->right;
    if (h_nodeAVL(left) < h_nodeAVL(right)) {
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

    RecalcHighAVL(now);
}

int MaxHighOfChildsAVL(node_avl * now) {
    return std::max(h_nodeAVL(now->left), h_nodeAVL(now->right));
}

node_avl * MaxChildDeletingAVL(node_avl * now, bool dif_way) {
    if (!dif_way && now->right != nullptr) {
        node_avl * x = MaxChildDeletingAVL(now->right);
        if (now->right == x) {
            now->right = now->right->left;
        }
        now->h = 1 + MaxHighOfChildsAVL(now);
        return x;
    } else if (dif_way && now->left != nullptr) {
        node_avl * x = MaxChildDeletingAVL(now->left);
        if (now->left == x) {
            now->left = now->left->left;
        }
        now->h = 1 + MaxHighOfChildsAVL(now);
        return x;
    }
    return now;
}

node_avl * MinChildDeletingAVL(node_avl * now, bool dif_way) {
    if (!dif_way && now->left != nullptr) {
        node_avl * x = MinChildDeletingAVL(now->left);
        if (now->left == x) {
            now->left = now->left->right;
        }
        now->h = 1 + MaxHighOfChildsAVL(now);
        return x;
    } else if (dif_way && now->right != nullptr) {
        node_avl * x = MinChildDeletingAVL(now->right);
        if (now->right == x) {
            now->right = now->right->right;
        }
        now->h = 1 + MaxHighOfChildsAVL(now);
        return x;
    }
    return now;
}

void InsertIterAVL(node_avl *& now, int new_num) {
    if (now == nullptr) { // root
        now = new node_avl;
        now->num = new_num;
        return;
    }
    if (now->num == new_num) return;
    if (new_num < now->num) {
        if (now->left != nullptr) {
            InsertIterAVL(now->left, new_num);
            TurnAVL(now);
        } else {
            now->left = new node_avl;
            now->left->num = new_num;
        }
    } else {
        if (now->right != nullptr) {
            InsertIterAVL(now->right, new_num);
            TurnAVL(now);
        } else {
            now->right = new node_avl;
            now->right->num = new_num;
        }
    }
    now->h = 1 + MaxHighOfChildsAVL(now);
}

node_avl * FindByNumAVL(node_avl * now, int finding) {
    if (now == nullptr) return nullptr;
    if (now->num == finding) return now;
    if (now->num < finding) return FindByNumAVL(now->right, finding);
    else return FindByNumAVL(now->left, finding);
}

void DeleteIterAVL(node_avl *& now, node_avl * deleting) {
    node_avl * new_node;
    if (now == deleting) {
        if (now->left != nullptr){
            new_node = MinChildDeletingAVL(now, true);
        } else if (now->right != nullptr){
            new_node = MaxChildDeletingAVL(now, true);
        } else {
            delete(now);
            now = nullptr;
            return;
        }
        node_avl * left = now->left, * right = now->right;
        delete(now);
        now = new_node;
        now->left = left; now->right = right;              // при удалении корректируй сыновей
        now->h = 1 + MaxHighOfChildsAVL(now);
        return;
    }
    if (now->num > deleting->num) {
        DeleteIterAVL(now->left, deleting);
    } else {
        DeleteIterAVL(now->right, deleting);
    }
    now->h = 1 + MaxHighOfChildsAVL(now);
}

void DeleteNodeAVL(node_avl *& root, int num) {
    node_avl * deleting = FindByNumAVL(root, num);
    if (deleting == nullptr) return;
    DeleteIterAVL(root, deleting);
    TurnAVL(root);
}

void TurnAVL(node_avl *& now) {  // h and h+2, not more
    node_avl * left = now->left, * right = now->right;
    int bet = h_nodeAVL(left) - h_nodeAVL(right);

    if (bet < 0) bet = -bet;
    if (bet <= 1) {
        return;
    }

    if (h_nodeAVL(left) > h_nodeAVL(right)) {
        if (h_nodeAVL(left->left) >= h_nodeAVL(left->right)) {
            SmallTurnAVL(now);
        } else {
            BigTurnAVL(now);
        }
    } else {
        if (h_nodeAVL(right->right) >= h_nodeAVL(right->left)) {
            SmallTurnAVL(now);
        } else {
            BigTurnAVL(now);
        }
    }
}

void InsertNodeAVL(node_avl *& root, int new_num) {
    InsertIterAVL(root, new_num);
    TurnAVL(root);
}
