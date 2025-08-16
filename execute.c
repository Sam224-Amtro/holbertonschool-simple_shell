#include "main.h"

/**
 * execute_command - Crée un processus pour exécuter une commande
 * @command: chemin absolu de la commande à exécuter
 * @args: tableau d'arguments à passer à execve
 * @envp: tableau des variables d'environnement
 *
 * * Return: code de retour du processus exécuté
 * (0 si succès, autre valeur si erreur)
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
