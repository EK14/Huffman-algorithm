#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include "btree.h"
#include <stdio.h>

NODE* MakeNodeFromNode( NODE* left, NODE* right)
{
    NODE* res = (NODE*)malloc(sizeof(NODE));
    if (res)
    {
        res->freq = left->freq + right->freq;
        res->isSymb = 0;
        res->symb = 0;
        res->left = left;
        res->right = right;
        res->next = NULL;
        return res;
    }
    else
    {
        return NULL;
    }  
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

void Simmetric(NODE* root, int * level, int * max, unsigned char* code, unsigned char arr[256][CODE_SIZE])
{
    if (root)
    {
        ++(*level);
        if (root->left)
        {
            code[*level] = '0';
            Simmetric(root->left, level, max, code, arr);
        }
        else if (root->isSymb == 1)
        {
            int n = root->symb;
           for (int i = 0; i < *level; ++i)
           {
               arr[n][i] = code[i];
           }
           arr[n][*level] = '\0';
           if (*level > *max)
               *max = *level;
           root->level = *level;
        }
        if (root->right)
        {
            code[*level] = '1';
            Simmetric(root->right, level, max, code, arr);
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
