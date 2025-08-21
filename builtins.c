#include "main.h"
#include <string.h>
#include <stdio.h>
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
 * _env - Affiche l'environnement courant
 * @envp: Tableau de chaînes contenant les variables d'environnement
 *
 * Return: 0 toujours (succès)
 */
int _env(char **envp)
{
	int i = 0;

	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	}

	return (0);
}

/**
 * handle_builtin - Vérifie et exécute les commandes internes
 * @args: Tableau d'arguments
 * @envp: Variables d'environnement
 * @line: Ligne entrée (pour free si besoin)
 *
 * Return: 1 si une commande interne a été exécutée, 0 sinon
 */
int handle_builtin(char **args, char **envp, char *line)
{
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
