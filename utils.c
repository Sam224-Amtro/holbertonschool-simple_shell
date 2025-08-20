#include "main.h"

/**
 * remove_trailing_newline - Supprime le '\n' à la fin d'une chaîne
 * @line: chaîne à modifier
 *
 * Parcourt la chaîne et remplace le premier '\n' rencontré
 * par un caractère de fin de chaîne '\0'. 
 * Si `line` est NULL, la fonction ne fait rien.
 */
void remove_trailing_newline(char *line)
{
	int i;

	if (!line) return;
	for (i = 0; line[i]; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = '\0';
			break;
		}
	}
}

/**
 * _realloc_args - Réalloue un tableau de pointeurs vers char
 * @args: ancien tableau à réallouer
 * @old_size: ancienne taille du tableau
 * @new_size: nouvelle taille désirée
 *
 * Copie les anciens éléments dans un nouveau tableau de taille
 * `new_size`, puis libère l'ancien tableau.
 *
 * Return: pointeur vers le nouveau tableau, ou NULL en cas d'échec
 */
char **_realloc_args(char **args, int old_size, int new_size)
{
	char **new_args = malloc(sizeof(char *) * new_size);

	int i;

	if (!new_args)
		return (NULL);

	for (i = 0; i < old_size; i++)
		new_args[i] = args[i];

	free(args);
	return (new_args);
}

/**
 * free_args - Libère un tableau d'arguments
 * @args: tableau à libérer
 *
 * Cette fonction libère simplement le tableau d'arguments
 * (pas les chaînes individuelles qui pointent vers `line`).
 */
void free_args(char **args)
{
	free(args); 
}

/**
 * my_strdup - Duplique une chaîne de caractères
 * @s: chaîne source à dupliquer
 *
 * Alloue dynamiquement une nouvelle chaîne et y copie
 * le contenu de `s`.
 *
 * Return: pointeur vers la nouvelle chaîne, ou NULL en cas d'échec
 */
char *my_strdup(const char *s)
{
	size_t len;
	char *dup;

	if (!s)
		return (NULL);

	len = strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);

	strcpy(dup, s);
	return (dup);
}
