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
		exit(127);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else
			return (-1);
	}
}
