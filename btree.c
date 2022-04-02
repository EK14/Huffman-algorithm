#include <stdlib.h>
#include "btree.h"
#include <stdio.h>

NODE* MakeNodeFromNode(const NODE* left, const NODE* right)
{
	NODE* res = (NODE*)malloc(sizeof(NODE));
	res->freq = left->freq + right->freq;
	res->isSymb = 0;
	res->symb = 0;
	res->left = left;
	res->right = right;
	res->next = NULL;
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

void Simmetric(NODE* root, int* level, unsigned char* code, NODE** arr)
{
	if (root)
	{
		++(*level);
		if (root->left)
		{
			code[*level] = '0';
			Simmetric(root->left, level, code, arr);
		}
		else if (root->isSymb == 1)
		{
			for (int i = 0; i < *level; ++i)
			{
				root->code[i] = code[i];
			}
			arr[root->symb] = root;
			root->level = *level;
		}
		if (root->isSymb == 1)
		{
			printf("['%c' f= %d l= %d c= ", root->symb, root->freq, root->level);
			for (int i = 0; i < *level; ++i)
			{
				printf("%c", root->code[i]);
			}
			printf("]\n");
		}
		if (root->right)
		{
			code[*level] = '1';
			Simmetric(root->right, level, code, arr);
		}
		--(*level);
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
