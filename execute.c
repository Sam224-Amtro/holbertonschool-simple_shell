#include "main.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * execute_command - Crée un processus fils et exécute une commande
 * @command: chemin absolu de la commande à exécuter
 * @args: tableau des arguments (args[0] = nom de la commande)
 * @envp: tableau des variables d'environnement
 *
 * Description :
 * Cette fonction fork le processus courant, puis exécute la commande
 * spécifiée dans le processus fils avec ses arguments et l'environnement.
 * Le processus parent attend la fin du fils et récupère son code de retour.
 *
 * Return: code de retour du processus fils, ou -1 en cas d’erreur.
 */
int execute_command(char *full_path, char **args, char **envp)
{
	pid_t pid = fork();
	int status;

	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
	{
		if (execve(full_path, args, envp) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
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
	}

	return (0);
}
