#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashtable.h"
#include "queue.h"

#define EMPTY_STRING ""
#define DEFINE_ARG "-D"
#define DIR_ARG "-I"
#define OUT_ARG "-O"
#define DELIM_ARGS "=" 
#define DEF_ARG_CODE 0
#define DEF_ARG_CODE_U 1
#define DIR_ARG_CODE 2
#define DIR_ARG_CODE_U 3
#define IN_FILE_CODE 4
#define OUT_FILE_CODE 5
#define OUT_FILE_CODE_U 6

void definition_arguments(char *str, hash_table *define)
{	
	char *ptr, *key, *value;

	ptr = strtok(str, DELIM_ARGS);
	key = malloc(strlen(ptr) * sizeof(char) + 1);
	strcpy(key, str);

	ptr = strtok(NULL, DELIM_ARGS);
	if (ptr == NULL)
	{
		value = malloc(sizeof(char));
		strcpy(value, EMPTY_STRING);
	}
	else
	{
		value = malloc(strlen(ptr) * sizeof(char) + 1);
		strcpy(value, ptr);
	}
	
	put(define, key, value);
}

int get_code(char *argv)
{
	if (strstr(argv, DEFINE_ARG) != NULL)
	{
		if (strlen(argv) > 2)
		{
			return DEF_ARG_CODE_U;			
		}
		else
		{
			return DEF_ARG_CODE;
		}
	}
	else if (strstr(argv, DIR_ARG) != NULL)
	{
		if (strlen(argv) > 2)
		{
			return DIR_ARG_CODE_U;			
		}
		else
		{
			return DIR_ARG_CODE;
		}
	}
	else if (strstr(argv, OUT_ARG) != NULL)
	{
		if (strlen(argv) > 2)
		{
			return OUT_FILE_CODE_U;			
		}
		else
		{
			return OUT_FILE_CODE;
		}
	}
	else {
		return IN_FILE_CODE;
	}
}

int get_count_directores(int argc, char **argv)
{
	int count = 0;

	for (int i = 1; i < argc; ++i)
	{
		if (strstr(argv[i], DIR_ARG) != NULL)
		{
			count++;
			if (strlen(argv[i]) == 2)
			{
				++i;			
			}
		}
	}

	return count;
}

void parse_arguments(
	int argc,
	char **argv,
	int directories_count,
	char ***directories,
	char **in_file,
	char **out_file,
	hash_table *define
)
{
	printf("%d\n", directories_count);
	char *substr;
	directories[0] = malloc(directories_count * sizeof(char *) + 1);
	int iterator_dir = 0;

	for (int i = 1; i < argc; ++i)
	{
		switch(get_code(argv[i]))
		{
			case DEF_ARG_CODE_U: ;
				substr = malloc((strlen(argv[i]) - 2) * sizeof(char) + 1);
				strcpy(substr, &argv[i][2]);
				definition_arguments(substr, define);
				free(substr);
				break;
			case DEF_ARG_CODE:
				definition_arguments(argv[i+1], define);
				++i;
				break;
			case DIR_ARG_CODE_U: ;
				substr = malloc((strlen(argv[i]) - 2) * sizeof(char) + 1);
				strcpy(substr, &argv[i][2]);
				directories[0][iterator_dir] = malloc(strlen(substr) * sizeof(char) + 1);
				strcpy(directories[0][iterator_dir], substr);
				iterator_dir++;
				free(substr);
				break;
			case DIR_ARG_CODE:
				directories[0][iterator_dir] = malloc(strlen(argv[i + 1]) * sizeof(char) + 1);
				strcpy(directories[0][iterator_dir], argv[i + 1]);
				++i;
				iterator_dir++;
				break;
			case IN_FILE_CODE:
				*in_file = malloc(strlen(argv[i]) * sizeof(char) + 1);
				strcpy(*in_file, argv[i]);
				break;
			case OUT_FILE_CODE_U: ;
				substr = malloc((strlen(argv[i]) - 2) * sizeof(char) + 1);
				strcpy(substr, &argv[i][2]);
				*out_file = malloc(strlen(substr) * sizeof(char) + 1);
				strcpy(*out_file, substr);
				free(substr);
				break;
			case OUT_FILE_CODE:
				*out_file = malloc(strlen(argv[i + 1]) * sizeof(char) + 1);
				strcpy(*out_file, argv[i+1]);
				++i;
				break;
		}	
	}
}

int main(int argc, char *argv[])
{
	hash_table *define = init_table(1024);
	char **directories = NULL;
	char *in_file = NULL, *out_file = NULL;
	int directories_count = get_count_directores(argc, argv);
	parse_arguments(argc, argv, directories_count, &directories, &in_file, &out_file, define);
	
	char* str[define->size];
	unsigned int i;
	list_keys(define, str, define->size);
	for(i = 0; i < define->size; i++)
	{
		printf("key: %s -> value: %s\n", str[i], (char *)get(define, str[i]));
	}
	if (directories != NULL)
	{
		for (int i = 0; i < directories_count; ++i)
		{
			printf("%s\n", directories[i]);
			free(directories[i]);
		}
		free(directories);
	}
	if (in_file != NULL)
	{
		printf("%s\n", in_file);
		free(in_file);
	}
	if (out_file != NULL)
	{
		printf("%s\n", out_file);
		free(out_file);
	}

	destroy(define);
	return 0;
}
