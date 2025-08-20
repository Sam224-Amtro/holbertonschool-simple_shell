#include "main.h"

static char *path_join(const char *dir, const char *cmd)
{
	size_t len1 = strlen(dir), len2 = strlen(cmd);
	char *full = malloc(len1 + 1 + len2 + 1);

	if (!full)
		return (NULL);

	strcpy(full, dir);
	full[len1] = '/';
	strcpy(full + len1 + 1, cmd);

	return (full);
}

char *get_path_from_env(char **envp)
{
	int i;

	for (i = 0; envp && envp[i]; i++)
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
	}
	return (NULL);
}

char *find_full_path(const char *command, char **envp)
{
	char *path, *copy, *dir, *full;

	if (!command || !*command)
		return (NULL);

	if (strchr(command, '/'))
	{
		if (access(command, X_OK) == 0)
			return (my_strdup(command));
		return (NULL);
	}

	path = get_path_from_env(envp);
	if (!path)
		return (NULL);

	copy = my_strdup(path);
	if (!copy)
		return (NULL);

	dir = strtok(copy, ":");
	while (dir)
	{
		full = path_join(dir, command);
		if (!full)
		{
			free(copy);
			return (NULL);
		}

		if (access(full, X_OK) == 0)
		{
			free(copy);
			return (full);
		}
		free(full);
		dir = strtok(NULL, ":");
	}
	free(copy);
	return (NULL);
}
