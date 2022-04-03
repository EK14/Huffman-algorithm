#ifndef HAFFMAN_NODE_H
#define HAFFMAN_NODE_H
#include <stdio.h>
#define CODE_SIZE 100

typedef struct node{
    unsigned char symb;
    unsigned char isSymb;
    unsigned int freq;
    //unsigned char code[CODE_SIZE];
    int level;
    struct node *left, *right, *next;
}NODE;

void CreateList(FILE* fr, NODE ** phead, int * freq, long length);

void Add2List(NODE** pphead, const NODE*  tmp);

void PrintList(const NODE* phead);


#endif //HAFFMAN_NODE_H
