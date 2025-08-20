#include "main.h"

/**
 * path_join - Concatène un dossier et une commande en un chemin complet
 * @dir: dossier (ex: /bin)
 * @cmd: commande (ex: ls)
 *
 * Cette fonction crée une nouvelle chaîne contenant `dir` + "/" + `cmd`.
 * Une mémoire est allouée dynamiquement, à libérer par l'appelant.
 *
 * Return: pointeur vers le chemin complet, ou NULL en cas d'échec malloc
 */
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

/**
 * get_path_from_env - Récupère la valeur de PATH dans l'environnement
 * @envp: tableau des variables d'environnement
 *
 * Cette fonction parcourt `envp` et retourne un pointeur vers la valeur
 * associée à la variable PATH (après "PATH=").
 *
 * Return: pointeur vers la valeur de PATH, ou NULL si introuvable
 */
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

/**
 * find_full_path - Trouve le chemin complet d'une commande
 * @command: commande à rechercher (ex: "ls")
 * @envp: tableau des variables d'environnement
 *
 * Si la commande contient déjà un '/', elle est vérifiée directement.
 * Sinon, cette fonction parcourt chaque dossier dans PATH et construit
 * un chemin complet avec la commande. Le premier chemin exécutable trouvé
 * est retourné.
 *
 * Return: pointeur vers une chaîne nouvellement allouée contenant
 *         le chemin complet, ou NULL si la commande n'est pas trouvée.
 */
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
