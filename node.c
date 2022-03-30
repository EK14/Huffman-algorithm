#include <stdlib.h>
#include "node.h"


void Add2List(NODE** pphead, NODE* tmp)
{
	while (*pphead)
	{
		if ((*pphead)->freq >= tmp->freq)
			break;
		pphead = &((*pphead)->next);
	}
	NODE* pnew = (NODE*)malloc(sizeof(NODE));
	pnew->freq = tmp->freq;
	pnew->symb = tmp->symb;
	pnew->isSymb = tmp->isSymb;
	pnew->next = *pphead;
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


//NODE* Add2Tree(NODE* root, NODE* tmp)
//{
//	if (root == NULL)
//	{
//		root = (NODE*)malloc(sizeof(NODE));
//		root->freq = value;
//		root->left = root->right = NULL;
//	}
//	else
//	{
//		if (value < root->freq)
//		{
//			root->left = Add2Tree(root->left, value);
//		}
//		else 
//		{
//			root->right = Add2Tree(root->right, value);
//		}
//	}
//	return root;
//}

//void Simmetric(const NODE* root)
//{
//	if (root)
//	{
//		Simmetric(root->left);
//		printf("%5d", root->freq);
//		Simmetric(root->right);
//	}
//}