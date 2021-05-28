#ifndef TREAP_H
#define TREAP_H

#include<vector>
#include<random>

struct node_treap{
    int x;
    double y = static_cast<double>(rand()) / RAND_MAX;
    node_treap * left = nullptr, * right = nullptr;
};

std::vector<node_treap*> SplitTreap(node_treap * A, int num);
node_treap* MergeTreap(node_treap *& A, node_treap * B);
node_treap * InsertTreap(node_treap *& A, node_treap * num);
node_treap * DeleteTreap(node_treap *& A, int num);

#endif // TREAP_H
