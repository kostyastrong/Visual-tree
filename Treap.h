//
// Created by maincpp on 26.05.2021.
//

#ifndef CLIONPROJECTS_TREAP_H
#define CLIONPROJECTS_TREAP_H

struct node_treap{
    int x;
    double y = static_cast<double>(rand()) / RAND_MAX;
    node_treap * left = nullptr, * right = nullptr;
};

std::vector<node_treap*> SplitTreap(node_treap *A, int num) {
    if (!A) return {nullptr, nullptr, nullptr};
    if (A->x == num) return {A->left, A, A->right};
    if (A->x < num) {
        std::vector<node_treap*> p = SplitTreap(A->right, num);
        A->right = p[0];
        return {A, p[1], p[2]};
    } else {
        std::vector<node_treap*> p = SplitTreap(A->left, num);
        A->left = p[2];
        return {p[0], p[1], A};
    }
}

node_treap* MergeTreap(node_treap * A, node_treap * B) {  // A < B
    if (!A) return B;
    if (!B) return A;

    if (A->y > B->y) {
        A->right = MergeTreap(A->right, B);
        return A;
    } else {
        B->left = MergeTreap(A, B->left);
        return B;
    }
}

node_treap * InsertTreap(node_treap * A, node_treap * num) {
    if (num->y > A->y) {
        std::vector<node_treap*> p = SplitTreap(A, num->x);
        num->left = p[0];
        num->right = p[2];
        return num;
    } else {
        if (num->x > A->x) {
            A->right = InsertTreap(A->right, num);
        } else {
            A->left = InsertTreap(A->left, num);
        }
        return A;
    }
}

#endif //CLIONPROJECTS_TREAP_H
