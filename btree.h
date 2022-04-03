#ifndef HAFFMAN_BTREE_H
#define HAFFMAN_BTREE_H
#include "node.h"

NODE* MakeTreeFromList(NODE* head);

void Simmetric(NODE* root, int* level, unsigned char* code, NODE** arr);

NODE* DeleteTree(NODE* root);

#endif //HAFFMAN_BTREE_H
