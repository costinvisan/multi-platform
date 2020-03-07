#include "hashtable.h"

unsigned int hash_code(char* key)
{
	unsigned int h = 5381;
	while(*(key++))
		h = ((h << 5) + h) + (*key);
	return h;
}

hash_table* init_table(unsigned int capacity)
{
	hash_table* hash = malloc(sizeof(hash_table));
	hash->storage = malloc(capacity * sizeof(hash_node*));
	hash->capacity = capacity;
	hash->size = 0;
	for (unsigned int i = 0; i < capacity; ++i)
	{
		hash->storage[i] = NULL;
	}
	return hash;
}

void* put(hash_table* hash, char* key, void* value)
{
	if (value == NULL)
	{
		return NULL;
	}

	unsigned int key_hashed = hash_code(key) % hash->capacity;
	hash_node* node = hash->storage[key_hashed];
	
	while (node != NULL)
	{
		if (!strcmp(node->key, key))
		{
			void* for_return = node->value;
			node->value = value;
			return for_return;
		}
		node = node->next;
	}

	node = malloc(sizeof(hash_node) + strlen(key) + 1);
	strcpy(node->key, key);
	node->value = value;

	node->next = hash->storage[key_hashed];
	hash->storage[key_hashed] = node;
	hash->size++;

	return NULL;
}

void* get(hash_table* hash, char* key)
{
	unsigned int key_hashed = hash_code(key) % hash->capacity;
	hash_node* node = hash->storage[key_hashed];

	while (node != NULL)
	{
		if (!strcmp(node->key, key))
		{
			return node->value;
		}
		node = node->next;
	}
	
	return NULL;
}

void* erase(hash_table* hash, char* key)
{
	unsigned int key_hashed = hash_code(key) % hash->capacity;
	hash_node* node = hash->storage[key_hashed];
	hash_node* prev = NULL;

	while (node != NULL)
	{
		if (!strcmp(node->key, key))
		{
			void* for_return = node->value;
			if (prev != NULL)
			{
				prev->next = node->next;
			}
			else 
			{
				hash->storage[key_hashed] = node->next;
			}
			free(node);
			node = NULL;
			hash->size--;
			return for_return;
		}
		prev = node;
		node = node->next;
	}
	return NULL;
}

