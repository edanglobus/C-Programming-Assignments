#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

typedef struct treeNode
{
    char data;
    struct treeNode* left;
    struct treeNode* right;
}TreeNode;

typedef struct tree
{
    TreeNode* root;
}Tree;


#define SIZE 100
#define FALSE 0
#define TRUE 1

TreeNode* buildExpressionTreeRec(int* size, char* str);
TreeNode* createNewNode(char data, TreeNode* lefr, TreeNode* right);
double calcExpression(Tree tr);
double calcExpressionhrlprt(TreeNode* root);
bool buildExpressionTree(char* str, Tree* tr);
bool isValidInput(char str[]);
bool isDig(char c);
bool isOp(char c);
void allocationCheck(void* ptr);
void freeTree(Tree tr);
void freeTreeRec(TreeNode* root);

void main()
{
    char str[SIZE];

    Tree tr;

    double res;

    bool expressionOK;

    printf("Please enter the expression: ");
     gets(str);

    expressionOK = buildExpressionTree(str, &tr);

    if (expressionOK == true)
    {
        res = calcExpression(tr);
        printf("%s = %.2f", str, res);
    }
    else
        printf("The input expression is not valid\n");

    freeTree(tr);
}



bool buildExpressionTree(char* str, Tree* tr)
{
    bool validExpression;
    int stam, counter = 0;
    validExpression = isValidInput(str);
    if (!validExpression)
    {
        tr->root = NULL;
        return validExpression;
    }
    tr->root = buildExpressionTreeRec(&stam, str);
    return validExpression;
}
TreeNode* buildExpressionTreeRec(int* size, char* str)
{
    TreeNode* root, * left, * right;
    int leftsize, rightsize;
    if (isDig(str[0]) && str[1] == ')')
    {
        *size = 1;
        return root = createNewNode(str[0], NULL, NULL);
    }
    if (isDig(str[1]) && isOp(str[2]) && isDig(str[3]))
    {
        left = createNewNode(str[1], NULL, NULL);
        right = createNewNode(str[3], NULL, NULL);
        root = createNewNode(str[2], left, right);
        *size = 5;
        return root;
    }
    else if (isDig(str[1]) && isOp(str[2])) {
        left = createNewNode(str[1], NULL, NULL);
        right = buildExpressionTreeRec(&rightsize, str + 4);
        root = createNewNode(str[2], left, right);
        *size = rightsize + 4; 
        return root;
    }
    else 
    {
        left = buildExpressionTreeRec(&leftsize, str + 1); 
        right = buildExpressionTreeRec(&rightsize, str + (leftsize + 2)); 
        root = createNewNode(str[leftsize + 1], left, right);
        *size = leftsize + rightsize + 3;

        return root;
    }




}
TreeNode* createNewNode(char data, TreeNode* lefr, TreeNode* right)
{
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    allocationCheck(root);
    root->data = data;
    root->left = lefr;
    root->right = right;
    return root;
}
double calcExpression(Tree tr)
{
    return calcExpressionhrlprt(tr.root);
}
double calcExpressionhrlprt(TreeNode* root)
{
    if (isDig(root->data))
    {
        int a;
        a = root->data - '0';
        return a;
    }
    else if (isDig(root->left->data) && isDig(root->right->data)) // case of (dig op dig)
    {
        int left = root->left->data - '0', right = root->right->data - '0'; // we extract the integers from the chars in the tree.
        ;
        switch (root->data) // we operate 
        {
        case '+':
            return ((double)left) + right;
            break;

        case '-':
            return ((double)left) - right;
            break;

        case '/':
            return ((double)left) / right;
            break;

        case '*':
            return ((double)left) * right;
            break;

        case '%':
            return left % right;
            break;

        default:
            break;
        }

    }

    switch (root->data) 
    {
    case '+':
        return calcExpressionhrlprt(root->left) + calcExpressionhrlprt(root->right);
        break;
    case '-':
        return calcExpressionhrlprt(root->left) - calcExpressionhrlprt(root->right);
        break;

    case '/':
        return calcExpressionhrlprt(root->left) / calcExpressionhrlprt(root->right);
        break;

    case '*':
        return calcExpressionhrlprt(root->left) * calcExpressionhrlprt(root->right);
        break;

    case '%':
        return (int)calcExpressionhrlprt(root->left) % (int)calcExpressionhrlprt(root->right);
        break;

    default:
        break;
    }

}
bool isValidInput(char str[])
{
    int i, counter; 
    counter = 0;
    if (str[0] != '(') 
        return false;

    for (i = 0; i < strlen(str); i++)
    {
        if (isDig(str[i])) 
        {
            if (!(isOp(str[i + 1]) || str[i + 1] == ')'))
                return false;
        }
        else if (str[i] == ')') 
        {
            if (!(isOp(str[i + 1]) || str[i + 1] == ')' || str[i + 1] == '\0'))
                return false;
            counter--;
        }
        else if (str[i] == '(') 
        {
            if (!(isDig(str[i + 1]) || str[i + 1] == '(') || str[i + 2] == ')')
                return false;
            counter++;
        }
        else if (isOp(str[i])) 
        {
            if (!(isDig(str[i + 1]) || str[i + 1] == '('))
                return false;
        }
        if (counter < 0) 
            return false;
    }
    if (counter != 0)
        return false;
    return true; 
}
bool isDig(char c)
{
    return ('0' <= c && c <= '9') ? true : false;
}
bool isOp(char c)
{
    if (c == '-' || c == '+' || c == '*' || c == '/' || c == '%')
        return true;
    return false;
}
void allocationCheck(void* ptr)
{
    if (ptr == NULL) {
        printf("Memory allocation failed");
        exit(1);
    }
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