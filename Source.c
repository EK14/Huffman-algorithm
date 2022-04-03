#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "btree.h"
#include "binary.h"
#include <locale.h>
#define SIZE_OF_STR 1000000


int main()
{
    char* locale = setlocale(LC_ALL, "");
    printf("Enter the file name and its extension: ");
    char name[15];
    scanf("%s", &name);
    FILE* fr = fopen(name, "rb");
    if (!fr)
    {
        printf("Error opening the file for reading\n");
        return -1;
    }
    fseek(fr, 0L, SEEK_END);
    long length = ftell(fr);
    fseek(fr, 0, SEEK_SET);
    NODE* phead = NULL;
    int freq[256] = { 0 };

    CreateList(fr, &phead, &freq,  length);

    PrintList(phead);
    printf("\n");

    phead = MakeTreeFromList(phead);

    int level = -1;
    unsigned char code[CODE_SIZE] = { 0 };
    NODE * arrOfStruct[256];

    Simmetric(phead, &level, &code, &arrOfStruct);

    char str[SIZE_OF_STR] = { 0 };
    int count = 0;
    int tail = 0;

    MakeBinaryStr(fr, &str, length, &count, &tail, &arrOfStruct);

    Compression(fr, &str, length, count, tail);

    fr = fopen(name, "rb+");
    fclose(fr);
    DeleteTree(phead);
    printf("\n%d\n", count - tail);
    printf("%d\n", count);
    //printf("%s", str);
    return 0;

}
