#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * execute_command - exécute une commande avec arguments et environnement
 * @cmd: la commande à exécuter
 * @args: tableau d'arguments
 * @envp: tableau des variables d'environnement
 *
 * Crée un processus fils et exécute la commande. Affiche une erreur
 * si l'exécution échoue.
 * Retourne 0 si succès, -1 sinon.
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
