#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Q1.h"






char* makeFileName(char* fileName, char* add) {
	int len = (strlen(fileName) + 1 + strlen(add));
	char* name = (char*)malloc(sizeof(char) * len);
	name[0] = '\0';
	strcat(name, fileName);
	strcat(name, add);
	printf("%s \n", name);
	return name;
}
void newFilePrintf(char* fileName, char** strToP, int strLen) {
	char* newFile = makeFileName(fileName, ".srt.txt");

	FILE* file = fopen(newFile, "wt");
	fileCheck(file);

	sortByLetter(&strToP, strLen);
	for (int i = 0; i < strLen; i++) {
		printf("%s\n", strToP[i]);
		fprintf(file, "%s\n", strToP[i]);
	}
	fclose(file);
	freeStr(strToP, strLen);
	free(file);
}
void sortByLetter(char*** str, int strLen) {
	char** string = *str;
	int ind;
	for (int j = 0; j < strLen - 1; j++) {
		for (int i = j; i <= strLen - 2; i++) {
			if (whosSmaller(string[i], string[i + 1]) < 0) {
				swap(string, i, i + 1);
			}
		}
	}
}
int whosSmaller(char* a, char* b) {

	int i = 0;
	while (a[i] != '\0' && b[i] != '\0') {
		if (a[i] < b[i]) {
			return LEFT_SMALLER;
		}
		else if (a[i] > b[i]) {
			return RIGHT_SMALLER;
		}
		else {
			i++;
		}
	}
	if (a[i] == '\0')
		return LEFT_SMALLER;
	else
		return RIGHT_SMALLER;
}
void swap(char** str, int a, int b) {
	char* tmp = str[a];

	str[a] = str[b];
	str[b] = tmp;
}
char** readStrFileSmallLetter(char* fileName, int numOfStr) {
	if (fileName == NULL) {
		printf("File name not exist.");
	}
	else if (numOfStr == 0) {
		return NULL;
	}
	char** strOfstr = (char**)malloc(sizeof(char*) * numOfStr);
	memoryCheck(strOfstr);

	FILE* file = fopen(fileName, "rb");
	fileCheck(file);

	char currCh;
	int strLen;
	for (int i = 0; i < numOfStr; i++) {
		fread(&strLen, sizeof(int), 1, file);

		strOfstr[i] = (char*)malloc(sizeof(char) * strLen + 1);
		memoryCheck(strOfstr[i]);

		int log = 0;
		currCh = fgetc(file);
		for (int j = 0; j < strLen; j++)
		{
			if (isSmall(currCh)) {
				strOfstr[i][log] = currCh;
				log++;
			}
			//fread(&currCh, sizeof(char), 1, file);
			currCh = fgetc(file);
		}
		strOfstr[i] = (char*)realloc(strOfstr[i], sizeof(char) * (log + 1));
		memoryCheck(strOfstr[i]);
		strOfstr[i][log] = '\0';
		fseek(file, -1, SEEK_CUR);
	}
	fclose(file);
	return strOfstr;
}
void memoryCheck(void* addres) {
	if (addres == NULL) {
		printf("Memory allocation failed");
		exit(1);
	}
}
void fileCheck(FILE* file) {
	if (file == NULL) {
		printf("Error opening file");
		exit(1);
	}
}
bool isNum(char ch) {
	if (ch <= 'Z' && ch >= 'a')
		return true;
	else
		return false;
}
bool isSmall(char ch) {
	if (ch <= 'z' && ch >= 'a')
		return true;
	else
		return false;
}
void freeStr(char** str, int size) {
	for (int i = 0; i < size; i++) {
		free(str[i]);
	}
	free(str);
}