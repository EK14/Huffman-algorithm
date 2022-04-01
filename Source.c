#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "node.h"
#include <conio.h>
#include <locale.h>
#define SIZE_OF_STR 1000000
#define BIT8 8


// Заголовочный можно поделить на Сптсок, Дерево, Объединение
int main()
{

	setlocale(LC_ALL, "Rus");
	printf("Enter the file name and its extension: ");
	char name[15];
	scanf("%s", &name);
	FILE* fr = fopen(name, "rb");
	if (!fr)
	{
		printf("Error opening the file for reading\n");
		return -1;
	}
	fseek(fr, 0L, SEEK_END);
	long length = ftell(fr);
	fseek(fr, 0, SEEK_SET);
	// Можно в отдельную функцию: например, CreateList_____ 
	NODE data;		// I don't like the name			//|
	data.isSymb = 1;									//|
	data.left = NULL;									//|
	data.right = NULL;									//|
	data.level = 0;										//|
	int freq[256] = { 0 };								//|
	for (int i = 0; i < length; ++i)					//|
	{													//|
		freq[(unsigned char)fgetc(fr)]++;				//|		Используются:
	}													//|		- fr
	NODE* phead = NULL;									//|		- phead
	for (int i = 0; i < 256; ++i)						//|		- freq
	{													//|		- length
		if (freq[i] > 0)								//|
		{												//|
			data.freq = freq[i];						//|
			data.symb = i;								//|
			Add2List(&phead, &data);					//|
		}												//|
	}													//|
												//---------
	PrintList(phead);
	phead = MakeTreeFromList(phead);
	int level = -1;
	unsigned char code[CODE_SIZE] = { 0 };
	NODE * arrOfStruct[256];	// I don't like the name
	Simmetric(phead, &level, &code, &arrOfStruct);
	char str[SIZE_OF_STR] = { 0 };
	int count = 0;
	// Можно в отдельную функцию: например, MakeBinaryStr _____________
	fseek(fr, 0, SEEK_SET);											//|
	for (int i = 0; i < length; ++i)								//|			
	{																//|
		int num = (unsigned char)fgetc(fr);							//|
		for (int j = 0; j < (*arrOfStruct[num]).level; ++j)			//|
		{															//|
			str[count] = arrOfStruct[num]->code[j];					//|		Используются:
			++count;												//|		- fr
		}															//|		- str
	}																//|		- length
	int remainder = (count / 8 + (count % 8 ? 1 : 0)) * 8 - count;	//|		- count
	for (int i = 0; i < remainder; ++i)								//|		- remainder (высчитывается через count)
	{																//|
			str[count] = '0';										//|
			++count;												//|
	}																//|
	fclose(fr);														//|
															//---------
	
	// Можно в отдельную функцию: например, Compression   _____________
	BIT2CHAR symb;												    //|
	char * res = (char*)malloc((count / 8) * sizeof(char));			//|
	for (int i = 0; i < count / 8; ++i)								//|
	{																//|
		symb.mbit.b1 = str[i * BIT8 + 0];							//|
		symb.mbit.b2 = str[i * BIT8 + 1];							//|
		symb.mbit.b3 = str[i * BIT8 + 2];							//|
		symb.mbit.b4 = str[i * BIT8 + 3];							//|		Используются:
		symb.mbit.b5 = str[i * BIT8 + 4];							//|		- fr
		symb.mbit.b6 = str[i * BIT8 + 5];							//|		- str
		symb.mbit.b7 = str[i * BIT8 + 6];							//|		- res
		symb.mbit.b8 = str[i * BIT8 + 7];							//|		- count
		res[i] = symb.symb;											//|
	}																//|
	fr = fopen(name, "wb");											//|
	for (int i = 0; i < count / 8; ++i)								//|
	{																//|
		fprintf(fr, "%c", res[i]);									//|
	}																//|
	fclose(fr);														//|
															//---------
	

		//Осталось : 
		//Заменяем каждый символ на последовательность бит
		//Заменяем каждую последовательность бит на символ, который эта последовательность кодирует
		//Записываем результат в файл распаковки
		//Исходный файл и распакованный файл должны совпадать
	fr = fopen(name, "rb+");
	fclose(fr);
	DeleteTree(phead);
	printf("%s", str);
	return 0;

}
