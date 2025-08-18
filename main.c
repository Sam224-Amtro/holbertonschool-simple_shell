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
	char buffer[1024];
	char *args[64];
	int i = 0;

	while (1)
	{
		printf("$ ");
		fgets(buffer, 1024, stdin);
		buffer[strcspn(buffer, "\n")] = 0;

		if (strcmp(buffer, "exit") == 0)
			break;

		args[i] = strtok(buffer, " ");

		while (args[i] != NULL)
		{
			i++;
			args[i] = strtok(NULL, " ");
		}

		pid_t pid = fork();

		if (pid == 0)
		{
			if (execvp(args[0], args) == -1)
			{
				perror("Erreur");
			}
			exit(0);
		} else if (pid > 0)
		{
			wait(NULL);
		} else
		{
			perror("fork");
		}
	}

	return (0);
}
