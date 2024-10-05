#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void printArray(char** strArray, int size) {

	for (int i = 0; i < size; i++) {
		printf("string %d: %s \n", i, strArray[i]);
	}
}
void freeArray(char** strArray, int size) {


	for (int i = 0; i < size; i++) {
		free(strArray[i]);
	}
	free(strArray);
}
char** setPtrToCharsArray(char** str_array)

{

	char** res;

	int size, i;

	int str_array_row, str_array_col;


	printf("insert ptr size: ");
	scanf("%d", &size); // Get number of ptrs

	res = (char**)malloc(sizeof(char*) * (size + 1)); // Add 1 for NULL at the end
	if (res == NULL) {
		printf("Memory failed");
		exit(1);

	}

	for (i = 0; i < size; i++)

	{

		scanf("%d", &str_array_row);

		scanf("%d", &str_array_col);

		res[i] = str_array[str_array_row] + str_array_col;

	}



	res[size] = NULL; // Set the last one to NULL



	return res;

}
char** getStrArrayInput(int* size) {
	int i = 0;
	int main_phis = 2;
	int main_logic = 0;

	char** mainStrArray = (char**)malloc(main_phis * sizeof(char*));
	if (mainStrArray == NULL) {
		printf("Memory allocation failed");
		exit(1);
	}


	char tester;
	int phis, logic;
	bool emptyStr = false;

	while (emptyStr == false) {
		phis = 2, logic = 0;
		mainStrArray[main_logic] = (char*)malloc(phis * sizeof(char));
		if (mainStrArray[main_logic] == NULL) {
			printf("Memory allocation failed");
			exit(1);
		}

		tester = getchar();
		while (tester != '\n') {
			if (logic == phis) {
				phis *= 2;
				mainStrArray[main_logic] = (char*)realloc(mainStrArray[main_logic], phis * sizeof(char));
				if (mainStrArray[main_logic] == NULL) {
					printf("Memory allocation failed");
					exit(1);
				}
			}

			mainStrArray[main_logic][logic] = tester;
			++logic;
			tester = getchar();
		}

		if (logic > 0) {
			mainStrArray[main_logic] = (char*)realloc(mainStrArray[main_logic], (logic + 1) * sizeof(char));
			if (mainStrArray[main_logic] == NULL) {
				printf("Memory allocation failed");
				exit(1);
			}

			char zero = '\0';
			mainStrArray[main_logic][logic] = '\0';
			main_logic++;

			if (main_logic == main_phis) {
				main_phis *= 2;
				mainStrArray = (char**)realloc(mainStrArray, main_phis * sizeof(char*));
				if (mainStrArray == NULL) {
					printf("Memory allocation failed");
					exit(1);
				}
			}
		}
		else {
			free(mainStrArray[main_logic]);
			emptyStr = true;
		}
	}

	mainStrArray = (char**)realloc(mainStrArray, main_logic * sizeof(char*));
	if (mainStrArray == NULL) {
		printf("Memory allocation failed");
		exit(1);
	}

	*size = main_logic;
	return mainStrArray;


}
void deleteFromStr(char* str) {

	int size = strlen(str);

	for (int i = 1; i < size; i++) {
		str[i - 1] = str[i];

	}
	str[size - 1] = '\0';
}


unsigned int  RemoveFromStrArray(char** str_array, unsigned  int  str_array_size, char** ptr_to_chars_array)
{
	int i, j, k;
	int counter = 0;

	int* sizeArray = (int*)calloc(str_array_size, sizeof(int));
	if (sizeArray == NULL) {
		printf("Memory allocation failed");
		exit(1);
	}

	// initialize the dynamic array to the size of each string in str_array
	for (i = 0; i < str_array_size; i++) {
		sizeArray[i] = strlen(str_array[i]);
	}

	// replace all char that need to be deleted with \0
	for (i = 0; ptr_to_chars_array[i] != NULL; i++) {
		*(ptr_to_chars_array[i]) = '\0';
	}




	// loop to delete all '\0' from the str except from the last one
	for (i = 0; i < str_array_size; i++) {

		
		for (j = 0; j < sizeArray[i]; j++) {

			// running on each string on str_array and check if char == '\0'
			if (str_array[i][j] == '\0') {
				k = j;
				while (k < sizeArray[i]) {
					str_array[i][k] = str_array[i][k + 1];
					k++;
				}
				sizeArray[i]--;
				str_array[i][sizeArray[i]] = '\0';			
				j--;
			}
			
			str_array[i] = (char*)realloc(str_array[i], (sizeArray[i] + 1) * sizeof(char));
			if (str_array[i] == NULL) {
				printf("Memory allocation failed 1");
				exit(1);
			}
			
		}
	}

	// loop to delete empty strings from str_array
	for (int z = 0; z < str_array_size; z++) {
		if (str_array[z][0] == '\0') {
			char* strToFree = str_array[z];
			free(strToFree);
			for (int k = z; k < str_array_size - 1; k++) {
				str_array[k] = str_array[k + 1];
				
			}
			str_array_size--;
			counter++;
			z--;
			
		}
	}
	

	free(sizeArray);
	return counter;

}


void main() {
	char** str_array;

	unsigned int str_array_size;

	char** ptr_to_chars_array;

	unsigned int res = 0;



   str_array = getStrArrayInput(&str_array_size); // Get the size and strings from user (can't assume max size for each string)

   ptr_to_chars_array = setPtrToCharsArray(str_array);

   res = RemoveFromStrArray(str_array, str_array_size, ptr_to_chars_array);
   printArray(str_array, str_array_size - res);
   printf("%d", res);

	// Free memory
	freeArray(str_array, str_array_size - res);

	free(ptr_to_chars_array);

}



