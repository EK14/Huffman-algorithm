#define CODE_SIZE 8
#ifndef NODE_H
#define NODE_H 

typedef struct node{
	unsigned char symb;
	unsigned char isSymb;
	unsigned int freq;
	unsigned char code[CODE_SIZE];
	int level;
	struct node *left, *right, *next;
}NODE;

void Add2List(NODE** pphead, NODE* tmp);

void PrintList(const NODE* phead);
//NODE* Add2Tree(NODE* root, NODE* tmp);

#endif
