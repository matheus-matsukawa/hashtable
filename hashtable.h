#ifndef HASH_H_
#define HASH_H_

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 1000000

typedef struct
{
  char *key;
  char *value;
} entry_t;

typedef struct
{
  entry_t **entries;
} ht_t;

unsigned int hash(const char *key);

entry_t *ht_pair(const char *key, const char *value);

ht_t *ht_create(void);

void ht_set(ht_t *hashtable, const char *key, const char *value);

char *ht_get(ht_t *hashtable, const char *key);

void ht_del(ht_t *hashtable, const char *key);

void ht_dump(ht_t *hashtable);

#endif