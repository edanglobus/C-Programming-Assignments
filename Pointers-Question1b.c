#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TABLE 10  // Constant for default table size

// Function that generates a multiplication table up to the specified number
void generTable(int num);

// Main function: takes user input and generates a multiplication table
void main() {
    int maxMult;  

    printf("Please enter number:\n");  

    scanf("%d", &maxMult); 

    generTable(maxMult);  
}

// Function that counts the number of digits in a given number
int countDig(int num) {
    int count = 0;

    if (num == 0)
        return 0;
    else
        count = (int)log10(num) + 1;  

    return count;
}

// Function that generates a multiplication table up to 'num x num'
void generTable(int num) {
    int k, i = 1, j = 1;
    int bNum; 
    int cNum;  

    // Loop through rows and columns to print the multiplication table
    for (i = 1; i <= num; i++) {
        for (j = 1; j <= num; j++) {
            bNum = countDig(num * j);  
            cNum = countDig(i * j);  

            if (j == 1)
                k = 1;  
            else
                k = 0;  

           
            for (; k < bNum - cNum + 1; k++) {
                printf(" ");
            }
            printf("%d", i * j);  
        }
        printf("\n");  
    }
}