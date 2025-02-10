#include "hash.h"
#include "node.h"
#include <stdbool.h>

HashNode *hash_table[TABLE_SIZE] = {NULL};

Node *create_node(tokenType tok, int val, char *op, char *var, Node *left, Node *right)
{
    Node *node = malloc(sizeof(Node));
    node->tok = tok;
    node->val = val;
    node->op = op;
    node->var = var;
    node->left = left;
    node->right = right;
    return node;
}

unsigned int hash(const char *str)
{
    unsigned int hash = 5381;
    int c;
    while ((c = *str++))
    {
        hash = (hash << 5) + c;
    }
    return hash % TABLE_SIZE;
}

void insert(const char *key, int value, bool is_defined)
{
    unsigned int index = hash(key);

    HashNode *newNode = (HashNode *)malloc(sizeof(HashNode));
    if (!newNode)
    {
        fprintf(stderr, "Memory allocation failed for HashNode\n");
        exit(EXIT_FAILURE);
    }

    newNode->key = strdup(key);
    if (!newNode->key)
    {
        fprintf(stderr, "Memory allocation failed for key\n");
        free(newNode);
        exit(EXIT_FAILURE);
    }

    newNode->is_defined = is_defined;
    newNode->value = is_defined ? value : 0;
    newNode->next = hash_table[index];
    hash_table[index] = newNode;
}

HashNode *search(const char *key)
{
    unsigned int index = hash(key);
    HashNode *entry = hash_table[index];
    while (entry)
    {
        if (strcmp(entry->key, key) == 0)
        {
            return entry;
        }
        entry = entry->next;
    }
    return NULL;
}

void freeTable()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        HashNode *entry = hash_table[i];
        while (entry)
        {
            HashNode *temp = entry;
            entry = entry->next;
            free(temp->key);
            free(temp);
        }
    }
}

void update(const char *key, int new_value)
{
    HashNode *entry = search(key);
    if (entry)
    {
        entry->value = new_value;
        entry->is_defined = true; // Mark it as defined if it wasn't already
    }
    else
    {
        printf("Error: Uninitialized variable '%s' is used in the program...!\n", key);
    }
}

void printTable()
{
    printf("\n=============================\n");
    printf("      Symbol Table\n");
    printf("=============================\n");
    printf("| %-15s | %-10s |\n", "Variable", "Value");
    printf("=============================\n");

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        HashNode *entry = hash_table[i];
        while (entry)
        {
            printf("| %-15s | %-10d |\n", entry->key, entry->value);
            entry = entry->next;
        }
    }

    printf("=============================\n");
}

int height(Node *tree)
{
    if (!tree)
        return 0;
    int hl = height(tree->left), hr = height(tree->right);
    return (hl > hr ? hl : hr) + 1;
}

void print_level(Node *node, int cur, int target, int maxH)
{
    if (cur > target)
    {
        fprintf(stderr, "Error\n");
        return;
    }
    if (cur < target)
    {
        print_level(node ? node->left : NULL, cur + 1, target, maxH);
        print_level(node ? node->right : NULL, cur + 1, target, maxH);
        return;
    }
    int pad = 1;
    for (int i = target; i < maxH - 1; i++)
        pad = pad * 2 + 1;
    for (int i = 0; i < (pad + 1) / 2; i++)
        printf("   ");
    for (int i = (pad + 1) / 2; i < pad; i++)
        printf("___");

    if (node != NULL)
    {
        switch (node->tok)
        {
        case tokenVar:
            printf("%3s", node->var);
            break;
        case tokenId:
            printf("%3s", node->var);
            break;
        case tokenVal:
            printf("%3d", node->val);
            break;
        case tokenOp:
            printf("%3s", node->var);
            break;
        default:
            break;
        }
    }
    else
    {
        printf("   ");
    }

    for (int i = (pad + 1) / 2; i < pad; i++)
        printf("___");
    for (int i = 0; i < (pad + 1) / 2; i++)
        printf("   ");
    printf("   ");
}

void print_tree(Node *root)
{
    int h = height(root);
    for (int lvl = 0; lvl < h; lvl++)
    {
        print_level(root, 0, lvl, h);
        printf("\n");
    }
}

void preorder(Node *node)
{
    if (node != NULL)
    {
        switch (node->tok)
        {
        case tokenVar:
            printf("%s ", node->var);
            break;
        case tokenId:
            printf("%s ", node->var);
            break;
        case tokenVal:
            printf("%d ", node->val);
            break;
        case tokenOp:
            printf("%s ", node->var);
            break;
        default:
            break;
        }
        preorder(node->left);
        preorder(node->right);
    }
    else
    {
        return;
    }
}
