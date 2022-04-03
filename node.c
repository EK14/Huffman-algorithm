#include "node.h"
#include <stdlib.h>
#include "node.h"

void CreateList(FILE * fr, NODE ** phead, int * freq, int length)
{
    NODE data;
    data.isSymb = 1;
    data.left = NULL;
    data.right = NULL;
    data.next = NULL;
    data.level = 0;
    for (int i = 0; i < length; ++i)
    {
        int num = (unsigned char)fgetc(fr);
        printf("%c", num);
        freq[num]++;
        //freq[(unsigned char)fgetc(fr)]++;
    }
    for (int i = 0; i < 256; ++i)
    {
        if (freq[i] > 0)
        {
            data.freq = freq[i];
            data.symb = i;
            Add2List(phead, &data);
        }
    }
}

void Add2List(NODE** pphead, const NODE*  tmp)
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
    if (tmp->left)
        pnew->left = tmp->left;
    else
        pnew->left = NULL;
    if (tmp->right)
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
