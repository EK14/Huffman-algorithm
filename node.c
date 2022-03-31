#include <stdlib.h>
#include "node.h"


void Add2List(NODE** pphead, NODE* tmp)
{
	while (*pphead)
	{
		if ((*pphead)->freq > tmp->freq)
			break;
		pphead = &((*pphead)->next);
	}
	NODE* pnew = (NODE*)malloc(sizeof(NODE));
	pnew->freq = tmp->freq;
	pnew->symb = tmp->symb;
	pnew->isSymb = tmp->isSymb;
	pnew->next = *pphead;
	if (pnew->left)
		pnew->left = tmp->left;
	else
		pnew->left = NULL;
	if (pnew->right)
		pnew->right = tmp->right;
	else
		pnew->right = NULL;
	*pphead = pnew;
}

void PrintList(const NODE* phead)
{
	while (phead)
	{
		printf("['%c' %d %d]-> ", phead->symb, phead->freq, phead->isSymb);
		phead = phead->next;
	}
	printf("\n");
}

NODE* MakeNodeFromNode(const NODE* left, const NODE* right)
{
	NODE* res = (NODE*)malloc(sizeof(NODE));
	res->freq = left->freq + right->freq;
	res->isSymb = 0;
	res->symb = 0;
	res->left = left;
	res->right = right;
	res->next = 0;
	return res;
}

NODE* MakeTreeFromList(NODE* head)
{
	while (head && head->next)
	{
		NODE* left = head;
		NODE* right = head->next;
		Add2List(&(head->next->next), MakeNodeFromNode(left, right));
		head = head->next->next;
	}
	return head;
}


void Simmetric(NODE* root, int * level)
{
	if (root)
	{
		++(*level);
		Simmetric(root->left, level);
		root->level = *level;
		printf("['%c' %d %d %d]   ", root->symb, root->freq, root->isSymb, root->level);
		Simmetric(root->right, level);
		--(*level);
		
	}

}