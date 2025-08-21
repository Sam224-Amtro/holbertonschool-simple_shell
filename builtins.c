#include "main.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <stdlib.h>

/**
 * free_args - libère correctement le tableau d'arguments
 * @args: tableau d'arguments à libérer
 *
 * NB: si args[i] vient de strtok(line), il ne faut PAS faire free(args[i])
 */
void free_args(char **args)
{
	if (args)
		free(args);
}


/**
 * built_in_checks - Vérifie et exécute les commandes internes du shell
 * @args: Tableau d'arguments (args[0] est la commande)
 * @envp: Variables d'environnement
 * @line: Ligne complète entrée par l'utilisateur
 *
 * Return: 1 si un built-in a été exécuté, 0 sinon
 */
int built_in_checks(char **args, char **envp, char *line)
{
	if (args == NULL || args[0] == NULL)
		return (0);

	if (strcmp(args[0], "exit") == 0)
	{
		free_args(args);
		free(line);
		exit(0);
	}
	else if (strcmp(args[0], "env") == 0)
	{
		_env(envp);
		return (1);
	}

	return (0);
}
