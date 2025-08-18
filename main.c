#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - simple shell
 *
 * Return: Always 0
 */
int main(void)
{
	char *line;
	size_t len;
	ssize_t nread;

	line = NULL;
	len = 0;

	while (1)
	{
		pid_t pid;
		char *args[2];
		int status;

		printf("$ ");
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			free(line);
			printf("\n");
			exit(EXIT_SUCCESS);
		}

		if (line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		if (strcmp(line, "exit") == 0)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			free(line);
			exit(EXIT_FAILURE);
		}

		if (pid == 0)
		{
			args[0] = line;
			args[1] = NULL;

			if (execvp(args[0], args) == -1)
			{
				perror("execvp");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(&status);
		}
	}

	free(line);
	return (0);
}
