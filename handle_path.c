#include "main.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/**
 * find_full_path - Obtient le chemin absolu d'une commande
 * @command: nom de la commande (ex: "ls")
 * @envp: tableau des variables d'environnement
 *
 * Return: chaîne allouée contenant le chemin complet si trouvé, NULL sinon.
 */
char *find_full_path(char *command, char **envp)
{
	char *path, *path_copy, *token, *full_path;
	size_t len;

	if (!command || !*command)
		return (NULL);

	if (strchr(command, '/'))
		return (strdup(command));

	path = get_path_from_env(envp);
	if (!path)
		return (NULL);

	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	token = strtok(path_copy, ":");
	while (token)
	{
		len = strlen(token) + strlen(command) + 2;
		full_path = malloc(len);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}
		snprintf(full_path, len, "%s/%s", token, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
