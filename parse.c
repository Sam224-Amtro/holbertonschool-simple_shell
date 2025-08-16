#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * parse_line - Splits the command line into tokens (words)
 * @line: line entered by the user
 *
 * Return: array of strings terminated by NULL (to be freed after use)
 */
char **parse_line(char *line)
{
	char **args;
	char *token;
	char **tmp;
	int bufsize = 64;
	int i = 0;

	args = malloc(bufsize * sizeof(char *));
	if (!args)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, "\t\r\n");
	while (token != NULL)
	{
		args[i++] = strdup(token);

		if (i >= bufsize)
		{
			bufsize += 64;
			tmp = realloc(args, bufsize * sizeof(char *));
			if (!tmp)
			{
				perror("realloc");
				exit(EXIT_FAILURE);
			}
			args = tmp;
		}

		token = strtok(NULL, "\t\r\n");
	}

	args[i] = NULL;
	return (args);
}
