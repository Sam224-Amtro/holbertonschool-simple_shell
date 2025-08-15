#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

/**
* read_line - Reads a line from stdin
*
* Return: Pointer to the read line (must be freed by the caller),
* or NULL on EOF/error
*/
char *read_line(void)
{
	char *line = NULL;

	size_t bufsize = 0;
	ssize_t nread;

	nread = getline(&line, &bufsize, stdin);
	if (nread == -1)
	{
		free(line);
		return (NULL);
	}

	if (nread > 0 && line[nread - 1] == '\n')
		line[nread - 1] = '\0';

	return (line);
}

/**
* parse_line - Splits a line into tokens
* @line: The input string
*
* Return: Array of strings (tokens), NULL-terminated. Must be freed by caller.
*/
char **parse_line(char *line)
{
	int bufsize = 64, position = 0;

	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " \t\r\n");
	while (token != NULL)
	{
		tokens[position++] = token;

		if (position >= bufsize)
		{
			bufsize += 64;
			char **tmp = realloc(tokens, bufsize * sizeof(char *));

			if (!tmp)
			{
				perror("realloc");
				free(tokens);
				exit(EXIT_FAILURE);
			}
			tokens = tmp;
		}

		token = strtok(NULL, " \t\r\n");
	}
	tokens[position] = NULL;

	return (tokens);
}
