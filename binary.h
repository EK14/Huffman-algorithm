#ifndef HAFFMAN_BINARY_H
#define HAFFMAN_BINARY_H
#include <stdio.h>
#include <string.h>
#include "node.h"

typedef union bit2char {
    char symb;
    struct bit{
        unsigned b1 : 1;
        unsigned b2 : 1;
        unsigned b3 : 1;
        unsigned b4 : 1;
        unsigned b5 : 1;
        unsigned b6 : 1;
        unsigned b7 : 1;
        unsigned b8 : 1;
    }mbit;
}BIT2CHAR;

void MakeBinaryStr(FILE* fr,  char* str, long length, long* count, int* tail, unsigned char arr[256][CODE_SIZE], int flag, int readsnumb);

void Compression(FILE* fr, const unsigned char* str, long length, int count, int tail, int freq[256], int maxlev);

void Decompression(FILE* fw, FILE* fr, char name[]);
#endif

