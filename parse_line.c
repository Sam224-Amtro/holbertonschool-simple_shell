#include "main.h"

/**
 * parse_line - Découpe une ligne en arguments (tokens)
 * @line: chaîne entrée par l’utilisateur
 *
 * Return: tableau de pointeurs vers les arguments, ou NULL en cas d’erreur
 */
char **parse_line(char *line)
{
	char *token;
	char **args;
	int bufsize = 64;
	int i = 0;

	args = malloc(sizeof(char *) * bufsize);
	if (!args)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " \t\r\n");
	while (token != NULL)
	{
		args[i++] = token;

		if (i >= bufsize)
		{
			bufsize += 64;
			args = _realloc_args(args, i, bufsize);
			if (!args)
			{
				perror("realloc");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, "\t\r\n");
	}
	args[i] = NULL;
	return (args);
}
