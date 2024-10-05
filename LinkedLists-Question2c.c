#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>


typedef struct listNode {
    int* dataPtr;
    struct listNode* next;
}ListNode;

typedef struct list
{
    ListNode* head;
    ListNode* tail;
}List;

List getList();
void freeList(List* Lst);
void makeEmptyList(List* lst);
void insertDataToEndList(List* lst, int num);
void printList(List* lst);
void insertToEnd(List* lst, ListNode* node);
void mergeRec(List* merged, ListNode* lst1, ListNode* lst2);
List merge(List lst1, List lst2);



void main() {

    List lst1, lst2, mergedList;

    lst1 = getList();

    lst2 = getList();

    mergedList = merge(lst1, lst2);

    printf("Merged list:\n");

    printList(&mergedList);



    freeList(&lst1);

    freeList(&lst2);

    freeList(&mergedList);

}



List getList()

{

    List res;

    int size, num, i;



    makeEmptyList(&res);

    printf("Please enter the number of items to be entered:\n");

    scanf("%d", &size);



    printf("Please enter the numbers:\n");

    for (i = 0; i < size; i++)

    {

        scanf("%d", &num);

        insertDataToEndList(&res, num);

    }
    return res;
}
void freeList(List* Lst) {

    ListNode* currentNode = Lst->head->next;
    ListNode* NodeToFree = Lst->head;

    while (currentNode->next != NULL) {
        free(NodeToFree->dataPtr);
        free(NodeToFree);
        NodeToFree = currentNode;
        currentNode = currentNode->next;
    }
    free(currentNode->dataPtr);
    free(currentNode);
}
void makeEmptyList(List* lst) {

    //creating dummy bear
    ListNode* dummyBear = (ListNode*)malloc(sizeof(ListNode));
    if (dummyBear == NULL) {
        printf("Memory allocation failed");
        exit(1);
    }

    dummyBear->dataPtr = (int*)malloc(sizeof(int));

    dummyBear->next = NULL;
    lst->head = dummyBear;
    lst->tail = dummyBear;
}
void insertDataToEndList(List* lst, int num) {

    ListNode* node_in_list = (ListNode*)malloc(sizeof(ListNode));
    if (node_in_list == NULL) {
        printf("Memory allocation failed");
        exit(1);
    }

    node_in_list->dataPtr = (int*)malloc(sizeof(int));
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

    *(node_in_list->dataPtr) = num;
    node_in_list->next = NULL;
}
void insertToEnd(List* lst, ListNode* node) {
    lst->tail->next = node;
    lst->tail = node;
}

void printList(List* lst) {

    ListNode* currentSquare = lst->head->next;

    while (currentSquare->next != NULL) {
        printf("%d ", *(currentSquare->dataPtr));
        currentSquare = currentSquare->next;
    }
    printf("%d \n", *(currentSquare->dataPtr));
}
void mergeRec(List* merged, ListNode* lst1, ListNode* lst2) {

    if (lst1 == NULL && lst2 == NULL) {
        return;
    }
    else if (lst1 == NULL) {
        while (lst2->next != NULL) {
            insertDataToEndList(merged, *(lst2->dataPtr));
            lst2 = lst2->next;
        }
        insertDataToEndList(merged, *(lst2->dataPtr));
        return;
    }
    else if (lst2 == NULL) {
        while (lst1->next != NULL) {
            insertDataToEndList(merged, *(lst1->dataPtr));
            lst1 = lst1->next;
        }
        insertDataToEndList(merged, *(lst1->dataPtr));
        return;
    }
    else {
        if (*(lst1->dataPtr) > *(lst2->dataPtr)) {
            insertDataToEndList(merged, *(lst1->dataPtr));
            mergeRec(merged, lst1->next, lst2);
        }
        else {
            insertDataToEndList(merged, *(lst2->dataPtr));
            mergeRec(merged, lst1, lst2->next);
        }

    }

}



List merge(List lst1, List lst2) {
    List merged;
    makeEmptyList(&merged);


    mergeRec(&merged, lst1.head->next, lst2.head->next);

    return merged;
}