#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <stdlib.h>
#include <string.h>

typedef struct hash_node {
	struct hash_node* next;
	void *value;
	char *key;
} hash_node;

typedef struct hash_table {
	int capacity;
	int size;
	struct hash_node** storage;
} hash_table;

unsigned int hash_code(char* key);

hash_table* init_table(unsigned int capacity);

void* put(hash_table* hash, char* key, void* value);

void* get(hash_table* hash, char* key);

void* erase(hash_table* hash, char* key);

void list_values(hash_table* hasht, void** v, size_t len);

void list_keys(hash_table* hasht, char** k, size_t len);

void clear(hash_table* hasht);

void destroy(hash_table* hasht);

#endif // HASHTABLE_H_
