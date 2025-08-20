#include "main.h"

/**
 * execute_command - Crée un processus et exécute une commande
 * @command: chemin complet de la commande à exécuter
 * @args: tableau d'arguments pour la commande
 * @envp: tableau des variables d'environnement
 *
 * Cette fonction utilise fork() pour créer un processus fils.
 * - Dans le fils : exécute la commande via execve().
 * - Dans le parent : attend la fin du fils avec waitpid().
 *
 * Return: le code de sortie de la commande si succès,
 *         -1 en cas d'erreur, ou 128 + numéro du signal
 *         si le processus est terminé par un signal.
 */
int execute_command(char *command, char **args, char **envp)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}

	if (pid == 0)
	{
		execve(command, args, envp);
		_exit(127); /* execve a échoué */
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			return (-1);

		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status));
	}
	return (-1);
}
