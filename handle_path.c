#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char **environ;

/**
* get_path_from_env - Récupère la valeur de la variable PATH depuis environ
*
* Return: Chaîne contenant la valeur de PATH si trouvée, NULL sinon
*/
char *get_path_from_env(void)
{
	int i = 0;

	while (environ[i])
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
			return (environ[i] + 5);
		i++;
	}
	return (NULL);
}

/**
* find_full_path - Cherche le chemin complet d'une commande dans le PATH
* @command: Nom de la commande à chercher
*
* Return: Chaîne allouée contenant le chemin complet si trouvé,
*         NULL sinon (à free() après usage)
*/
char *find_full_path(char *command)
{
	char *path, *path_copy, *token, *full_path;

	int len;

	if (strchr(command, '/'))
		return (strdup(command));

	path = get_path_from_env();
	if (!path || !*path)
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
			perror("malloc");
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
