#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include "btree.h"
#include "binary.h"
#include <locale.h>
#include <math.h>
#define SIZE 1000
#define PART_TO_READ 32

int main()
{
    long count = 0;
    int tail = 0, ind = 0;
    setlocale(LC_ALL, "");
    printf("Enter the file name and its extension: ");
    char name[15], transfer[8] = {'\0'};
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
    int readsnumb = (int)(length / PART_TO_READ * pow(2,-20)) + 1;
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
    int remaind = 0;
    unsigned char code[CODE_SIZE] = { 0 };
    unsigned char arrofCode[256][CODE_SIZE] = {'\0'};

    Simmetric(phead, &level, &maxlev, &code, arrofCode);
    FILE * fw = fopen("temp.txt", "wb");
    fseek(fr, 0, SEEK_SET);
    for(int i=0; i < readsnumb; ++i) {
        count = 0;
        char *str = (char *) malloc((PART_TO_READ * pow(2, 20) * maxlev) * sizeof(char));
        char *ptr = str;
        if(strlen(transfer) != 0) {
            memcpy(str, transfer, remaind);
            ptr += remaind;
            count += remaind;
        }
        length = PART_TO_READ * pow(2,20);
        MakeBinaryStr(fr, ptr, length, &count, &tail, arrofCode, i, readsnumb);

        remaind = count % 8;
        ind = count - remaind;

        Compression(fw, str, length, count, tail, freq, maxlev);

        char * ptr2 = str + ind;
        if(ind > 256){
            memcpy(transfer, ptr2, remaind);
        }
        free(str);
    }
    fclose(fr);
    fclose(fw);
    fr = fopen("temp.txt", "rb");
    fw = fopen(name, "wb");
    fprintf(fw, "%d %d ", maxlev, tail);

    for (int i = 0; i < 256; ++i)
        fprintf(fw, "%d ", freq[i]);
    int num;
    char buf[SIZE];
    while(num = fread(buf, sizeof(char), SIZE, fr)){
        fwrite(buf, sizeof(char), num, fw);
    }
    fclose(fr);
    fclose(fw);
    remove("temp.txt");
    DeleteTree(phead);

    char choice[4];
    printf("Do you want to decompress file? Answer yes or no\n");
    scanf("%s", choice);
    if(!strcmp(choice, "yes"))
        Decompression(fw, fr, name);
    return 0;
}
