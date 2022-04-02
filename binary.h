#include <stdio.h>
#include "node.h"
#ifndef BINARY_H
#define BINARY_H

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

void MakeBinaryStr(FILE* fr, char* str, int length, int* count, int* tail, NODE* arr);

void Compression(FILE* fr, char* str, int length, int count, int tail);

#endif