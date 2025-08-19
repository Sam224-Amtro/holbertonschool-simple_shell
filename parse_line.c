#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
* parse_line - Divise la ligne de commande en tokens (mots)
* @line: ligne saisie par l'utilisateur
*
* Return: tableau de chaînes terminées par NULL (à libérer après utilisation)
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

	token = strtok(line, " \t\r\n");
	while (token != NULL)
	{
		args[i] = strdup(token);
		if (!args[i])
		{
			perror("strdup");
			exit(EXIT_FAILURE);
		}
		i++;

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

		token = strtok(NULL, " \t\r\n");
	}

	args[i] = NULL;
	return (args);
}
