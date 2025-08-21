#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

/**
 * execute_command - Crée un processus pour exécuter une commande
 * @command: chemin absolu de la commande à exécuter
 * @args: tableau d'arguments à passer à execve
 * @envp: tableau des variables d'environnement
 *
 * Return: Code de sortie du fils si terminé normalement
 *          127 si execve échoue,
 *         -1 si le processus s'est terminé anormalement.
 * Description :
 * Cette fonction crée un processus fils pour exécuter une commande
 * en utilisant execve. Le processus parent attend que le fils termine.
 * Si execve échoue dans le fils, celui-ci quitte avec le code 127
 * (convention Unix pour "commande non trouvée").
 */
int execute_command(char *command, char **args, char **envp)
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
		execve(command, args, envp);
		perror("execve");
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
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status));
		else
			return (-1);
	}
}
