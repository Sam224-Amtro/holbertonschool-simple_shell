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
	char **args = malloc(TOK_BUFSIZE * sizeof(char *));
	char *token;
	char **tmp;
	int bufsize = TOK_BUFSIZE;
	int i = 0;

	if (!args)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, TOK_DELIM);
	while (token != NULL)
	{
		args[i++] = strdup(token);

		if (i >= bufsize)
		{
			bufsize += TOK_BUFSIZE;
			tmp = realloc(args, bufsize * sizeof(char *));
			if (!tmp)
			{
				perror("realloc");
				exit(EXIT_FAILURE);
			}
			args = tmp;
		}

		token = strtok(NULL, TOK_DELIM);
	}

	args[i] = NULL;
	return (args);
}
