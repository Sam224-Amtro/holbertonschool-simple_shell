#include "main.h"

/**
 * parse_line - Découpe une ligne en tokens (arguments)
 * @line: ligne saisie par l'utilisateur
 *
 * Cette fonction utilise strtok pour découper la chaîne `line`
 * en plusieurs mots séparés par des espaces, tabulations ou retours
 * à la ligne. Les arguments sont stockés dans un tableau dynamique
 * qui est réalloué si nécessaire.
 *
 * Return: tableau de pointeurs vers les arguments (se termine par NULL)
 */
char **parse_line(char *line)
{
	int bufsize = 64, i = 0;

	char **args = malloc(sizeof(char *) * bufsize);

	char *token;

	if (!args)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " \t\r\n");
	while (token)
	{
		args[i++] = token;

		if (i >= bufsize)
		{
			int old = bufsize;

			bufsize += 64;
			args = _realloc_args(args, old, bufsize);
			if (!args)
			{
				perror("realloc");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, " \t\r\n");
	}
	args[i] = NULL;
	return (args);
}
