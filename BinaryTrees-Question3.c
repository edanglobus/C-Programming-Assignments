#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>


typedef struct listNode {
    int data;
    struct listNode* next;
} ListNode;

typedef struct list {
    ListNode* head;
    ListNode* tail;
} List;

typedef struct  treeNode {
    int data;
    struct treeNode* parent;
    struct treeNode* left;
    struct treeNode* right;
} TreeNode;

typedef struct tree {
    TreeNode* root;
    List leafList;
} Tree;



#define NOT_NODE -1
#define SIZE 100
#define LEFT  0 
#define RIGHT 1 




TreeNode* createTreeNode(int data);
ListNode* createListNode(int data);
void makeEmptyList(List* newList);
bool isEmptyLst(List* lst);
void insertToEndList(List* list, ListNode* newNode);
void allocationCheck(void* add);
void printLeafList(Tree tr);
void printParent(TreeNode* tr);
Tree BuildTreeFromArrayWithLeafList(int* arr, int size);
TreeNode* BuildTreeFromArrayRec(List* lst, int arr[], int size);
TreeNode* findParent(Tree tr, int parentData, int branchSelect);
TreeNode* findParentRec(TreeNode* root, int Data, int branchSelect);
Tree AddLeaf(Tree tr, TreeNode* p, int branchSelect, int data);
Tree findAndPlaceNodeInTree(Tree tr, TreeNode* p, int branchSelect, int data);
Tree findAndPlaceNodeInLst(Tree tr, TreeNode* p, int branchSelect, int data);
void printTreeInorder(Tree tr);
void printTreeInorderRec(TreeNode* root);
void freeTree(Tree tr);
void freeTreeRec(TreeNode* root);
void freeLst(List lst);

void main()
{
    int size, i;
    int arr[SIZE];
    Tree tr;
    TreeNode* p;
    int parentData, data, branchSelect;



    printf("Please enter the number of items: ");
    scanf("%d", &size);

    for (i = 0; i < size; i++)
        scanf("%d", &arr[i]);

    scanf("%d%d%d", &parentData, &data, &branchSelect);

    tr = BuildTreeFromArrayWithLeafList(arr, size);//the array is given as described in question 1


    //scan the tree inorder (LDR) and find the first parent (a node with parentData as data) that has no child in branchSelect


    p = findParent(tr, parentData, branchSelect);

    tr = AddLeaf(tr, p, branchSelect, data);
    printTreeInorder(tr); //Print the tree in-order (LDR)
    printLeafList(tr); //Print the leaves from left to right
    freeTree(tr);
}


TreeNode* BuildTreeFromArrayRec(List* lst, int arr[], int size) {
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


        left = BuildTreeFromArrayRec(lst, arr, mid);
        right = BuildTreeFromArrayRec(lst, arr + (mid + 1), mid);

        TreeNode* root = createTreeNode(arr[mid]);
        root->left = left;
        root->right = right;


        if (left != NULL) {
            root->left->parent = root;
        }
        if (right != NULL) {
            root->right->parent = root;
        }

        if (left == NULL && right == NULL) {
            ListNode* newNode = createListNode(arr[mid]);
            insertToEndList(lst, newNode);
        }

        return root;
    }

}
TreeNode* createTreeNode(int data) {
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    allocationCheck(root);

    root->data = data;
    root->parent = NULL;
    root->left = NULL;
    root->right = NULL;

    return root;
}
TreeNode* findParent(Tree tr, int parentData, int branchSelect) {
    TreeNode* selectedP;

    selectedP = findParentRec(tr.root, parentData, branchSelect);
    return selectedP;
}
TreeNode* findParentRec(TreeNode* root, int Data, int branchSelect) {

    if (root == NULL) {
        return NULL;
    }
    else {

        TreeNode* left = findParentRec(root->left, Data, branchSelect);
        TreeNode* right = findParentRec(root->right, Data, branchSelect);

        TreeNode* branch;
        if (branchSelect == LEFT) {
            branch = root->left;
        }
        else {
            branch = root->right;
        }

        if (root->data == Data && branch == NULL) {
            return root;
        }
        else if (left != NULL || right != NULL) {
            if (left != NULL)
                return left;
            else
                return right;
        }
        else {
            return NULL;
        }
    }
}
ListNode* createListNode(int data) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    allocationCheck(node);

    node->data = data;
    node->next = NULL;
    return node;
}



