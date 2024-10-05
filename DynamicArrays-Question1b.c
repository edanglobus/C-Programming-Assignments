#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define SIZE 100
void swapPointers(int** p1, int** p2) {
	int* tmp;

	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}
void pointerSort(int* arr, unsigned int size, int ascend_flag , int **pointers) {
	int x = 0, j = 0, i = 0;
	int** pointerArr = (int**)malloc(size * sizeof(int*));
	if (pointerArr == NULL) {
		printf("Memory allocation failed");
		exit(1);
	}


	for (i = 0; i < size; i++) {
		pointerArr[i] = &arr[i];
	}
	if (ascend_flag == 1) {
		for (i = 0; i < size; i++) {
			for (j = 0; j < size - i - 1; j++) {
				if (*pointerArr[j] > *pointerArr[j + 1]) {
					swapPointers(&pointerArr[j], &pointerArr[j + 1]);
				}
			}
		}
	}
	else {
		for (i = 0; i < size; i++) {
			for (j = 0; j < size - i - 1; j++) {
				if (*pointerArr[j] < *pointerArr[j + 1]) {
					swapPointers(&pointerArr[j], &pointerArr[j + 1]);
				}
			}
		}
	}
	*pointers = pointerArr;
}
printPointers(int** pointers, int size) {

	for (int i = 0; i < size; i++) {
		printf("%d ", *pointers[i]);
	}
}

void main() {
	unsigned int size, i;

	int arr[SIZE];

	int** pointers;

	int ascend_flag;



	printf("Please enter the number of items:\n");

	scanf("%u", &size);


	
	for (i = 0; i < size; i++)

		scanf("%d", &arr[i]);


	
	scanf("%d", &ascend_flag);

	pointerSort(arr, size, ascend_flag, &pointers);

	printf("The sorted array:\n"); //Print the sorted array

	printPointers(pointers, size);

	free(pointers);

}