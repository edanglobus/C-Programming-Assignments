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
void freeList(List* Lst);
void makeEmptyList(List* lst);
void insertDataToEndList(List* lst, int num);
void printList(List* lst);


void main()

{

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
List merge(List lst1, List lst2) {
    List mergedList;
    makeEmptyList(&mergedList);

    ListNode* current_lst_1 = lst1.head->next;
    ListNode* current_lst_2 = lst2.head->next; 

    while (current_lst_1->next != NULL && current_lst_2->next != NULL) {
        if (*(current_lst_1->dataPtr) > *(current_lst_2->dataPtr)) {
            insertDataToEndList(&mergedList, *(current_lst_1->dataPtr));
            current_lst_1 = current_lst_1->next;
        }
        else {
            insertDataToEndList(&mergedList, *(current_lst_2->dataPtr));
            current_lst_2 = current_lst_2->next;
        }
    }

    if (current_lst_1->next == NULL) {
        bool last_1 = false;
        int numToIsert = *(current_lst_1->dataPtr);

        while (current_lst_2->next != NULL) {
            if (last_1 == false && numToIsert > *(current_lst_2->dataPtr)) {
            insertDataToEndList(&mergedList, numToIsert);
            last_1 = true;
            }
            else {
            insertDataToEndList(&mergedList, *(current_lst_2->dataPtr));
            current_lst_2 = current_lst_2->next;
            }
        }
      
        if (last_1 == false) {
            if (*(current_lst_1->dataPtr) > *(current_lst_2->dataPtr)) {
                insertDataToEndList(&mergedList, *(current_lst_1->dataPtr));
                insertDataToEndList(&mergedList, *(current_lst_2->dataPtr));
            }
            else {
                insertDataToEndList(&mergedList, *(current_lst_2->dataPtr));
                insertDataToEndList(&mergedList, *(current_lst_1->dataPtr));
            }
            last_1 = true;
        }
        else {
            insertDataToEndList(&mergedList, *(current_lst_2->dataPtr));
        }
    }
    else if (current_lst_2->next == NULL)
    {
        bool last_2 = false;
        int numToInsert2 = *(current_lst_2->dataPtr);

        while (current_lst_1->next != NULL) {
            if (last_2 == false && numToInsert2 > *(current_lst_1->dataPtr)) {
                insertDataToEndList(&mergedList, numToInsert2);
                last_2 = true;
            }
            else {
            insertDataToEndList(&mergedList, *(current_lst_1->dataPtr));
            current_lst_1 = current_lst_1->next;
            }
        }

        if (last_2 == false) {
            if (*(current_lst_2->dataPtr) > *(current_lst_1->dataPtr)) {
                insertDataToEndList(&mergedList, *(current_lst_2->dataPtr));
                insertDataToEndList(&mergedList, *(current_lst_1->dataPtr));
            }
            else {
                insertDataToEndList(&mergedList, *(current_lst_1->dataPtr));
                insertDataToEndList(&mergedList, *(current_lst_2->dataPtr));
            }
            last_2 = true;
        }
        else {
            insertDataToEndList(&mergedList, *(current_lst_1->dataPtr));
        }



    }


    ListNode* current_lst = mergedList.head;

    return mergedList;

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
void printList(List* lst) {

    ListNode* currentSquare = lst->head->next;
  
    while (currentSquare->next != NULL) {
        printf("%d ", *(currentSquare->dataPtr));
        currentSquare = currentSquare->next;
    }
    printf("%d \n", *(currentSquare->dataPtr));
}