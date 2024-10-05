





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

List merge(List lst1, List lst2);
List getList();
void makeEmptyList(List* lst);
void insertDataToEndList(List* lst, int num);
void freeList(List* Lst);
void printList(List* lst);
void insertToEnd(List* lst, ListNode* node);
void sortedInsert(List* lst, ListNode* nodeToInsert);


void main()

{

    List lst1, lst2, mergedList;

    lst1 = getList();

    lst2 = getList();

    mergedList = merge(lst1, lst2);

    printf("Merged list:\n");

    printList(&mergedList);



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
List merge(List lst1, List lst2) {

    List functionList;
    ListNode functionDummy;
    functionDummy.next = NULL;
    functionList.head = &functionDummy;
    functionList.tail = &functionDummy;
    // in the end need to make lst1 dummy head take functionList pointers: lst1.head->next = functiondummy.next;
    ListNode* current_lst_1 = lst1.head->next;
    ListNode* current_lst_2 = lst2.head->next;
    ListNode* current_tmp;

    while (current_lst_1->next != NULL && current_lst_2->next != NULL) {
        if (*(current_lst_1->dataPtr) > *(current_lst_2->dataPtr)) {
            insertToEnd(&functionList, current_lst_1);
            current_lst_1 = current_lst_1->next;
        }
        else {
            insertToEnd(&functionList, current_lst_2);
            current_lst_2 = current_lst_2->next;
        }
    }

    if (current_lst_1->next == NULL) {
        lst2.head->next = current_lst_2;
        sortedInsert(&lst2, current_lst_1);
        functionList.tail->next = lst2.head->next;
        functionList.tail = lst2.tail;
    }
    else {
        lst1.head->next = current_lst_1;
        sortedInsert(&lst1, current_lst_2);
        functionList.tail->next = lst1.head->next;
        functionList.tail = lst1.tail;
    }

    lst1.head->next = functionDummy.next;
    lst1.tail = functionList.tail;
    return lst1;
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
    free(Lst->tail->dataPtr);
    free(Lst->tail);
}
void printList(List* lst) {

    ListNode* currentSquare = lst->head->next;

    while (currentSquare->next != NULL) {
        printf("%d ", *(currentSquare->dataPtr));
        currentSquare = currentSquare->next;
    }
    printf("%d \n", *(currentSquare->dataPtr));
}
void insertToEnd(List* lst, ListNode* node) {
    lst->tail->next = node;
    lst->tail = node;
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
void sortedInsert(List* lst, ListNode* nodeToInsert) {

    ListNode* current;
    ListNode* stepBack;

    current = lst->head->next;
    stepBack = lst->head->next;

    while (*(current->dataPtr) > *(nodeToInsert->dataPtr) && current->next != NULL) {
        stepBack = current;
        current = current->next;
    }

    if (*(lst->tail->dataPtr) > *(nodeToInsert->dataPtr)) {
        lst->tail->next = nodeToInsert;
        lst->tail = nodeToInsert;
        nodeToInsert->next = NULL;
    }
    else if (*(nodeToInsert->dataPtr) >= *(lst->head->next->dataPtr)) {
        nodeToInsert->next = lst->head->next;
        lst->head->next = nodeToInsert;
    }
    else {
        nodeToInsert->next = current;
        stepBack->next = nodeToInsert;
    }
}
