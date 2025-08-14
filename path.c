#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * get_path_from_env - retrieves PATH value from envp
 * @envp: array of environment variables
 *
 * Return: pointer to PATH string if found, otherwise NULL
 */
char *get_path_from_env(char **envp)
{
	int i = 0;

	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}
/**
 * find_full_path - Finds the full path of a command via PATH
 * @command: command name (e.g. "ls")
 * @envp: array of environment variables
 *
 * Return: full path (to free) if found, otherwise NULL
 */
char *find_full_path(char *command, char **envp)
{
	char *path, *path_copy, *token, *full_path;
	int len;

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
