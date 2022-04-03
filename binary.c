#include "binary.h"
#include <stdlib.h>
#define BIT8 8

void MakeBinaryStr(FILE * fr,unsigned char *str, long length, int* count, int* tail, NODE** arr)
{
    fseek(fr, 0, SEEK_SET);
    for (int i = 0; i < length; ++i)
    {
        int num = (unsigned char)fgetc(fr);
        for (int j = 0; j < arr[num]->level; ++j)
        {
            str[*count] = arr[num]->code[j];
            ++(*count);
        }
    }
    *tail = ((*count) / 8 + ((*count) % 8 ? 1 : 0)) * 8 - (*count);
    for (int i = 0; i < *tail; ++i)
    {
        str[*count] = '0';
        ++(*count);
    }
    fclose(fr);
}

void Compression(FILE *fr, const unsigned char * str, long length, int count, int tail)
{
    BIT2CHAR symb;
    char* res = (char*)malloc((count / 8) * sizeof(char));
    for (int i = 0; i < count / 8; ++i)
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
    //fr = fopen(name, "wb");
    for (int i = 0; i < count / 8; ++i)
    {
        //fprintf(fr, "%c", res[i]);
        printf("%c", res[i]);
    }
    //fclose(fr);



}

