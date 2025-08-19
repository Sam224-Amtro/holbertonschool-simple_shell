#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

extern char **environ;

/**
* execute_command - Crée un processus pour exécuter une commande
* @command: chemin absolu de la commande à exécuter
* @args: tableau d'arguments à passer à execve
*
* Return: code de retour du processus exécuté
* (0 si succès, autre valeur si erreur)
*/
int execute_command(char *command, char **args)
{
	int status;

	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}

	if (pid == 0)
	{
		execve(command, args, environ);

		// Si execve échoue :
		fprintf(stderr, "simple_shell: %s: not found\n", command);
		exit(127);
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid");
			return (-1);
		}

		if (WIFEXITED(status))
			return WEXITSTATUS(status);

		if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status));

		return (-1);
	}
}
