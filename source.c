#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashtable.h"
#include "queue.h"
#include "defines.h"

void definition_arguments(char *str, hash_table *define)
{	
	char *ptr, *key, *value;

	ptr = strtok(str, DELIM_ARGS);
	key = malloc(strlen(ptr) * sizeof(char) + 1);
	strcpy(key, ptr);

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

int get_code_args(char *argv)
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

int get_code_directive(char *line)
{
	if (strstr(line, KEY_WORD_DEFINE) != NULL)
	{
		return DEFINE_CODE;
	}
	else
	{
		return IGNORE_CODE;
	}
}

int get_count_directores(int argc, char **argv)
{
	int count = 0;
	int i;
	for (i = 1; i < argc; ++i)
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
	char *substr;
	directories[0] = malloc(directories_count * sizeof(char *) + 1);
	int iterator_dir = 0;
	int i;
	for (i = 1; i < argc; ++i)
	{
		switch(get_code_args(argv[i]))
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

void add_define_map(char *line, hash_table *define)
{
	char *ptr, *key, *value;
	int count_aux = 1;
	ptr = strtok(line, DELIM_FILE);
	
	ptr = strtok(NULL, DELIM_FILE);
	key = malloc(strlen(ptr) * sizeof(char) + 1);
	strcpy(key, ptr);
	
	ptr = strtok(NULL, NEW_LINE);
	value = malloc(strlen(ptr) * sizeof(char) + 1);
	strcpy(value, ptr);

	put(define, key, value);
	strcpy(line, TERMINATOR);
}

char* check_substr_in_string(char *s, char *delim)
{
    char *target = NULL;
    char *start, *end;

    if ( start = strstr( s, delim ) )
    {
        start += strlen( delim );
        if ( end = strstr( start, delim) )
        {
            target = ( char * )malloc( end - start + 1 );
            memcpy( target, start, end - start );
            target[end - start] = '\0';
        }
    }

    return target;
}

void insertString(char* destination, int pos, char* seed)
{
    char * strC;

    strC = (char*)malloc(strlen(destination)+strlen(seed)+1);
    strncpy(strC,destination,pos);
    strC[pos] = '\0';
    strcat(strC,seed);
    strcat(strC,destination+pos);
    strcpy(destination,strC);
    free(strC);
}

void removeSubStr( char **str, const char *substr )
{
    size_t m1 = strlen(str[0]);
    size_t m2 = strlen(substr);

    if (!(m1 < m2))
    {
		char *p;
        for (p = str[0]; (p = strstr(p, substr)) != NULL; )
        {
            size_t n = m1 - ( p + m2 - str[0] );
            memmove(p, p + m2, n + 1);
        }
    }
}

void replace_aux(char **line, char *key, char *value)
{
	char *pch = strstr(line[0], key);
	if (pch != NULL)
	{
		insertString(pch, 0, value);
		removeSubStr(line, key);
		replace_aux(line, key, value);
	}
	
}

void replace_key_in_line(char *line, char *key, char *value)
{

	char *result = check_substr_in_string(line, "\"");
	if (result != NULL)
	{
		char *pch = strstr(result, key);
		if (pch != NULL)
		{
			removeSubStr(&line, result);
			char *pch_sec = strstr(line, key);
			if (pch_sec != NULL)
			{
				replace_aux(&line, key, value);
			}
			char *pch_third = strstr(line, "\"");
			insertString(pch_third, 1, result);
		}
		else
		{
			replace_aux(&line, key, value);
		}
		free(result);
	}
	else
	{
		replace_aux(&line, key, value);
	}
}

void replace_define(char *key, char*value, char ***lines_code, int count_lines)
{
	int i;
	for (i = 0; i < count_lines; ++i)
	{
		if (strstr(lines_code[0][i], KEY_WORD_UNDEFINE) != NULL
			&& strstr(lines_code[0][i], key) != NULL)
		{
			strcpy(lines_code[0][i], TERMINATOR);
			return;
		}
		replace_key_in_line(lines_code[0][i], key, value);
	}
}

void read_and_write(
	int directories_count,
	char **directories,
	char *in_file,
	char *out_file,
	hash_table *define
)
{
	FILE *fd_in, *fd_out;
	char buffer[BUFFER_LENGTH];

	if (in_file != NULL)
	{
		fd_in = fopen(in_file, "r");
		if (fd_in == NULL)
			exit(EXIT_FAILURE);
	}
	else
	{
		fd_in = stdin;
	}

	if (out_file != NULL)
	{
		fd_out = fopen(out_file, "w");
		if (fd_out == NULL)
			exit(EXIT_FAILURE);
	}
	else
	{
		fd_out = stdout;
	}

	char **lines_code = malloc(sizeof(char *) * 32);
	int i;
	for (i = 0; i < 32; ++i)
	{
		lines_code[i] = malloc(255 * sizeof(char));
	}

	int count_lines = 0;
	while(fgets(buffer, sizeof(buffer), fd_in) != NULL)
	{
		switch(get_code_directive(buffer))
		{
			case DEFINE_CODE: ;
				add_define_map(buffer, define);
				break;
		}
		if (strcmp(buffer, NEW_LINE) != 0)
		{
			strcpy(lines_code[count_lines], buffer);
			count_lines++;
		}
    }
	
	char* str[define->size];
	list_keys(define, str, define->size);
	for(i = 0; i < define->size; ++i)
	{
		replace_define(str[i], get(define, str[i]), &lines_code, count_lines);
	}

	for (i = 0; i < count_lines; ++i)
	{
		fputs(lines_code[i], fd_out);
	}

	int to_free = count_lines > 32 ? count_lines : 32;
	for (i = 0; i < to_free; ++i)
	{
		free(lines_code[i]);
	}
	free(lines_code);

    fclose(fd_in);
	fclose(fd_out);
}

int main(int argc, char *argv[])
{
	hash_table *define = init_table(1024);
	char **directories = NULL;
	char *in_file = NULL, *out_file = NULL;
	
	int directories_count = get_count_directores(argc, argv);
	parse_arguments(argc, argv, directories_count, &directories, &in_file, &out_file, define);

	read_and_write(directories_count, directories, in_file, out_file, define);

	if (directories != NULL)
	{
		int i;
		for (i = 0; i < directories_count; ++i)
		{
			free(directories[i]);
		}
		free(directories);
	}
	if (in_file != NULL)
	{
		free(in_file);
	}
	if (out_file != NULL)
	{
		free(out_file);
	}

	destroy(define);
	return 0;
}
