#include "main.h"
#include <stdlib.h>
#include <string.h>

/**
* get_env_path - Récupère la valeur de la variable PATH depuis envp
* @envp: tableau des variables d'environnement
*
* Return: pointeur vers la valeur de PATH (ne pas free), ou NULL si absente
*/
char *get_env_path(char **envp)
{
	int k;

	for (k = 0; envp[k] != NULL; k++)
	{
		if (strncmp(envp[k], "PATH=", 5) == 0)
			return (envp[k] + 5);
	}
	return (NULL);
}

/**
* _realloc_args - Réalloue dynamiquement un tableau de chaînes
* @args: tableau de chaînes existant
* @old_size: nombre d’éléments actuellement utilisés (hors NULL final)
* @new_size: nouvelle capacité souhaitée
*
* Return: pointeur vers le nouveau tableau, ou NULL si malloc échoue
*/
char **_realloc_args(char **args, int old_size, int new_size)
{
	char **new_args;

	int k;

	new_args = malloc(sizeof(char *) * new_size);
	if (!new_args)
		return (NULL);

	for (k = 0; k <= old_size; k++)  /* recopie aussi le NULL final */
		new_args[k] = args[k];

	free(args);
	return (new_args);
}
