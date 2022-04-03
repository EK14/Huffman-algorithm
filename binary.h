#define _CRT_SECURE_NO_WARNINGS
#ifndef HAFFMAN_BINARY_H
#define HAFFMAN_BINARY_H
#include <stdio.h>
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

void MakeBinaryStr(FILE* fr, unsigned char* str, long length, int* count, int* tail, unsigned char arr[256][CODE_SIZE]);

void Compression(FILE* fr,const unsigned char* str, long length, int count, int tail);

#endif

