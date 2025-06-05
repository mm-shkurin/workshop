#include "hashtable.h"
#include "pool_alloc.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_MEMORY_SIZE (4 * 1024 * 1024)
#define BLOCK_SIZE 256
#define BLOCK_COUNT (TEST_MEMORY_SIZE / BLOCK_SIZE)

int main() {
  printf("Running HashTable tests...\n");

  char *test_memory = malloc(TEST_MEMORY_SIZE);
  assert(test_memory != NULL && "Failed to allocate test memory");

  PoolAllocator main_allocator;
  pool_allocator_init(&main_allocator, test_memory, BLOCK_SIZE, BLOCK_COUNT);

  printf("Testing HashTable with small dataset...\n");
  HashTable table;
  hashtable_init(&table, 32, &main_allocator);

  int value1 = 42;
  float value2 = 3.14f;
  char value3[] = "test string";

  hashtable_insert(&table, "key1", &value1);
  hashtable_insert(&table, "key2", &value2);
  hashtable_insert(&table, "key3", value3);

  assert(*(int *)hashtable_get(&table, "key1") == value1);
  assert(*(float *)hashtable_get(&table, "key2") == value2);
  assert(strcmp((char *)hashtable_get(&table, "key3"), value3) == 0);

  int new_value1 = 100;
  hashtable_insert(&table, "key1", &new_value1);
  assert(*(int *)hashtable_get(&table, "key1") == new_value1);

  hashtable_del(&table, "key2");
  assert(hashtable_get(&table, "key2") == NULL);
  assert(hashtable_get(&table, "nonexistent") == NULL);

  printf("Testing with moderate number of items (50)...\n");
  for (int i = 0; i < 50; i++) {
    char key[20];
    sprintf(key, "item%d", i);
    int *value = malloc(sizeof(int));
    assert(value != NULL);
    *value = i;
    hashtable_insert(&table, key, value);
  }

  for (int i = 0; i < 50; i++) {
    char key[20];
    sprintf(key, "item%d", i);
    int *value = (int *)hashtable_get(&table, key);
    assert(value != NULL && *value == i);
    hashtable_del(&table, key);  
    free(value); 
    }

  printf("Cleaning up...\n");
  hashtable_free(&table);
  free(test_memory);

  printf("All HashTable tests passed!\n");
  return 0;
}