#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>


#define SIZE 100
#define NOT_NODE -1


typedef struct treeNode {
    int data;
    struct treeNode* left;
    struct treeNode* right;
} TreeNode;

typedef struct tree {
    TreeNode* root;
} Tree;

typedef struct lstNode {
    TreeNode* data;
    struct lstNode* next;
}ListNode;

typedef struct lst {
    ListNode* head;
    ListNode* tail;
}List;



void printByLevels(Tree tr);
void makeEmptyList(List* newList);
bool isEmptyLst(List* lst);
ListNode* createNewNode(TreeNode* TrNode);
void insertToEndList(List* list, ListNode* newNode);
void printNrelease(List* tour);

TreeNode* BuildTreeFromArrayRec(int arr[], int size);
Tree BuildTreeFromArray(int arr[], int size);
void freeTree(Tree tr);
void freeTreeRec(TreeNode* root);
void allocationCheck(void* add);


void main()

{

    int size, i;

    int arr[SIZE];

    Tree tr;

    scanf("%d", &size);

    for (i = 0; i < size; i++)

        scanf("%d", &arr[i]);

    tr = BuildTreeFromArray(arr, size);

    printByLevels(tr);

    freeTree(tr);

}




void printByLevels(Tree tr) {
    List tour;
    makeEmptyList(&tour);

    ListNode* newNode = createNewNode(tr.root);
    insertToEndList(&tour, newNode);

    while (tour.head != NULL) {
        if (tour.head->data->left != NULL) {
            newNode = createNewNode(tour.head->data->left);
            insertToEndList(&tour, newNode);
        }
        if (tour.head->data->right != NULL) {
            newNode = createNewNode(tour.head->data->right);
            insertToEndList(&tour, newNode);
        }

        if (tour.head != NULL)
            printNrelease(&tour);
    }
}
void makeEmptyList(List* newList) {

    newList->head = NULL;
    newList->tail = NULL;
}
bool isEmptyLst(List* lst) {
    if (lst->head == NULL && lst->tail == NULL) {
        return true;
    }
    return false;
}
ListNode* createNewNode(TreeNode* TrNode) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    allocationCheck(node);

    node->data = TrNode;
    node->next = NULL;
    return node;
}
void insertToEndList(List* list, ListNode* newNode) {
    if (isEmptyLst(list)) {
        list->head = newNode;
        list->tail = newNode;
        return;
    }

    list->tail->next = newNode;
    list->tail = newNode;
    newNode->next = NULL;
}
void printNrelease(List* tour) {
    printf("%d ", tour->head->data->data);

    ListNode* toFree = tour->head;
    tour->head = tour->head->next;
    free(toFree);
}
void allocationCheck(void* add) {
    if (add == NULL) {
        printf("Memory allocation failed");
        exit(1);
    }
}
TreeNode* BuildTreeFromArrayRec(int arr[], int size) {
    int mid = size / 2;
    TreeNode* left;
    TreeNode* right;

    if (size <= 0) {
        return NULL;
    }
    else if (arr[mid] == NOT_NODE) {
        return NULL;
    }
    else {


        left = BuildTreeFromArrayRec(arr, mid);
        right = BuildTreeFromArrayRec(arr + (mid + 1), mid);

        TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
        allocationCheck(root);

        root->data = arr[mid];
        root->left = left;
        root->right = right;

        return root;
    }

}
Tree BuildTreeFromArray(int arr[], int size) {

    Tree tree;
    tree.root = NULL;

    tree.root = BuildTreeFromArrayRec(arr, size);
    return tree;

}
void freeTree(Tree tr) {
    if (tr.root != NULL) {
        freeTreeRec(tr.root);
    }
    return;
}
void freeTreeRec(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    else {

        freeTreeRec(root->left);
        freeTreeRec(root->right);

        free(root);
        return;
    }
}