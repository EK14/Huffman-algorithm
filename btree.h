#ifndef HAFFMAN_BTREE_H
#define HAFFMAN_BTREE_H
#include "node.h"

NODE* MakeNodeFromNode(NODE* left, NODE* right);

NODE* MakeTreeFromList(NODE* head);

void Simmetric(NODE* root, int* level, int * max, unsigned char* code, unsigned char arr[256][CODE_SIZE]);

NODE* DeleteTree(NODE* root);

#endif

