#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "q2.h"





void main(int argc, char** argv) {

    Employee** empArr;
    int empNum;

    empArr = buildArray(argv[1], &empNum);
    printf("before: \n");
    printEmployees(empArr, empNum);

    increaseSalary(empArr, argv[2], empNum);
    printf("after increasmet: \n");
    printEmployees(empArr, empNum);
    
    sortBySalary(&empArr, empNum);
    printf("after sort: \n");
    printEmployees(empArr, empNum);

    writeEmpArray(empArr, empNum, argv[1]);

    freeEmpArray(empArr, empNum);
}