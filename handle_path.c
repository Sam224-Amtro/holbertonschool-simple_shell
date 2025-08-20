#include "main.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * find_full_path - Retourne le chemin complet d'une commande
 * @command: nom de la commande
 * @envp: tableau des variables d'environnement
 *
 * Return: chemin complet (à libérer) si trouvé, sinon NULL
 */
char *find_full_path(char *command, char **envp)
{
	char *path, *path_copy, *token, *full_path;
	int len;

	if (strchr(command, '/'))
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));
		else
			return (NULL);
	}

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
		sprintf(full_path, "%s/%s", token, command);

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
