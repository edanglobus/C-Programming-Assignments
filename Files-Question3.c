#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "q3.h"


void fileCheck(FILE* file) {
	if (file == NULL) {
		printf("Error opening file");
		exit(1);
	}
}
void memoryCheck(void* addres) {
	if (addres == NULL) {
		printf("Memory allocation failed");
		exit(1);
	}
}
char* makeFileName(char* fileName, char* add) {
	int len = (strlen(fileName) + 1 + strlen(add));
	char* name = (char*)malloc(sizeof(char) * len);
	name[0] = '\0';
	strcat(name, fileName);
	strcat(name, add);
	printf("%s \n", name);
	return name;
}
void checkFileName(char* fileName) {
	if (fileName == NULL) {
		printf("File not exist.");
		exit(1);
	}
}
long int fileSize(char* fileName) {
	checkFileName(fileName);

	FILE* file = fopen(fileName, "rb");
	fileCheck(file);
	fseek(file, 0, SEEK_END);
	long int size = ftell(file);
	fseek(file, 0, SEEK_SET);
	fclose(file);
	return size;
}

// create index file
void createIndFile(char* fileName, DATA* gradesArr, short int size) {
    char* newName = makeFileName(fileName, ".ind");

    FILE* file = fopen(newName, "wb");
    fileCheck(file);

    for (int i = 0; i < size; i++) {
        fwrite(&gradesArr[i].cursorPos, sizeof(int), 1, file);
        printf("%d ", gradesArr[i].avg);
    }
    fclose(file);
    free(newName);
}
// create data array of grade and cursor position
DATA* createDataArray(char* fileName, short int* size) {
    short int len;
    short int studentNum;

    FILE* file = fopen(fileName, "rb"); // open file to binary read
    fileCheck(file);

    //studentNum = getNum(fileName); // get the num of student from file
    fread(&studentNum, sizeof(short int), 1, file);
    DATA* dataArray = (DATA*)malloc(sizeof(DATA) * studentNum); // create array size of student num scanned type DATA struct
    memoryCheck(dataArray);

    for (int i = 0; i < studentNum; i++) {
        dataArray[i].cursorPos = ftell(file);  // insert item possition i cursor poss
        fread(&len, sizeof(short int), 1, file); // read student name Length
        fseek(file, len, SEEK_CUR); // jumping over the student name 
        fread(&(dataArray[i].avg), sizeof(int), 1, file);  // insert item possition i student avg
    }
    sortGrades(dataArray, studentNum);

    fclose(file);
    *size = studentNum;
    return dataArray;
}
// scan short int number from file
short int getNum(char* fileName) {
    checkFileName(fileName);
    short int num = 0;

    FILE* file = fopen(fileName, "rb");
    fileCheck(file);

    fread(&num, sizeof(short int), 1, file);
    fclose(file);
    return num;
}

// sort array of grade by bubble sort
void sortGrades(DATA* gradesArr, short int size) {

    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (gradesArr[j].avg < gradesArr[i].avg) {
                swapAvg(gradesArr, j, i);
            }
        }
    }
} // sort grades array
// swap two items in DATA array
void swapAvg(DATA* arr, int a, int b) {
    DATA tmp = arr[a];

    arr[a] = arr[b];
    arr[b] = tmp;
}

void printNames(char** records, int size) {
    int i;
    printf("The students names are:\n");
    for (i = 0; i < size; i++) {
        printf("%s\n", records[i]);
    }
}

void printData(DATA* data, int size) {

    for (int i = 0; i < size; i++) {
        printf("%d ", data[i].avg);
    }
    printf("\n");
}


// Q3b
char** findAverageGrade(char* database, int avgGrade, int* resSize) {
	int* indArr;
	int size;
	indArr = indexArrMaker(&size);
	char** dataArr = (char**)malloc(sizeof(char*) * size);
	memoryCheck(dataArr);

	FILE* file = fopen(database, "rb");
	fileCheck(file);
	int aa = ftell(file);

	short int nameLen = 0;
	int avg = 0;
	int count = 0;
	for (int i = 0; i < size; i++) {
		fseek(file, indArr[i], SEEK_SET);                          // move cursor to i position index arr
		fread(&nameLen, sizeof(short int), 1, file);              // read name length

		dataArr[i] = (char*)malloc(sizeof(char) * (nameLen + 1)); // name len + 1 for \0
		memoryCheck(dataArr[i]);
		fread(dataArr[i], sizeof(char), nameLen, file);     // insert name to data struct position i
		dataArr[i][nameLen] = '\0';                         // put in the end \0

		fread(&avg, sizeof(int), 1, file);                        // rescue student avg from file
		if (avg == avgGrade) {
			dataArr[count] = dataArr[i];
			count++;
		}
		else {
			free(dataArr[i]);
		}

		fseek(file, 0, SEEK_CUR);                                // return crusor to the beginnig of the file  
	}
	dataArr = (char**)realloc(dataArr, sizeof(char*) * count);
	memoryCheck(dataArr);

	fclose(file);
	free(indArr);
	*resSize = count;
	return dataArr;
}
int* indexArrMaker(int* size) {
	FILE* indexFile = fopen("Exe5Q3.bin.ind", "rb");
	fileCheck(indexFile);

	long int fileS = fileSize("Exe5Q3.bin.ind") / sizeof(int);
	int* crusorArr = (int*)malloc(sizeof(int) * fileS);
	memoryCheck(crusorArr);

	fread(crusorArr, sizeof(int), fileS, indexFile);
	fclose(indexFile);

	*size = fileS;
	return crusorArr;
}
void freeStr(char** str, int size) {
	for (int i = 0; i < size; i++) {
		free(str[i]);
	}free(str);
}


