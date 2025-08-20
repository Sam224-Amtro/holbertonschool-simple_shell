#include "main.h"

int handle_builtin(char **args, char **envp, char *line)
{
	int i;

	if (!args || !args[0])
		return (0);

	if (strcmp(args[0], "exit") == 0)
	{
		free_args(args);
		free(line);
		exit(0);
	}

	if (strcmp(args[0], "env") == 0)
	{
		for (i = 0; envp && envp[i]; i++)
			printf("%s\n", envp[i]);
		return (1);
	}

	return (0);
}
