#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "node.h"


int main()
{
	NODE data;
	int freq[256] = { 0 };
	FILE* fr = fopen("txt.txt", "rb");
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
	fclose(fr);
	NODE* phead = NULL;
	for (int i = 0; i < 256; ++i)
	{
		if (freq[i] > 0)
		{
			data.isSymb = 1;
			data.freq = freq[i];
			int a = i;
			data.symb = i;
			data.left = NULL;
			data.right = NULL;
			data.level = 0;
			Add2List(&phead, &data);
		}
	}
	
	PrintList(phead);

	phead = MakeTreeFromList(phead);
	printf("\n");
	int level = -1;
	Simmetric(phead, &level);
	return 0;

}
