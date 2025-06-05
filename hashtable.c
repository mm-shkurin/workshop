#include "hashtable.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>  

#define FNV_OFFSET_BASIS 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

static size_t fnv1a_hash(const char *key) {
  size_t hash = FNV_OFFSET_BASIS;
  while (*key) {
    hash ^= (size_t)(*key++);
    hash *= FNV_PRIME;
  }
  return hash;
}

void hashtable_init(HashTable *table, size_t capacity,
                    PoolAllocator *allocator) {
  assert(table != NULL);
  assert(capacity > 0);
  assert(allocator != NULL);

  table->allocator = allocator;
  table->capacity = capacity;

  table->buckets =
      (HashTableEntry **)calloc(capacity, sizeof(HashTableEntry *));
  if (table->buckets == NULL) {
    fprintf(stderr, "Error: Failed to allocate buckets\n");
    return;
  }

  size_t entry_size = sizeof(HashTableEntry);
  size_t entry_count = capacity * 2;

  void *entries_memory = pool_allocator_allocate(allocator);
  if (entries_memory == NULL) {
    fprintf(stderr, "Error: Failed to allocate entries memory\n");
    free(table->buckets);
    table->buckets = NULL;
    return;
  }

  pool_allocator_init(&table->entry_allocator, entries_memory, entry_size,
                      entry_count);
  table->is_initialized = true;
}

void hashtable_insert(HashTable *table, const char *key, void *value) {
  if (table == NULL || !table->is_initialized || key == NULL) {
    fprintf(stderr, "Error: Invalid arguments to hashtable_insert\n");
    return;
  }

  size_t hash = fnv1a_hash(key);
  size_t index = hash % table->capacity;

  HashTableEntry *entry = table->buckets[index];
  while (entry != NULL) {
    if (strcmp(entry->key, key) == 0) {
      entry->value = value;
      return;
    }
    entry = entry->next;
  }

  HashTableEntry *new_entry =
      (HashTableEntry *)pool_allocator_allocate(&table->entry_allocator);
  if (new_entry == NULL) {
    fprintf(stderr, "Error: Failed to allocate new entry. Pool may be full.\n");
    return;
  }

  size_t key_len = strlen(key) + 1;
  new_entry->key = (char *)pool_allocator_allocate(table->allocator);
  if (new_entry->key == NULL) {
    fprintf(stderr, "Error: Failed to allocate key memory\n");
    pool_allocator_free(&table->entry_allocator, new_entry);
    return;
  }

  strncpy(new_entry->key, key, key_len);
  new_entry->value = value;
  new_entry->next = table->buckets[index];
  table->buckets[index] = new_entry;
}

void *hashtable_get(HashTable *table, const char *key) {
  if (table == NULL || !table->is_initialized || key == NULL) {
    fprintf(stderr, "Error: Invalid arguments to hashtable_get\n");
    return NULL;
  }

  size_t hash = fnv1a_hash(key);
  size_t index = hash % table->capacity;

  HashTableEntry *entry = table->buckets[index];
  while (entry != NULL) {
    if (strcmp(entry->key, key) == 0) {
      return entry->value;
    }
    entry = entry->next;
  }

  return NULL;
}

void hashtable_del(HashTable *table, const char *key) {
  if (table == NULL || !table->is_initialized || key == NULL) {
    fprintf(stderr, "Error: Invalid arguments to hashtable_del\n");
    return;
  }

  size_t hash = fnv1a_hash(key);
  size_t index = hash % table->capacity;

  HashTableEntry **entry_ptr = &table->buckets[index];
  while (*entry_ptr != NULL) {
    HashTableEntry *entry = *entry_ptr;
    if (strcmp(entry->key, key) == 0) {
      *entry_ptr = entry->next;
      pool_allocator_free(table->allocator, entry->key);
      pool_allocator_free(&table->entry_allocator, entry);
      return;
    }
    entry_ptr = &entry->next;
  }
}

void hashtable_free(HashTable *table) {
  if (table == NULL || !table->is_initialized) {
    return;
  }
  for (size_t i = 0; i < table->capacity; i++) {
    HashTableEntry *entry = table->buckets[i];
    while (entry != NULL) {
      HashTableEntry *next = entry->next;
      pool_allocator_free(table->allocator, entry->key);
      pool_allocator_free(&table->entry_allocator, entry);
      entry = next;
    }
    table->buckets[i] = NULL;
  }

  free(table->buckets); 
  table->buckets = NULL;
  table->is_initialized = false;
}