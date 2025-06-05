#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "pool_alloc.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct HashTableEntry {
  char *key;
  void *value;
  struct HashTableEntry *next;
} HashTableEntry;

typedef struct HashTable {
  HashTableEntry **buckets;
  size_t capacity;
  PoolAllocator *allocator;
  PoolAllocator entry_allocator;
  bool is_initialized;
} HashTable;

void hashtable_init(HashTable *table, size_t capacity,
                    PoolAllocator *allocator);
void hashtable_insert(HashTable *table, const char *key, void *value);
void *hashtable_get(HashTable *table, const char *key);
void hashtable_del(HashTable *table, const char *key);
void hashtable_free(HashTable *table);

#endif