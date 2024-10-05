#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "q1.h"







void main(int argc, char** argv) {
    char** str_str;
    int num = atoi(argv[2]);
    str_str = readStrFileSmallLetter(argv[1], num);

    newFilePrintf(argv[1], str_str, num);
}