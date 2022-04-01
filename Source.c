#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#define SIZE_OF_STR 1000000
int main()
{
	//printf("Enter the file name and its extension: ");
	//char name[15];
	//scanf("%s", &name);
	NODE data;		// I don't like the name
	data.isSymb = 1;
	data.left = NULL;
	data.right = NULL;
	data.level = 0;
	int freq[256] = { 0 };
	//FILE* fr = fopen(name, "rb");
	FILE* fr = fopen("example.txt", "rb");
	if (!fr)
	{
		printf("Error opening the file for reading\n");
		return -1;
	}
	fseek(fr, 0L, SEEK_END);
	long length = ftell(fr);
	fseek(fr, 0, SEEK_SET);
	for (int i = 0; i < length; ++i)
	{
		freq[(unsigned char)fgetc(fr)]++;
	}

	NODE* phead = NULL;
	for (int i = 0; i < 256; ++i)
	{
		if (freq[i] > 0)
		{
			data.freq = freq[i];
			data.symb = i;	
			Add2List(&phead, &data);
		}
	}
	PrintList(phead);
	phead = MakeTreeFromList(phead);
	printf("\n");
	int level = -1;
	unsigned char code[CODE_SIZE] = { 0 };
	NODE * arrOfStruct[256];	// I don't like the name
	Simmetric(phead, &level, &code, &arrOfStruct);
	fseek(fr, 0, SEEK_SET);
	char str[SIZE_OF_STR] = { 0 };
	int count = 0;
	for (int i = 0; i < length; ++i)
	{
		int num = (unsigned char)fgetc(fr);
		int k = arrOfStruct[num]->level;
		for (int j = 0; j < k; ++j)
		{
			str[count] = arrOfStruct[num]->code[j];
			++count;
		}
	}
	int remainder = (count / 8 + (count % 8 ? 1 : 0)) * 8 - count;
	for (int i = 0; i < length; ++i)
	{
		int num = (unsigned char)fgetc(fr);
		int k = arrOfStruct[num]->level;
		for (int j = 0; j < k; ++j)
		{
			str[count] = arrOfStruct[num]->code[j];
			++count;
		}
	}


	fclose(fr);
	return 0;

}
