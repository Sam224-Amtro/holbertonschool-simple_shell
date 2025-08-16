#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * handle_builtin - Vérifie et exécute les commandes internes du shell
 * @args: tableau contenant la commande et ses arguments
 * @envp: tableau des variables d'environnement
 * @line: ligne saisie par l'utilisateur (libérée si nécessaire)
 *
 * Return: 1 si la commande était un builtin et a été exécutée,
 *         0 sinon
 */
int handle_builtin(char **args, char **envp, char *line)
{
	int i;

	if (strcmp(args[0], "exit") == 0)
	{
		free(args);
		free(line);
		exit(0);
	}

	if (strcmp(args[0], "env") == 0)
	{
		for (i = 0; envp[i] != NULL; i++)
			printf("%s\n", envp[i]);
		return (1);
	}

	return (0);
}
