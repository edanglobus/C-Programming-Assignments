#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct monom {
    int coefficient;	//המקדם  
    int power;		// החזקה
}Monom;

void swapPoly(Monom *poly1, Monom *poly2) {
    Monom tmp;

    tmp = *poly1;
    *poly1 = *poly2;
    *poly2 = tmp;
}
int countNumInStr(char str[]) {
    int count = 0;
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9') {
            if (str[i + 1] == '\0' || str[i + 1] == ' ')
                count++;
        }
        i++;
    }
    return count;
}
void strToArr(Monom arr[], int size, char str[], int strSize) {
    int num = 0;
    int sign = 1;
    int count = 0;
    bool fullMonom = false;

    
    for (int j = 0; j < strSize; j++) {

        if (str[j] == '-') {
            sign = -1;
        }
        else if (str[j] >= '0' && str[j] <= '9') {
            num = (num * 10) + str[j] - '0';
            if (str[j + 1] == ' ' && str[j+1] != '\0') {
             

                if (fullMonom == false) {
                    arr[count].coefficient = num * sign;
                    fullMonom = true;
                }
                else {
                    arr[count].power = num * sign;
                    count++;
                    fullMonom = false;
                }
                sign = 1;
                num = 0;
            }
        }
        
    }
}
void sortPoly(Monom poly[], int size) {
    int i, j;

    for (i = 0; i < size; i++) {

        for (j = 0; j < size; j++) {
            if (poly[i].power > poly[j].power) {
                swapPoly(&poly[i], &poly[j]);
            }
        }
    }
}


Monom* getPolynom(int* size) {
        int phis = 1, logic = 0;
        char currentChar;
        int number = 0;
        


        char* string = (char*)malloc(phis * sizeof(char));
        if (string == NULL) {
            printf("Memory allocation failed");
            exit(1);
        }
        currentChar = getchar();

        while (currentChar != '\n') {
            if (currentChar >= '0' && currentChar <= '9' || currentChar == '-' || currentChar == ' ') {
                string[logic] = currentChar;
                logic++;
            }
            if (logic == phis) {
                phis *= 2;
                string = (char*)realloc(string, phis * sizeof(char));
                if (string == NULL) {
                    printf("Memory allocation failed");
                    exit(1);
                }
            }
            currentChar = getchar();
        }
        string[logic] = ' ';

       
        int arrSize = countNumInStr(string)/2;
        Monom* polyArr = (Monom*)malloc((arrSize) * sizeof(Monom));
        if (polyArr == NULL) {
            printf("Memory allocation failed");
            exit(1);
        }
        strToArr(polyArr, arrSize , string, logic);
        free(string);
        
        sortPoly(polyArr, arrSize);
        
        *size = arrSize;
        return polyArr;
    }
