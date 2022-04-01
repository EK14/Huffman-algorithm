#define CODE_SIZE 16 // How much should the number be?
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

NODE* MakeTreeFromList(NODE* head);

void Simmetric(NODE* root, int* level, unsigned char* code, NODE** arr);


#endif
