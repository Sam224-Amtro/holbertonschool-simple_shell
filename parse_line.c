#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

/**
 * parse_line - Découpe une ligne en arguments (tokens)
 * @line: chaîne entrée par l'utilisateur
 *
 * Return: tableau de chaînes terminé par NULL
 */
char **parse_line(char *line)
{
	char *token;
	char **args = NULL;
	size_t bufsize = 0, i = 0;

	if (!line)
		return (NULL);

	bufsize = 64;
	args = malloc(sizeof(char *) * bufsize);
	if (!args)
		return (NULL);

	token = strtok(line, " \t");
	while (token != NULL)
	{
		args[i] = strdup(token);
		i++;

		if (i >= bufsize)
		{
			bufsize *= 2;
			args = realloc(args, sizeof(char *) * bufsize);
			if (!args)
				return (NULL);
		}
		token = strtok(NULL, " \t");
	}
	args[i] = NULL;
	return (args);
}
