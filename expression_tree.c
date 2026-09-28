#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

struct Node
{
    char data;
    struct Node *left;
    struct Node *right;
};

struct Node *treeStack[MAX];
int treeTop = -1;

int valueStack[MAX];
int valueTop = -1;

int postfixPush = 0;
int postfixPop = 0;
int postfixCompute = 0;

int treeOperand = 0;
int treeCompute = 0;

struct Node *createNode(char data)
{
    struct Node *newNode;

    newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

void pushTree(struct Node *node)
{
    treeStack[++treeTop] = node;
}

struct Node *popTree()
{
    return treeStack[treeTop--];
}


void pushValue(int value)
{
    valueStack[++valueTop] = value;
    postfixPush++;
}

int popValue()
{
    postfixPop++;
    return valueStack[valueTop--];
}

int calculate(int a, int b, char op)
{
    switch (op)
    {
        case '+':
            return a + b;

        case '-':
            return a - b;

        case '*':
            return a * b;

        case '/':
            return a / b;
    }

    return 0;
}

struct Node *buildExpressionTree(char postfix[])
{
    int i;
    char ch;
    struct Node *node;

    treeTop = -1;

    for (i = 0; postfix[i] != '\0'; i++)
    {
        ch = postfix[i];

        if (ch == ' ')
            continue;

        node = createNode(ch);

        if (isdigit(ch))
        {
            pushTree(node);
        }
        else
        {
            node->right = popTree();
            node->left = popTree();

            pushTree(node);
        }
    }

    return popTree();
}

void inorder(struct Node *root)
{
    if (root != NULL)
    {
        if (!isdigit(root->data))
            printf("(");

        inorder(root->left);

        printf("%c", root->data);

        inorder(root->right);

        if (!isdigit(root->data))
            printf(")");
    }
}

void preorder(struct Node *root)
{
    if (root != NULL)
    {
        printf("%c ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct Node *root)
{
    if (root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%c ", root->data);
    }
}

void printTree(struct Node *root, int space)
{
    int i;

    if (root == NULL)
        return;

    space += 5;

    printTree(root->right, space);

    printf("\n");

    for (i = 5; i < space; i++)
        printf(" ");

    printf("%c\n", root->data);

    printTree(root->left, space);
}

int evaluatePostfix(char postfix[])
{
    int i;
    int a, b, result;
    char ch;

    valueTop = -1;

    printf("\n----------------------------------------\n");
    printf("STACK-BASED POSTFIX EVALUATION\n");
    printf("----------------------------------------\n");

    for (i = 0; postfix[i] != '\0'; i++)
    {
        ch = postfix[i];

        if (ch == ' ')
            continue;

        if (isdigit(ch))
        {
            result = ch - '0';

            pushValue(result);

            printf("Read %c -> Push %d\n", ch, result);
        }
        else
        {
            b = popValue();
            a = popValue();

            result = calculate(a, b, ch);

            postfixCompute++;

            pushValue(result);

            printf("Read %c -> Pop %d, %d -> %d %c %d = %d\n",
                   ch, a, b, a, ch, b, result);
        }
    }

    return popValue();
}

int evaluateTree(struct Node *root)
{
    int leftValue;
    int rightValue;
    int result;

    if (root == NULL)
        return 0;

    if (isdigit(root->data))
    {
        treeOperand++;

        return root->data - '0';
    }

    leftValue = evaluateTree(root->left);

    rightValue = evaluateTree(root->right);

    result = calculate(leftValue, rightValue, root->data);

    treeCompute++;

    printf("Tree node %c -> %d %c %d = %d\n",
           root->data,
           leftValue,
           root->data,
           rightValue,
           result);

    return result;
}

void freeTree(struct Node *root)
{
    if (root != NULL)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main()
{
    char postfix[] = "8 3 2 * + 6 2 / -";

    struct Node *root;

    int postfixResult;
    int treeResult;

    printf("============================================\n");
    printf(" POSTFIX EXPRESSION: EXPRESSION TREE\n");
    printf(" STACK EVALUATION & COMPARISON\n");
    printf("============================================\n");

    printf("\nPostfix Expression:\n");
    printf("%s\n", postfix);

    root = buildExpressionTree(postfix);

    printf("\nExpression Tree:\n");
    printf("----------------------------------------\n");
    printTree(root, 0);

    printf("\nTree Traversals:\n");
    printf("----------------------------------------\n");

    printf("Inorder   : ");
    inorder(root);

    printf("\nPreorder  : ");
    preorder(root);

    printf("\nPostorder : ");
    postorder(root);

    printf("\n");

    postfixResult = evaluatePostfix(postfix);

    printf("\nPostfix Evaluation Result = %d\n",
           postfixResult);

    printf("\n----------------------------------------\n");
    printf("EXPRESSION TREE EVALUATION\n");
    printf("----------------------------------------\n");

    treeResult = evaluateTree(root);

    printf("\nExpression Tree Evaluation Result = %d\n",
           treeResult);

    printf("\n============================================\n");
    printf(" OPERATION COUNT SUMMARY\n");
    printf("============================================\n");

    printf("\nStack-Based Postfix Evaluation:\n");
    printf("Push operations     : %d\n", postfixPush);
    printf("Pop operations      : %d\n", postfixPop);
    printf("Arithmetic operations: %d\n", postfixCompute);

    printf("\nExpression Tree Evaluation:\n");
    printf("Operand visits      : %d\n", treeOperand);
    printf("Arithmetic operations: %d\n", treeCompute);

    /* Final Comparison */
    printf("\n============================================\n");
    printf(" COMPARISON\n");
    printf("============================================\n");

    printf("Postfix result       : %d\n", postfixResult);
    printf("Expression Tree result: %d\n", treeResult);

    if (postfixResult == treeResult)
        printf("Both methods produce the same result.\n");

    printf("\nTime Complexity:\n");
    printf("Postfix Evaluation   : O(n)\n");
    printf("Expression Tree      : O(n)\n");

    printf("\nSpace Complexity:\n");
    printf("Postfix Evaluation   : O(n)\n");
    printf("Expression Tree      : O(n)\n");

    printf("\nThe Expression Tree provides additional\n");
    printf("structural information about the relationship\n");
    printf("between operands and operators.\n");

    freeTree(root);

    return 0;
}