Tree BuildTreeFromArrayWithLeafList(int* arr, int size) {
    Tree tr;
    List leafList;
    makeEmptyList(&leafList);
    tr.root = BuildTreeFromArrayRec(&leafList, arr, size);
    tr.leafList = leafList;

    return tr;
}
Tree AddLeaf(Tree tr, TreeNode* p, int branchSelect, int data) {

    tr = findAndPlaceNodeInTree(tr, p, branchSelect, data);
    tr = findAndPlaceNodeInLst(tr, p, branchSelect, data);
    return tr;
}
Tree findAndPlaceNodeInTree(Tree tr, TreeNode* p, int branchSelect, int data) {
    TreeNode* trNode = createTreeNode(data);
    trNode->parent = p;

    if (branchSelect == LEFT) {
        p->left = trNode;
    }
    else {
        p->right = trNode;
    }
    return tr;
}
Tree findAndPlaceNodeInLst(Tree tr, TreeNode* p, int branchSelect, int data) {
    ListNode* lstNode = createListNode(data);

    ListNode* currentNode = tr.leafList.head;
    ListNode* forwardNode = tr.leafList.head->next;


    if (p->data == tr.root->data) {
        if (branchSelect == LEFT) {
            lstNode->next = tr.leafList.head;
            tr.leafList.head = lstNode;
        }
        else {
            tr.leafList.tail->next = lstNode;
            tr.leafList.tail = lstNode;

        }
    }
    else {
        if (currentNode->data == p->data) {
            lstNode->next = currentNode->next;
            tr.leafList.head = lstNode;
            free(currentNode);
        }
        else {
            while (forwardNode->data != p->data) {
                if (forwardNode->next != NULL) {
                    currentNode = currentNode->next;
                    forwardNode = forwardNode->next;
                }
                else {
                    break;
                }
            }
            lstNode->next = forwardNode->next;
            currentNode->next = lstNode;
            free(forwardNode);
        }
    }

    return tr;
}



bool isEmptyLst(List* lst) {
    if (lst->head == NULL && lst->tail == NULL) {
        return true;
    }
    return false;
}
void makeEmptyList(List* newList) {
    newList->head = NULL;
    newList->tail = NULL;
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
void allocationCheck(void* add) {
    if (add == NULL) {
        printf("Memory allocation failed");
        exit(1);
    }
}
void printLeafList(Tree tr)
{
    ListNode* curr;
    curr = tr.leafList.head;

    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}
void printParent(TreeNode* tr) {
    TreeNode* curr = tr->left;
    while (curr != NULL) {
        printf("%d ", curr->parent->data);
        curr = curr->left;
    }
}
void freeTree(Tree tr) {
    freeLst(tr.leafList);
    freeTreeRec(tr.root);
}
void freeTreeRec(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    else {
        freeTreeRec(root->left);
        freeTreeRec(root->right);
        free(root);
    }
}
void printTreeInorder(Tree tr) {
    printTreeInorderRec(tr.root);
    printf("\n");
}
void printTreeInorderRec(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    else {
        printTreeInorderRec(root->left);
        printf("%d ", root->data);
        printTreeInorderRec(root->right);
    }
}
void freeLst(List lst) {
    ListNode* current = lst.head;
    ListNode* toFree;

    while (current != NULL) {
        toFree = current;
        current = current->next;
        free(toFree);
    }
}