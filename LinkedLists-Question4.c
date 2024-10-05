#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define NUM_SIZE 10

typedef struct list_node
{
    char* dataPtr;
    struct list_node* next;
}ListNode;

typedef struct list
{
    ListNode* head;
    ListNode* tail;
}List;

typedef struct  student
{
    List first;
    int grade;
} Student;

Student unScramble(List lst);
void makeEmptyList(List* lst);
void insertDataToEndList(List* lst, char ch);
void printStudent(Student* student);
void freeList(List* studentNameLst);


void main() {
    List lst;

    Student student;

    char ch;

    makeEmptyList(&lst);

    printf("Please enter the scrambled student:\n");

    ch = (char)getchar();

    while (ch != '\n')

    {

        insertDataToEndList(&lst, ch);

        ch = (char)getchar();

    }

    student = unScramble(lst);

    printStudent(&student);

    freeList(&student.first);
}



Student unScramble(List lst) {
    Student studentData;
    int studentGrade = 0;
    bool lastNote = false;

    ListNode* currentNode = lst.head->next;
    ListNode* stepBackNode = lst.head;
    ListNode* toFree = NULL;

    while (currentNode->next != NULL) {

        for (; lastNote == false && '9' >= *(currentNode->dataPtr) && *(currentNode->dataPtr) >= '0';) {
            toFree = currentNode;
            if (currentNode->next == NULL) {
                lastNote = true;
            }
            else {
                currentNode = currentNode->next;
            }

            studentGrade = studentGrade * NUM_SIZE + *(toFree->dataPtr) - '0';
            free(toFree->dataPtr);
            free(toFree);
            toFree = NULL;
        }

        if (lastNote == true) {
            currentNode = stepBackNode;
            currentNode->next = NULL;
            lst.tail = currentNode;
        }
        else if ('z' >= *(currentNode->dataPtr) && *(currentNode->dataPtr) >= 'a') {
            stepBackNode->next = currentNode;
        }

        if (currentNode->next != NULL) {
            stepBackNode = currentNode;
            currentNode = currentNode->next;
        }
    }

    if ('9' >= *(currentNode->dataPtr) && *(currentNode->dataPtr) >= '0' && studentGrade == 0) {
        studentGrade = studentGrade * NUM_SIZE + *(currentNode->dataPtr) - '0';
        lst.tail = stepBackNode;
        stepBackNode->next = NULL;
        free(currentNode->dataPtr);
        free(currentNode);
    }

    studentData.first = lst;
    studentData.grade = studentGrade;
    return studentData;
}
void makeEmptyList(List* lst) {

    //creating dummy bear
    ListNode* dummyBear = (ListNode*)malloc(sizeof(ListNode));
    if (dummyBear == NULL) {
        printf("Memory allocation failed");
        exit(1);
    }
    dummyBear->next = NULL;
    lst->head = dummyBear;
    lst->tail = dummyBear;
}
void insertDataToEndList(List* lst, char ch) {

    ListNode* node_in_list = (ListNode*)malloc(sizeof(ListNode));
    if (node_in_list == NULL) {
        printf("Memory allocation failed");
        exit(1);
    }

    node_in_list->dataPtr = (char*)malloc(sizeof(char));
    if (node_in_list->dataPtr == NULL) {
        printf("Memory allocation failed");
        exit(1);
    }

    if (lst->head->next == NULL) {
        lst->head->next = node_in_list;
        lst->tail = node_in_list;
    }
    else {

        lst->tail->next = node_in_list;
        lst->tail = node_in_list;
    }

    *(node_in_list->dataPtr) = ch;
    node_in_list->next = NULL;
}
void printStudent(Student* student) {

    ListNode* currentSquare = student->first.head->next;
    printf("First name: ");
    while (currentSquare->next != NULL) {
        printf("%c", *(currentSquare->dataPtr));
        currentSquare = currentSquare->next;
    }
    printf("%c \n", *(currentSquare->dataPtr));

    printf("Grade: %d \n", student->grade);
}
void freeList(List* studentNameLst) {

    ListNode* currentNode = studentNameLst->head->next;
    ListNode* NodeToFree = studentNameLst->head;

    while (currentNode->next != NULL) {
        free(NodeToFree->dataPtr);
        free(NodeToFree);
        NodeToFree = currentNode;
        currentNode = currentNode->next;
    }
    free(studentNameLst->tail->dataPtr);
    free(studentNameLst->tail);
}
