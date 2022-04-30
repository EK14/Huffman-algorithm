#define _CRT_SECURE_NO_WARNINGS
#include "binary.h"
#include "btree.h"
#include <stdlib.h>
#include <math.h>
#define BIT8 8
#define PART_TO_READ 32
#define SIZE 10000

void MakeBinaryStr(FILE * fr,char *str, long length, long* count, int* tail, unsigned char arr[256][CODE_SIZE], int flag, int readsnumb)
{
    char * pt = str;
    int i = 0;
    while((i < length) && !feof(fr))
    {
        //strcat(str, arr[(unsigned char)fgetc(fr)]);
        int symb = (unsigned char)fgetc(fr);
        memcpy(pt, arr[symb], strlen(arr[symb]));
        pt +=  strlen(arr[symb]);
        *count += strlen(arr[symb]);
        i++;
    }
    *tail = ((*count) / 8 + ((*count) % 8 ? 1 : 0)) * 8 - (*count);
    //for (int i = 0; i < *tail; ++i)
    //{
    //    str[*count] = '0';
    //    ++(*count);
    //}
    if(flag == readsnumb - 1) {
        for (int i = 0; i < *tail; ++i) {
            str[(*count)++] = '0';
        }
    }
    str[*count] = '\0';
}

void Compression(FILE *fw, const unsigned char * str, long length, int count, int tail, int freq[256], int maxlev)
{
    BIT2CHAR symb;
    char* res = (char*)malloc(((count + 1)/ 8) * sizeof(char));
    if (res)
    {
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
        for (int i = 0; i < count / 8; ++i)
        {
            fprintf(fw, "%c", res[i]);
        }
    }
}

void Decompression(FILE* fw, FILE* fr, char name[])
{
    int ind = 0;
    char transfer[256] = {'\0'}, byte[9] = {'\0'};
    fr = fopen(name, "rb");
    fw = fopen("temp.txt", "ab");
    fseek(fr, 0L, SEEK_END);
    long length = ftell(fr);
    fseek(fr, 0, SEEK_SET);
    long len = 0;
    int tail, maxlev, remaind = 0;
    int freq[256] = { 0 };
    fscanf(fr, "%d ", &maxlev);
    fscanf(fr, "%d ", &tail);
    for (int i = 0; i < 256; ++i)
    {
        fscanf(fr, "%d ", &freq[i]);
    }
    NODE* phead = NULL;
    CreateList(fr, &phead, freq);
    phead = MakeTreeFromList(phead);

    BIT2CHAR symb;
    int readsnumb = (int)(length / PART_TO_READ * pow(2, -20)) + 1;

    for(int i=0; i < readsnumb + 1; ++i) {
        len = 0;
        char *str = (char *) malloc((PART_TO_READ * pow(2, 20)* maxlev) * sizeof(char));
        char * ptr = str;
        if(strlen(transfer) != 0){
                memcpy(str, transfer, remaind);
                len += remaind;
                ptr += remaind;
        }
        long count = -1, loop = PART_TO_READ*pow(2,20);
        int j = 0;
        symb.symb = fgetc(fr);
        while (j < loop && !feof(fr)) {
            byte[0] = symb.mbit.b1 + '0';
            byte[1] = symb.mbit.b2 + '0';
            byte[2] = symb.mbit.b3 + '0';
            byte[3] = symb.mbit.b4 + '0';
            byte[4] = symb.mbit.b5 + '0';
            byte[5] = symb.mbit.b6 + '0';
            byte[6] = symb.mbit.b7 + '0';
            byte[7] = symb.mbit.b8 + '0';
            memcpy(ptr, byte, 8);
            ptr += 8;
            j++;
            len += 8;
            symb.symb = fgetc(fr);
        }
        if(feof(fr) && len > 0){
            for(int k = 0; k < tail; k++){
                str[len - k - 1] = '\0';
            }
            len -= tail;
        }
        ind = len;
        remaind = len;
        if(ind > 256 && i != readsnumb)
            ind = ind - 256;
        count = 0;
        NODE *head = phead;
        while (len != 0) {
            if (head) {
                if (head->isSymb) {
                    fprintf(fw, "%c", head->symb);
                    head = phead;
                    if(phead->isSymb)
                        count++;
                    if(count  >= ind) {
                        remaind = len - count;
                        break;
                    }
                } else {
                    if (str[count++] == '0') {
                        head = head->left;
                    } else {
                        head = head->right;
                    }
                }
            }
        }
        char * ptr2 = str + len - remaind;
        if(ind > 256){
            memcpy(transfer, ptr2, remaind);
        }
        free(str);
    }
    fclose(fr);
    fclose(fw);
    remove(name);
    fr = fopen("temp.txt", "rb");
    fw = fopen(name, "wb");
    int num;
    char buf[SIZE] = {'\0'};
    while(num = fread(buf, sizeof(char), SIZE, fr)) {
        fwrite(buf, sizeof(char), num, fw);
    }
    fclose(fr);
    fclose(fw);
    remove("temp.txt");
    DeleteTree(phead);
}


