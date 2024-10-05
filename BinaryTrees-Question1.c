#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>


typedef struct treeNode
{
    unsigned int data;
    struct treeNode* left;
    struct treeNode* right;
}TreeNode;

typedef struct tree
{      
  TreeNode* root;
}Tree;

void allocationCheck(void* add);
void printTreeInorder(Tree tr);
void printTreeInOrderRec(TreeNode* root);
TreeNode* BuildTreeFromArrayRec(int arr[], int size);
Tree BuildTreeFromArray(int arr[], int size);
void freeTree(Tree tr);
void freeTreeRec(TreeNode* root);

#define SIZE 100
#define NOT_NODE -1



void main()

{

    int size, i;

    int arr[SIZE];

    Tree tr;



    printf("Please enter the number of items: ");

    scanf("%d", &size);

    for (i = 0; i < size; i++)

        scanf("%d", &arr[i]);



    tr = BuildTreeFromArray(arr, size);

    printf("The tree in inorder (LDR) format:\n");

    printTreeInorder(tr); //Print the tree in-order (LDR)

    freeTree(tr);

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
TreeNode* createTreeNode(int num) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    allocationCheck(node);

    node->data = num;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void printTreeInOrderRec(TreeNode* root) {
    if (root == NULL) {
        return;
    }

    printTreeInOrderRec(root->left);

    printf("%d ", root->data);

    printTreeInOrderRec(root->right);
    return;
}
void printTreeInorder(Tree tr) {
    if (tr.root != NULL) {
        printTreeInOrderRec(tr.root);
    }
    return;
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