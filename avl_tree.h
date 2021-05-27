#ifndef AVL_TREE_H
#define AVL_TREE_H


#include <iostream>


struct node_avl {
    node_avl * left = nullptr, * right = nullptr;
    int h = 1;
    int num;
};

int h_nodeAVL(node_avl * now);  // returning high of node
void RecalcHighAVL(node_avl * now);
void SmallTurnAVL(node_avl *& now);  // now is the top of vertexes
void BigTurnAVL(node_avl *& now);
int MaxHighOfChildsAVL(node_avl * now);

node_avl * MaxChildDeletingAVL(node_avl * now, bool dif_way = false);
// finding max child for replacement in left subtree
node_avl * MinChildDeletingAVL(node_avl * now, bool dif_way = false);
node_avl * FindByNumAVL(node_avl * now, int finding);

void TurnAVL(node_avl *& now);  // now is a parent where we call
void InsertIterAVL(node_avl * now, int new_num);
void InsertNodeAVL(node_avl *& root, int new_num);

void DeleteIterAVL(node_avl *& now, node_avl * deleting);
void DeleteNodeAVL(node_avl *& root, node_avl * deleting);


#endif // AVL_TREE_H
