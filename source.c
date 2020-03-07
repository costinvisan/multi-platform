#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashtable.h"
#include "queue.h"

#define DEFINEARG "-D"

char** find_definition_arguments(int argc, char **argv)
{
	queue *q = create_queue();
	for (int i = 0; i < argc; ++i)
	{
		if (strstr(argv[i], DEFINEARG) != NULL)
		{
			if (strlen(argv[i]) > 2)
			{
				strcpy(argv[i], &argv[i][2]);
				enqueue(q, i);
			}
			else
			{
				enqueue(q, i + 1);
				i++;
			}
		}
	}

	int size = q->size;
	if (size == 0)
	{
		return NULL;
	}

	char **for_return = (char **)malloc(sizeof(char *) * size);
	
	int i = 0;
	QNode *node = dequeue(q);
	while (node != NULL)
	{
		for_return[i] = (char *)malloc(sizeof(char) * strlen(argv[node->key]));
		strcpy(for_return[i], argv[node->key]);
		node = dequeue(q);
		++i;
	}

	return for_return;
}

void parse_arguments(int argc, char **argv, hash_table *define)
{
	char symbols[][] = find_definition_arguments(argc, argv);
	int num_rows = sizeof(symbols) / sizeof(symbols[0]);
	for (int i = 0; i < num_rows; ++i)
	{
		printf("%s", symbols[i]);
	}
}

int main(int argc, char *argv[])
{
	hash_table *define = init_table(1024);
	parse_arguments(argc, argv, define);
	
	return 0;
}
