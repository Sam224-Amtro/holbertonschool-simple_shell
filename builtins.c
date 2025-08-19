#include "main.h"

/**
 * handle_builtin - Vérifie et exécute les commandes internes du shell
 * @args: tableau contenant la commande et ses arguments
 * @envp: tableau des variables d'environnement
 * @line: ligne saisie par l'utilisateur (libérée si nécessaire)
 *
 * Description :
 * Cette fonction prend en charge l’exécution des commandes internes du shell.
 * Elle gère notamment :
 *   - "exit" : qui termine proprement l’exécution du shell,
 *   - "env"  : qui affiche la liste des variables d’environnement.
 *
 * Return: 1 si une commande interne a été reconnue et exécutée, 0 sinon.
 */
int handle_builtin(char **args, char **envp, char *line)
{
	int k;

	if (strcmp(args[0], "exit") == 0)
	{
		free(args);
		free(line);
		exit(0);
	}

	if (strcmp(args[0], "env") == 0)
	{
		for (k = 0; envp[k] != NULL; k++)
			printf("%s\n", envp[k]);
		return (1);
	}

	return (0);
}
