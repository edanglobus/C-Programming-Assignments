#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TEN 10  // Constant representing the number 10 (used for table dimensions)

// Function that returns the number of digits in a given number
int countDig(int num);

void main() {
    int k, i = 1, j = 1;
    int bNum;  
    int cNum;  

    // Generates a 10x10 multiplication table, with proper alignment of numbers in columns
    for (i = 1; i <= TEN; i++) {
        for (j = 1; j <= TEN; j++) {
            bNum = countDig(TEN * j);  
            cNum = countDig(i * j);  

            if (j == 1)
                k = 1;  
            else
                k = 0; 

            // Print spaces to align columns based on the number of digits
            for (; k < bNum - cNum + 1; k++) {
                printf(" ");
            }
            printf("%d", i * j);  
        }
        printf("\n");
    }
}

// Function that counts and returns the number of digits in a given number
int countDig(int num) {
    int count = 0;
    if (num == 0)
        return 0;
    else
        count = (int)log10(num) + 1;

    return count;
}