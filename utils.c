#include "main.h"

/**
 * get_path_from_env - Récupère la valeur de la variable PATH depuis envp
 * @envp: tableau des variables d'environnement
 *
 * Description :
 * Parcourt envp (tableau de chaînes "NOM=VALEUR") à la recherche de "PATH=".
 * Si trouvée, retourne pointeur vers le début de la valeur (après "PATH=").
 * Sinon, retourne NULL.
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
 * Description :
 * Crée un nouveau tableau avec plus de place,
 * copie les anciens pointeurs dedans, libère l'ancien tableau,
 * et retourne le nouveau.
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

	for (i = 0; i < old_size; i++)
		new_args[i] = args[i];

	free(args);
	return (new_args);
}
