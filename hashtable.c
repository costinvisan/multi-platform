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
	node->key = key;
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
			free(node->key);
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

void list_keys(hash_table* hasht, char** k, size_t len)
{
	if(len < hasht->size)
		return;
	int ki = 0;
	int i = hasht->capacity;
	while(--i >= 0)
	{
		hash_node* e = hasht->storage[i];
		while(e)
		{
			k[ki++] = e->key;
			e = e->next;
		}
	}
}

void list_values(hash_table* hasht, void** v, size_t len)
{
	if(len < hasht->size)
		return;
	int vi = 0;
	int i = hasht->capacity;
	while(--i >= 0)
	{
		hash_node* e = hasht->storage[i];
		while(e)
		{
			v[vi++] = e->value;
			e = e->next;
		}
	}
}

void clear(hash_table* hasht)
{
	char* str[hasht->size];
	unsigned int i;
	list_keys(hasht, str, hasht->size);
	int size = hasht->size;
	for(i = 0; i < size; i++)
	{
		free(erase(hasht, str[i]));
	}
}

void destroy(hash_table* hasht)
{
	clear(hasht);
	free(hasht->storage);
	free(hasht);
}

