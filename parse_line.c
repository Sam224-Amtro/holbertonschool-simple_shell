#include "main.h"

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
