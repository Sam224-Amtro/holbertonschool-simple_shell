#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include "main.h"

/**
* main - Boucle principale du shell
*
* Return: Always 0
*/

extern char **environ;

int main(void)
{
	char *line = NULL;

	size_t len = 0;
	ssize_t nread;
	pid_t pid;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");

	nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			break;
		}

		line[strcspn(line, "\n")] = '\0';
		if (line[0] == '\0')
			continue;

		pid = fork();
		if (pid == 0)
		{
			char *argv_child[] = { line, NULL };

			execve(line, argv_child, environ);

			fprintf(stderr, "simple_shell: %s: not found\n", line);
			_exit(127);
		}
		else if (pid > 0)
		{
			wait(NULL);
		}
		else
		{
			perror("fork");
		}

	free(line);
	return (0);
	}
}
