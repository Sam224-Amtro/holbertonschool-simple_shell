#include "main.h"

/**
 * main- Start of the program simple shell, who behave with less options, like
 * a shell.
 * @ac: Number of arguments passed in function
 * @av: Array which contain all the arguments passed in function
 * @env: Points to an array that contain all the environnment variables
 * available to the process
 * Return: -1 on failure, 0 on success
 */

int main(int ac, char **av, char **env)
{
	ssize_t check = 0;
	size_t size_buffer = 0;
	char *line = NULL, **_argv = NULL;
	(void)ac;

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
			printf("($) ");
		check = getline(&line, &size_buffer, stdin);
		if (check == -1)
		{
			free_arguments(_argv, line);
			break;
		}
		line[(strlen(line) - 1)] = '\0';
		if (line == NULL)
			printf("%s: 1: %s: not found\n", av[0], _argv[0]);
		else if (line != NULL)
		{
			_argv = argv_for_shell(line);
			if ((executing_program(line, _argv, env)) == 11)
				printf("%s: 1: %s: not found\n", av[0], _argv[0]);
		}
		free_arguments(_argv, line);
		line = NULL;
		_argv = NULL;
	}
	return (0);
}
