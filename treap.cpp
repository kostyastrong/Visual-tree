#include "treap.h"

std::vector<node_treap*> SplitTreap(node_treap *A, int num) {
    if (A == nullptr) return {nullptr, nullptr, nullptr};
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
    if (A == nullptr) return B;
    if (B == nullptr) return A;

    if (A->y > B->y) {
        A->right = MergeTreap(A->right, B);
        return A;
    } else {
        B->left = MergeTreap(A, B->left);
        return B;
    }
}

node_treap * InsertTreap(node_treap *& A, node_treap * num) {
    if (A == nullptr) { // root
        A = num;
        return A;
    }
    if (num->y > A->y) {
        std::vector<node_treap*> p = SplitTreap(A, num->x);
        num->left = p[0];
        num->right = p[2];
        return num;
    } else {
        if (num->x > A->x) {
            A->right = InsertTreap(A->right, num);
        } else if (num->x < A->x){
            A->left = InsertTreap(A->left, num);
        }
        return A;
    }
}
