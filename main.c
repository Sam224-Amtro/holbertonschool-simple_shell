#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - Entry point of the simple shell
 *
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	while (1)
	{
		printf("$ "); /* Prompt */
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

		pid_t pid = fork();
		if (pid == -1)
		{
			perror("fork");
			free(line);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			char *args[] = {line, NULL};
			if (execvp(args[0], args) == -1)
			{
				perror("execvp");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(NULL);
		}
	}

	free(line);
	return (0);
}
