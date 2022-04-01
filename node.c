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
	pnew->freq = 0;
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
		printf( "['%c' %d]-> ", phead->symb, phead->freq);
		phead = phead->next;
	}
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



void Simmetric(NODE* root, int * level, unsigned char * code, NODE ** arr)
{										// изначально в функцию передается level = -1
	if (root)							
	{
		++(*level);						// если корень существует, то в level записывается его уровень
		if (root->left)					// если есть левый потомок
		{
			code[*level] = '0';			// При проходе налево добавляем ноль
			Simmetric(root->left, level, code, arr);	// рекуррентно (или правильно рекурсивно?) вызываем функцию
		}
		else if (root->isSymb == 1)				// если дошли до конца, то |p.s.
		{
			for (int i = 0; i < *level; ++i)	// записываем в структуру корня код 
			{
				root->code[i] = code[i];
			}
			arr[root->symb] = root;
		}		
		root->level = *level;					// и уровень (длину кода)
		if (root->isSymb == 1)
		{
			printf("['%c' f= %d l= %d c= ", root->symb, root->freq, root->level);
			for (int i = 0; i < *level; ++i)
			{
				printf("%c", root->code[i]);
			}
			printf("]\n");
		}
		if (root->right)				// аналогично для правого корня
		{
			code[*level] = '1';			// но при проходе направо добавляем единицу
			Simmetric(root->right,level, code, arr);
		}
		--(*level);			// слева и справа потомков нет ==> возращаемся к родителю, на один уровень ниже
	}
}

NODE* DeleteTree(NODE* root)
{
	if (root)
	{
		root->left = DeleteTree(root->left);
		root->right = DeleteTree(root->right);
		free(root);
	}
	return NULL;
}


