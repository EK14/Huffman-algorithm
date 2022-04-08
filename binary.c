#define _CRT_SECURE_NO_WARNINGS
#include "binary.h"
#include "btree.h"
#include <stdlib.h>
#include <string.h>
#define BIT8 8

void MakeBinaryStr(FILE * fr,char *str, long length, long* count, int* tail, unsigned char arr[256][CODE_SIZE])
{
    fseek(fr, 0, SEEK_SET);
    str[*count] = '\0';
    char * pt = str;
    for (int i = 0; i < length; ++i)
    {
        //strcat(str, arr[(unsigned char)fgetc(fr)]);
        int symb = (unsigned char)fgetc(fr);
        memcpy(pt, arr[symb], strlen(arr[symb]));
        pt +=  strlen(arr[symb]);
    }
    long len = strlen(str);
    *count = len;
    *tail = ((*count) / 8 + ((*count) % 8 ? 1 : 0)) * 8 - (*count);
    for (int i = 0; i < *tail; ++i)
    {
        str[*count] = '0';
        ++(*count);
    }
    str[*count] = '\0';
    *count = len;
}

void Compression(FILE *fr, const unsigned char * str, long length, int count, int tail, int freq[256], int maxlev)
{
    BIT2CHAR symb;
    char* res = (char*)malloc(((count + 1)/ 8) * sizeof(char));
    if (res)
    {
        for (int i = 0; i < (count + 1) / 8; ++i)
        {
            symb.mbit.b1 = (int)str[i * BIT8 + 0];
            symb.mbit.b2 = (int)str[i * BIT8 + 1];
            symb.mbit.b3 = (int)str[i * BIT8 + 2];
            symb.mbit.b4 = (int)str[i * BIT8 + 3];
            symb.mbit.b5 = (int)str[i * BIT8 + 4];
            symb.mbit.b6 = (int)str[i * BIT8 + 5];
            symb.mbit.b7 = (int)str[i * BIT8 + 6];
            symb.mbit.b8 = (int)str[i * BIT8 + 7];
            res[i] = symb.symb;
        }

        fprintf(fr, "%d %d %d ", maxlev, tail, (count + 1) / 8);

        for (int i = 0; i < 256; ++i)
            fprintf(fr, "%d ", freq[i]);
        for (int i = 0; i < count / 8; ++i)
        {
            fprintf(fr, "%c", res[i]);
        }
        fclose(fr);
    }
}

void Decompression(FILE* fr, char name[])
{
    fr = fopen(name, "rb");
    long length = 0;
    int tail, maxlev, lenOfStr;
    int freq[256] = { 0 };
    fscanf(fr, "%d ", &maxlev);
    fscanf(fr, "%d ", &tail);
    fscanf(fr, "%d ", &lenOfStr);
    for (int i = 0; i < 256; ++i)
    {
        fscanf(fr, "%d ", &freq[i]);
        length = length + freq[i];
    }
    BIT2CHAR symb;
    char* str = (char*)malloc((length * maxlev) * sizeof(char));

    long count = -1;

    for (int i =0; i < lenOfStr; ++i)
    {
        symb.symb= fgetc(fr);
        if (symb.mbit.b1 == 0 && count < lenOfStr*BIT8-tail-1)
            str[++count] = '0';
        else if (count < lenOfStr * BIT8 - tail - 1)
            str[++count] = '1';
        if (symb.mbit.b2 == 0 && count < lenOfStr * BIT8 - tail - 1)
            str[++count] = '0';
        else if (count < lenOfStr * BIT8 - tail - 1)
            str[++count] = '1';
        if (symb.mbit.b3 == 0 && count < lenOfStr * BIT8 - tail - 1)
            str[++count] = '0';
        else if (count < lenOfStr * BIT8 - tail - 1)
            str[++count] = '1';
        if (symb.mbit.b4 == 0 && count < lenOfStr * BIT8 - tail - 1)
            str[++count] = '0';
        else if (count < lenOfStr * BIT8 - tail - 1)
            str[++count] = '1';
        if (symb.mbit.b5 == 0 && count < lenOfStr * BIT8 - tail - 1)
            str[++count] = '0';
        else if (count < lenOfStr * BIT8 - tail - 1)
            str[++count] = '1';
        if (symb.mbit.b6 == 0 && count < lenOfStr * BIT8 - tail - 1)
            str[++count] = '0';
        else if (count < lenOfStr * BIT8 - tail - 1)
            str[++count] = '1';
        if (symb.mbit.b7 == 0 && count < lenOfStr * BIT8 - tail - 1)
            str[++count] = '0';
        else if (count < lenOfStr * BIT8 - tail - 1)
            str[++count] = '1';
        if (symb.mbit.b8 == 0 && count < lenOfStr * BIT8 - tail - 1)
            str[++count] = '0';
        else if (count < lenOfStr * BIT8 - tail - 1)
            str[++count] = '1';
    }
    str[++count] = '\0';
    fclose(fr);
    NODE* phead = NULL;
    CreateList(fr, &phead, freq);
    phead = MakeTreeFromList(phead);

    lenOfStr = count;
    count = -1;
    NODE* head = phead;
    fr = fopen(name, "wb");
    while (count <= lenOfStr)
    {
        if (head)
        {
            if (head->isSymb == 1)
            {
                fprintf(fr, "%c", head->symb);
                head = phead;
            }
            else
            {
                if (str[++count] == '0')
                {
                    head = head->left;
                }
                else
                {
                    head = head->right;
                }
            }
        }

    }

    fclose(fr);
    free(str);
    DeleteTree(phead);
}


