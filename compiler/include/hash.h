#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 100

typedef struct HashNode
{
    char *key;
    int value;
    bool is_defined;
    struct HashNode *next;
} HashNode;

extern HashNode *hash_table[TABLE_SIZE];

unsigned int hash(const char *str); // Hash function (djb2)
void insert(const char *key, int value, bool is_defined);
HashNode *search(const char *key);
void freeTable();
void printTable();
void update(const char *key, int new_value);

#endif // HASH_H
