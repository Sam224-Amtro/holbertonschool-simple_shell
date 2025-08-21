#include "main.h"
#include <string.h>
#include <stdlib.h>

/**
 * get_path_from_env - Récupère la valeur de la variable PATH depuis envp
 * @envp: tableau des variables d'environnement
 *
 * Return: pointeur vers la valeur de PATH (ne pas free!), ou NULL si absente
 */
char *get_path_from_env(char **envp)
{
	int i;

	for (i = 0; envp[i] != NULL; i++)
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
	}
	return (NULL);
}

/**
 * _realloc_args - Réalloue dynamiquement un tableau de chaînes
 * @args: tableau de chaînes existant
 * @old_size: nombre actuel d'éléments utilisés
 * @new_size: nouvelle capacité souhaitée
 *
 * Return: pointeur vers le nouveau tableau, ou NULL si malloc échoue
 */
char **_realloc_args(char **args, int old_size, int new_size)
{
	char **new_args;
	int i;

	new_args = malloc(sizeof(char *) * new_size);
	if (!new_args)
		return (NULL);

	if (args != NULL)
	{
		for (i = 0; i < old_size; i++)
			new_args[i] = args[i];
		free(args);
	}
	for (i = old_size; i < new_size; i++)
		new_args[i] = NULL;

	return (new_args);
}
