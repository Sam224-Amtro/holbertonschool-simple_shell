#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

/**
* free_args - Frees an array of strings
* @args: NULL-terminated array
*/
void free_args(char **args)
{
	int i = 0;

	if (!args)
		return;

	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

/**
* print_error - Displays a formatted error
* @prog_name: Program name
* @cmd: Command that failed
*/
void print_error(char *prog_name, char *cmd)
{
	fprintf(stderr, "%s: %s: command not found\n", prog_name, cmd);
}

/**
* remove_trailing_newline - Removes the '\n' character at the end of the string
* @str: String to clean
*/
void remove_trailing_newline(char *str)
{
	size_t len;

	if (!str)
		return;

	len = strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}