// not in use
nameNavg* dataArr(char* database, char* indFile, int* psize) {
	int* indArr;
	int size;
	indArr = indexArrMaker(indFile, &size);     // need to free indArr
	nameNavg* dataArr = (nameNavg*)malloc(sizeof(nameNavg) * size);
	memoryCheck(dataArr);

	FILE* file = fopen(database, "rb");
	fileCheck(file);
	int aa = ftell(file);
	short int nameLen = 0;
	int avg = 0;
	for (int i = 0; i < size; i++) {
		fseek(file, indArr[i], SEEK_SET);                          // move cursor to i position index arr
		fread(&nameLen, sizeof(short int), 1, file);              // read name length
		dataArr[i].name = (char*)malloc(sizeof(char) * (nameLen + 1)); // name len + 1 for \0
		memoryCheck(dataArr[i].name);
		fread(dataArr[i].name, sizeof(char), nameLen, file);     // insert name to data struct position i
		dataArr[i].name[nameLen] = '\0';                              // put in the end \0
		fread(&avg, sizeof(int), 1, file);                        // rescue student avg from file
		dataArr[i].avg = avg;                                        // insert student avg to struct
		fseek(file, 0, SEEK_CUR);                                // return crusor to the beginnig of the file  
	}

	fclose(file);
	free(indArr);
	*psize = size;
	return dataArr;
}
// tried to do it binary search but to massy, coudnt figure it out
int binarySearchGrade(char* database, char* indexFile, int avgGrade, char*** outPutStr) {
	long int indSize = fileSize(indexFile);
	long int dataSize = fileSize(database);

	char** nameStr = (char**)malloc(sizeof(char*) * (indSize / sizeof(int)));
	memoryCheck(nameStr);

	FILE* indFile = fopen(indexFile, "rb");
	fileCheck(indFile);

	FILE* dataFile = fopen(database, "rb");
	fileCheck(dataFile);



	int Lcursor = 0, Mcursor, Rcursor = indSize - sizeof(int);
	int left, mid, right;
	int avgCount = 0;
	bool found = false;

	fseek(indFile, Rcursor, SEEK_SET);
	fread(&right, sizeof(int), 1, indFile);
	fseek(indFile, Lcursor, SEEK_SET);
	fread(&left, sizeof(int), 1, indFile);

	short int nameLen;
	char* name = "";
	int avg;
	while (left != right && found == false) {
		Mcursor = (Lcursor + Rcursor) / 2;

		fseek(indFile, Mcursor, SEEK_SET);
		fread(&mid, sizeof(int), 1, indFile);
		readStudent(dataFile, mid, &nameLen, &name, &avg);

		short int LnameLen;
		char* Lname;
		int Lavg;
		readStudent(dataFile, left, &LnameLen, &Lname, &Lavg);

		short int RnameLen;
		char* Rname;
		int Ravg;
		readStudent(dataFile, right, &RnameLen, &Rname, &Ravg);

		if (avg == avgGrade) {
			nameStr[avgCount] = name;
			avgCount++;
			found = true;
		}
		else if (avg > avgGrade) {
			free(name);
			free(Rname);
			Rcursor = Mcursor;
			fseek(indFile, Rcursor, SEEK_SET);
			fread(&right, sizeof(int), 1, indFile);
		}
		else if (avg < avgGrade) {
			free(name);
			free(Lname);
			Lcursor = Mcursor;
			fseek(indFile, Lcursor, SEEK_SET);
			fread(&left, sizeof(int), 1, indFile);
		}
	}

	if (found == false) {
		return NOT_FOUND;
	}
	int tmp = avg;
	Lcursor = Rcursor = Mcursor;
	while (avg == avgGrade) {
		nameStr[avgCount] = name;
		avgCount++;
		fseek(indFile, Lcursor - sizeof(int), SEEK_SET);
		fread(&mid, sizeof(int), 1, indFile);
		readStudent(dataFile, mid, &nameLen, &name, &avg);
	} free(name);

	fseek(indFile, Rcursor + sizeof(int), SEEK_SET);
	fread(&mid, sizeof(int), 1, indFile);
	readStudent(dataFile, mid, &nameLen, &name, &avg);
	while (avg == avgGrade) {
		nameStr[avgCount] = name;
		avgCount++;
		fseek(indFile, Rcursor + sizeof(int), SEEK_SET);
		fread(&mid, sizeof(int), 1, indFile);
		readStudent(dataFile, mid, &nameLen, &name, &avg);
	}free(name);


	nameStr = (char**)realloc(nameStr, sizeof(char*) * (avgCount));
	memoryCheck(nameStr);

	fclose(indFile);
	fclose(dataFile);
	*outPutStr = nameStr;
	return avgCount;
}       // tried to do it binary
void readStudent(FILE* dataFile, int cursor, short int* nameLen, char** pname, int* avg) {
	fseek(dataFile, cursor, SEEK_SET);
	fread(*nameLen, sizeof(short int), 1, dataFile);


	fread(*nameLen, sizeof(short int), 1, dataFile);
	char* name = (char*)malloc(sizeof(char) * (*nameLen + 1));
	memoryCheck(name);
	fread(name, sizeof(char), nameLen, dataFile);
	name[*nameLen] = '\0';
	fread(*avg, sizeof(int), 1, dataFile);
	*pname = name;
}


