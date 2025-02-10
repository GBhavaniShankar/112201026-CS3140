#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    tokenId,
    tokenVal,
    tokenVar,
    tokenOp
} tokenType;

typedef struct Node
{
    tokenType tok;
    int val;
    char* op;
    char *var;
    struct Node *left;
    struct Node *right;
} Node;

Node *create_node(tokenType tok, int val, char* op, char *var, Node *left, Node *right);
void print_tree(Node* node);
void preorder(Node* node);

#endif // NODE_H
