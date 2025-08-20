#include "main.h"

/**
 * handle_builtin - Gère l'exécution des commandes internes du shell
 * @args: tableau contenant la commande et ses arguments
 * @envp: tableau des variables d'environnement
 * @line: ligne saisie par l'utilisateur (à libérer si besoin)
 *
 * Cette fonction vérifie si la commande entrée correspond
 * à une commande interne du shell :
 * - "exit" : libère la mémoire et quitte le shell
 * - "env"  : affiche toutes les variables d'environnement
 *
 * Return: 1 si une commande interne a été exécutée,
 *         0 sinon.
 */
int handle_builtin(char **args, char **envp, char *line)
{
	int i;

	if (!args || !args[0])
		return (0);

	if (strcmp(args[0], "exit") == 0)
	{
		free_args(args);
		free(line);
		exit(0);
	}

	if (strcmp(args[0], "env") == 0)
	{
		for (i = 0; envp && envp[i]; i++)
			printf("%s\n", envp[i]);
		return (1);
	}

	return (0);
}