void printPolySum(Monom* polynom1, int polynom1Size, Monom* polynom2, int polynom2Size) {
    int i = 0, j = 0;

    int coefficient = 0;
    int currentPower = 0;
    bool firstloop = true;
    char sign;

    while (i < polynom1Size || j < polynom2Size) {
        coefficient = 0;
        currentPower = 0;

        if (polynom1[i].power >= polynom2[j].power) {
            currentPower = polynom1[i].power;
        }
        else {
            currentPower = polynom2[j].power;
        }

        while (currentPower == polynom1[i].power && i < polynom1Size) {
            coefficient += polynom1[i].coefficient;
            i++;
        }
       
        while (currentPower == polynom2[j].power && j < polynom2Size) {
                coefficient += polynom2[j].coefficient;
                j++;
        }
        if (coefficient != 0) {
            if (firstloop == true) {
                if (coefficient == 1 && currentPower != 0) {
                    printf("X^%d", currentPower);
                }
                else if (coefficient == 1 && currentPower == 0) {
                    printf("1");
                }
                else {
                    if (currentPower == 1) {
                        printf("%dX", coefficient);
                    }
                    else if (currentPower == 0) {
                        printf("%d", coefficient);
                    }
                    else {
                        printf("%dX^%d", coefficient, currentPower);
                    }  
                }
                firstloop = false;
            }
            else {
                if (coefficient < 0) {
                    coefficient *= (-1);
                    sign = '-';
                }
                else {
                    sign = '+';
                }

                if (coefficient == 1 && currentPower != 0) {
                    printf(" %c X^%d", sign, currentPower);
                }
                else if (coefficient == 1 && currentPower == 0) {
                    printf(" %c 1", sign);
                }
                else {
                    if (currentPower == 1) {
                        printf(" %c %dX", sign, coefficient);
                    }
                    else if (currentPower == 0) {
                        printf(" %c %d", sign, coefficient);
                    }
                    else {
                        printf(" %c %dX^%d", sign, coefficient, currentPower);
                    }
                }
            }
        }
       
    }

}
void printPolyMul(Monom* polynom1, int polynom1Size, Monom* polynom2, int polynom2Size) {
    int i = 0, j = 0;

    int coefficient = 0;
    int currentPower = 0;
    bool firstloop = true;

    int polySize = polynom1Size * polynom2Size;
    int insert = 0;
    Monom* polyArray = (Monom*)malloc((polySize) * sizeof(Monom));
    if (polyArray == NULL) {
        printf("Memory allocation failed");
        exit(1);
    }

    for (i = 0; i < polynom1Size; i++) {
        for (j = 0; j < polynom2Size; j++) {
            polyArray[insert].coefficient = polynom1[i].coefficient * polynom2[j].coefficient;
            polyArray[insert].power = polynom1[i].power + polynom2[j].power;
            insert++;
        }
    }
    sortPoly(polyArray, insert);

    for (i = 0; i < insert;) {
        currentPower = polyArray[i].power;
        coefficient = 0;
        
        while (currentPower == polyArray[i].power && i < insert) {
            coefficient += polyArray[i].coefficient;
            i++;
        }

        char sign;
        if (coefficient != 0) {
            if (firstloop == true) {
                if ((coefficient == 1 || coefficient == -1) && currentPower != 0) {
                    printf("X^%d", currentPower);
                }
                else if ((coefficient == 1 || coefficient == -1) && currentPower == 0) {
                    printf("1");
                }
                else {
                    if (currentPower == 1) {
                        printf("%dX", coefficient);
                    }
                    else if (currentPower == 0) {
                        printf("%d", coefficient);
                    }
                    else {
                        printf("%dX^%d", coefficient, currentPower);
                    }
                }
                firstloop = false;
            }
            else {
                if (coefficient < 0) {
                    coefficient *= (-1);
                    sign = '-';
                }
                else {
                    sign = '+';
                }

                if ((coefficient == 1 || coefficient == -1) && currentPower != 0) {
                    printf(" %c X^%d", sign, currentPower);
                }
                else if ((coefficient == 1 || coefficient == -1) && currentPower == 0) {
                    printf(" %c 1", sign);
                }
                else {
                    if (currentPower == 1) {
                        printf(" %c %dX", sign, coefficient);
                    }
                    else if (currentPower == 0) {
                        printf(" %c %d", sign, coefficient);
                    }
                    else {
                        printf(" %c %dX^%d", sign, coefficient, currentPower);
                    }
                }
            }
        }

    }
    free(polyArray);

}
   



    void main() {
      
        Monom* polynom1, * polynom2;             // The input polynoms
        unsigned int polynom1Size, polynom2Size; // The size of each polynom

        printf("Please enter the first polynom:\n");
        polynom1 = getPolynom(&polynom1Size);   // get polynom 1

        printf("Please enter the second polynom:\n");
        polynom2 = getPolynom(&polynom2Size);   // get polynom 2

        printf("The multiplication of the polynoms is:\n"); // print the multiplication
        printPolyMul(polynom1, polynom1Size, polynom2, polynom2Size);
        printf("\n");

        printf("The sum of the polynoms is:\n"); // print the sum
        printPolySum(polynom1, polynom1Size, polynom2, polynom2Size);
        printf("\n");

        free(polynom1); // releasing all memory allocations
        free(polynom2);
    }