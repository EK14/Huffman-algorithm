#define _CRT_SECURE_NO_WARNINGS
#include "binary.h"
#include "btree.h"
#include <stdlib.h>
#include <string.h>
#define BIT8 8

void MakeBinaryStr(FILE * fr,unsigned char *str, long length, int* count, int* tail, unsigned char arr[256][CODE_SIZE])
{
    fseek(fr, 0, SEEK_SET);
    str[*count] = '\0';
    for (int i = 0; i < length; ++i)
    {
        //int symb = (unsigned char)fgetc(fr);
        //strncat(str, arr[symb], strlen(arr[symb]));
        strcat(str, arr[(unsigned char)fgetc(fr)]);
    }
    *count = strlen(str);
    *tail = ((*count) / 8 + ((*count) % 8 ? 1 : 0)) * 8 - (*count);
    for (int i = 0; i < *tail; ++i)
    {
        str[*count] = '0';
        ++(*count);
    }
    str[*count] = '\0';
    *count = strlen(str);
 
}

void Compression(FILE *fr, const unsigned char * str, long length, int count, int tail, int freq[256])
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
        fprintf(fr, "%d ", tail);
        for (int i = 0; i < 256; ++i)
            fprintf(fr, "%d ", freq[i]);
        for (int i = 0; i < count / 8; ++i)
        {
            fprintf(fr, "%c", res[i]);
            //printf("%c", res[i]);
        }
        fprintf(fr, "\n");
        fclose(fr);
    }
}

void Decompression(FILE* fr)
{
    long length = 0;
    int tail = 0;
    int freq[256] = { 0 };
    fscanf(fr, "%d", &tail);
    for (int i = 0; i < 256; ++i)
    {
        fscanf(fr, "%d ", &freq[i]);
        length = length + freq[i];
    }
    NODE* phead = NULL;

    CreateList(fr, &phead, freq);

    BIT2CHAR symb;
    //char* res = (char*)malloc(length * maxlev) * sizeof(char));
    while (fr)
    {
        symb.symb= fgetc(fr);
        printf("%d%d%d%d%d%d%d%d", symb.mbit.b1, symb.mbit.b2, symb.mbit.b3, symb.mbit.b4, symb.mbit.b5, symb.mbit.b6, symb.mbit.b7, symb.mbit.b8);
    }

   
   



    phead = MakeTreeFromList(phead);

}

