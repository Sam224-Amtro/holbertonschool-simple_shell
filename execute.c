#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * execute_command - Exécute une commande avec ses arguments et environnement
 * @cmd: chemin de la commande
 * @args: tableau d'arguments (se termine par NULL)
 * @envp: tableau de variables d'environnement
 *
 * Return:
 *  - le code de retour de la commande exécutée (WEXITSTATUS),
 *  - ou -1 en cas d’erreur de fork.
 */
int execute_command(char *cmd, char **args, char **envp)
{
	pid_t pid = fork();

	if (pid < 0)
	{
		perror("fork failed");
		return (-1);
	}

	if (pid == 0)
	{
		execve(cmd, args, envp);
		perror("Erreur d'exécution");
		exit(EXIT_FAILURE);
	}
	else
	{
		int status;

		waitpid(pid, &status, 0);
		return (0);
	}
}
