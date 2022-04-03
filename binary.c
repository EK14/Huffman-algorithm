#include "binary.h"
#include <stdlib.h>
#include <string.h>
#define BIT8 8

void MakeBinaryStr(FILE * fr,unsigned char *str, long length, int* count, int* tail, unsigned char arr[256][CODE_SIZE])
{
    fseek(fr, 0, SEEK_SET);
    str[*count] = '\0';
    int m = 0, l = 20;
    for (int i = 0; i < length; ++i)
    {
        int symb = (unsigned char)fgetc(fr);
        strncat(str, arr[symb], strlen(arr[symb]));
        if (i == length/l){
            printf("Processing... %d", m);
            printf("%\n");
            m=m+5;
            l--;
        }
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

void Compression(FILE *fr, const unsigned char * str, long length, int count, int tail)
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
        //fr = fopen(name, "wb");
        for (int i = 0; i < (count + 1) / 8; ++i)
        {
            //fprintf(fr, "%c", res[i]);
            printf("%c", res[i]);
        }
        //fclose(fr);
    }


}

