#include "main.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <stdlib.h>

/**
 * free_args - libère correctement le tableau d'arguments
 * @args: tableau d'arguments à libérer
 */
void free_args(char **args)
{
	if (args)
		free(args);
}

/**
 * handle_builtin - exécute les commandes internes du shell
 * @args: tableau contenant la commande et ses arguments
 * @envp: tableau des variables d'environnement
 * @line: ligne saisie par l'utilisateur (libérée si nécessaire)
 *
 * Return: 1 si une built-in a été exécutée, 0 sinon
 */
int handle_builtin(char **args, char **envp, char *line)
{
	int i;

	if (args == NULL && args[0] == NULL)
		return (0);

	if (strcmp(args[0], "exit") == 0)
	{
		free(line);
		free(args);
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
