#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include <iostream>

struct node_splay{
    node_splay * left = nullptr, * right = nullptr;
    node_splay * parent = nullptr; // null for root
    int num;
};

void ZigSplay(node_splay *& now, node_splay *& root);
void ZigZigSplay(node_splay *& now, node_splay *& root);
void ZigZagSplay(node_splay * now, node_splay *& root);
void Splay(node_splay * now, node_splay *& root);
node_splay * InsertIterSplay(node_splay * now, int num);
void InsertSplay(node_splay *&root, int num);
node_splay* FindNodeSplay(node_splay * now, int num);
node_splay* FindMaxNodeSplay(node_splay *now);
node_splay * FindMinNodeSplay(node_splay *now);
void DeleteSplay(node_splay*& root, int num);

#endif // SPLAY_TREE_H
