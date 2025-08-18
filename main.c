#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * read_line - Lit une ligne depuis l'entrée standard
 *
 * Return: Pointeur vers la ligne lue (doit être free par l'appelant)
 */
char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

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

	return (line);
}

/**
 * execute_command - Exécute une commande simple
 * @line: La commande à exécuter
 */
void execute_command(char *line)
{
	pid_t pid;
	char *args[2];
	int status;

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

/**
 * main - Point d'entrée de la simple_shell
 *
 * Return: Toujours 0
 */
int main(void)
{
	char *line;

	while (1)
	{
		line = read_line();

		execute_command(line);

		free(line);
	}

	return (0);
}
