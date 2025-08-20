#include "main.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * get_env_path - Récupère la valeur de PATH dans envp
 * @envp: tableau des variables d'environnement
 *
 * Return: pointeur sur la chaîne PATH (après "PATH="), ou NULL
 */
static char *get_env_path(char **envp)
{
	int i = 0;

	while (envp && envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

/**
 * build_path - Construit un chemin complet dossier+commande
 * @dir: dossier (ex: "/bin")
 * @dir_len: longueur de dir
 * @command: commande (ex: "ls")
 *
 * Return: chaîne allouée contenant dir/command
 */
static char *build_path(char *dir, size_t dir_len, char *command)
{
	size_t cmd_len = strlen(command);
	char *full_path = malloc(dir_len + 1 + cmd_len + 1);

	if (!full_path)
		return (NULL);

	memcpy(full_path, dir, dir_len);
	full_path[dir_len] = '/';
	memcpy(full_path + dir_len + 1, command, cmd_len);
	full_path[dir_len + 1 + cmd_len] = '\0';

	return (full_path);
}

/**
 * find_full_path - Cherche le chemin absolu d'une commande
 * @command: commande (ex: "ls")
 * @envp: variables d'environnement
 *
 * Return: chaîne allouée contenant le chemin complet si trouvé, NULL sinon
 */
char *find_full_path(char *command, char **envp)
{
	char *path_env, *start, *end, *full_path;

	if (!command || !*command)
		return (NULL);

	if (strchr(command, '/'))
		return (strdup(command));

	path_env = get_env_path(envp);
	if (!path_env)
		return (NULL);

	start = path_env;
	while (*start)
	{
		end = start;
		while (*end && *end != ':')
			end++;

		full_path = build_path(start, end - start, command);
		if (!full_path)
			return (NULL);

		if (access(full_path, X_OK) == 0)
			return (full_path);

		free(full_path);
		start = (*end == ':') ? end + 1 : end;
	}

	return (NULL);
}
