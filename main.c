#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * main - Boucle principale du shell
 *
 * Return: Always 0
 */

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	char *args[64];
	int i = 0;

	while (1)
	{
		printf("$ ");
		fflush(stdout);

		if (getline(&line, &len, stdin) == -1)
			break;

		line[strcspn(line, "\n")] = 0;

		if (strcmp(line, "exit") == 0)
			break;

		args[i] = strtok(line, " ");
		while (args[i] != NULL && i < 63)
		{
			i++;
			args[i] = strtok(NULL, " ");
		}

		args[i] = NULL;

		pid_t pid = fork();

		if (pid == 0)
		{
			if (execve(args[0], args, NULL) == -1)
			{
				perror("Erreur");
				_exit(1);
			}
		}
		else if (pid > 0)
		{
			wait(NULL);
		}
		else
		{
			perror("fork");
		}
	}

	free(line);
	return 0;
}
