#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "btree.h"
#include "binary.h"
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "");
    printf("Enter the file name and its extension: ");
    char name[15];
    scanf("%s", name);
    name[strlen(name)] = '\0';
    FILE* fr = fopen(name, "rb");
    if (!fr)
    {
        printf("Error opening the file for reading\n");
        return -1;
    }
    fseek(fr, 0L, SEEK_END);
    long length = ftell(fr);
    fseek(fr, 0, SEEK_SET);
    int freq[256] = { 0 };
    for (int i = 0; i < length; ++i)
    {
        freq[(unsigned char)fgetc(fr)]++;
    }
    NODE* phead = NULL;

    CreateList(fr, &phead, freq);

    //PrintList(phead);
    //printf("\n");

    phead = MakeTreeFromList(phead);

    int level = -1;
    int maxlev = 0;
    unsigned char code[CODE_SIZE] = { 0 };
    unsigned char arrofCode[256][CODE_SIZE];

    Simmetric(phead, &level, &maxlev, &code, arrofCode);

    char* str = (unsigned char*)malloc((length * maxlev) * sizeof(unsigned char));
    int count = 0;
    int tail = 0;

    MakeBinaryStr(fr, str, length, &count, &tail, arrofCode);

    fr = fopen(name, "wb");

    Compression(fr, str, length, count, tail, freq, maxlev);
   
    free(str);
    DeleteTree(phead);

    Decompression(fr, name);   
    return 0;

}
