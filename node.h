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

typedef union bit2char {
	char symb;
	struct bit {
		unsigned b1 : 1;
		unsigned b2 : 1;
		unsigned b3 : 1;
		unsigned b4 : 1;
		unsigned b5 : 1;
		unsigned b6 : 1;
		unsigned b7 : 1;
		unsigned b8 : 1;
	}mbit;
}BIT2CHAR;


void Add2List(NODE** pphead, NODE* tmp);

void PrintList(const NODE* phead);

NODE* MakeTreeFromList(NODE* head);

void Simmetric(NODE* root, int* level, unsigned char* code, NODE** arr);

NODE* DeleteTree(NODE* root);

#endif
