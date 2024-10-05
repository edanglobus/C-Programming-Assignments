#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "q3.h"











void main(int argc, char** argv) {
    short int size;
    DATA* array = createDataArray(argv[1], &size);
    printData(array, 5);
    createIndFile(argv[1], array, size);
    free(array);

	char** string;
	int* count;
	string = findAverageGrade(argv[1], 100, &count);

	printf("\n\nnumber of student with that avg: %d\n", count);
	printf("\nStudent name list: ");
	for (int i = 0; i < count; i++) {
		printf(" %s", string[i]);
	}
	freeStr(string, count);
}