#include <stdio.h>
#include <stdlib.h>
#include "Q2.h"



void writeEmpArray(Employee** empArr, int empNum, char* fileName) {
    checkFileName(fileName);

    FILE* file = fopen(fileName, "wb");
    fileCheck(file);

    for (int i = 0; i < empNum; i++) {
        fwrite(&(empArr[i]->name_length), sizeof(int), 1, file);
        fwrite(empArr[i]->name, sizeof(char), empArr[i]->name_length, file);
        fwrite(&(empArr[i]->salary), sizeof(float), 1, file);
    }
    fclose(file);
}
Employee* readEmployee(char* fileName, int* empSize) {
    checkFileName(fileName);
    static int tell = 0; // the cursor doesnt stay static with out it (dont know why) thats why i made static

    FILE* file = fopen(fileName, "rb"); // open file for binary read
    fileCheck(file);
    fseek(file, tell, SEEK_SET); // the cursor doesnt stay static with out it (dont know why) thats why i made static

    Employee* emp = (Employee*)malloc(sizeof(Employee)); // allocate memory for Employee struct
    memoryCheck(emp);

    fread(&(emp->name_length), sizeof(int), 1, file); // read the name length

    emp->name = (char*)malloc(sizeof(char) * (emp->name_length + 1)); // allocate memory for the name + 1 for '\0'
    memoryCheck(emp->name);

    fread(emp->name, sizeof(char), emp->name_length, file); // read the employe name
    emp->name[emp->name_length] = '\0';

    fread(&(emp->salary), sizeof(float), 1, file); // read employe salary


    int seek = ftell(file); // the cursor doesnt stay static with out it (dont know why) thats why i made static
    tell += seek; // the cursor doesnt stay static with out it (dont know why) thats why i made static
    fclose(file);
    *empSize = sizeof(int) + sizeof(char) * (emp->name_length + 1) + sizeof(float);
    return emp;
}
Employee** buildArray(char* fileName, int* arrSize) {
    checkFileName(fileName);

    int phis = 2, log = 0;
    Employee** empArray = (Employee**)malloc(sizeof(Employee*) * phis); // allocate memory for array of struct address
    Employee* currEmpRead;

    long int file_size = fileSize(fileName); // checking file bytes size
    int currSize = 0;
    for (long int empCount = 0; empCount < file_size;) {           // loop running from current read bytes to file size bytes
        if (log == phis) {                                        // allocate memory dynamic size
            phis *= 2;
            empArray = (Employee**)realloc(empArray, sizeof(Employee*) * phis);
            memoryCheck(empArray);
        }
        currEmpRead = readEmployee(fileName, &currSize);          // funciton reading employee each time
        empArray[log] = currEmpRead;                              // insert employee to array in position log
        log++;                                                     // increase array log size
        empCount += currSize;                                     // taking currEmpRead size(bytes) and sum it in empCount 
    }
    empArray = (Employee**)realloc(empArray, sizeof(Employee*) * log);    // allocate memory for array in logic size
    memoryCheck(empArray);

    *arrSize = log;
    return empArray;
}
void increaseSalary(Employee** array, char* fileName, int empNum) {
    checkFileName(fileName);
    float increasement = 0;
    FILE* file = fopen(fileName, "rb");
    fileCheck(file);

    for (int i = 0; i < empNum; i++) {
        fread(&increasement, sizeof(float), 1, file);
        array[i]->salary += increasement;
    }
    fclose(file);
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
void checkFileName(char* fileName) {
    if (fileName == NULL) {
        printf("File not exist.");
        exit(1);
    }
}
void printEmployees(Employee** employees, int arrSize) {
    for (int i = 0; i < arrSize; ++i) {
        printf("Employee %d:\n", i + 1);
        printf("Name: %s\n", employees[i]->name);
        printf("Salary: %.2f\n", employees[i]->salary);
        printf("\n");
    }
}
void sortBySalary(Employee*** pempArr, int empSize) {
    Employee** empArr = *pempArr;

    for (int j = 0; j < empSize; j++) {
        for (int i = j; i < empSize - 1; i++) {
            if (empArr[i]->salary < empArr[i + 1]->salary) {
                swapEmp(empArr, i, i + 1);
            }
        }
    }
}
void swapEmp(Employee** arr, int a, int b) {
    Employee* tmp = arr[a];

    arr[a] = arr[b];
    arr[b] = tmp;
}
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
void freeEmpArray(Employee** arr, int size) {
    for (int i = 0; i < size; i++) {
        free(arr[i]->name);
        free(arr[i]);
    }free(arr);
}
