include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Les étapes de la fonction :
 * Récupérer PATH avec _getenv("PATH").
 * Faire une copie (strdup) pour ne pas modifier l’original.
 * Utiliser strtok() avec ":" comme séparateur.
 * Pour chaque morceau :
	Allouer un nouveau nœud (malloc).
	Copier la chaîne dans dir (avec strdup).
	Ajouter le nœud à la fin de la liste.
 * Retourner la tête de liste
*/

extern char **environ;

/** Cette structure "list_t" est un modèle de nœud de liste chaînée :
 * dir stocke une donnée (ici un chemin de répertoire).
 * next relie ce nœud au suivant.
 * typedef simplifie la déclaration.
*/
typedef struct list_s
{
	char *dir;

	struct list_s *next;
} list_t;

char *_getenv(const char *name)
{
	int i = 0;

	size_t len = strlen(name);

	while (environ[i] != NULL)
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (environ[i] + len + 1);
		i++;
	}
	return (NULL);
}

list_t *build_path_list(void)
{
	char *path = _getenv("PATH");

	if (path == NULL)
		return (NULL);
	/* Utiliser strdup() : alloue une copie d’une chaîne, utile car strtok() modifie la chaîne. */
	char *path_copy = strdup(path);

	if (!path_copy)
		return (NULL);

	list_t *head = NULL, *tail = NULL;
	char *token = strtok(path_copy, ":");

	while (token != NULL)
	{
		list_t *new_node = malloc(sizeof(list_t));
		if (!new_node)
		{
			/* Gestion mémoire : il faut libérer toute la liste après usage avec free.*/
			free(path_copy);
			return (NULL);
		}
		new_node->dir = strdup(token);
		new_node->next = NULL;

		if (!head)
			head = new_node;
		else
			tail->next = new_node;

		tail = new_node;
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (head);
}

void print_list(list_t *head)
{
	while (head)
	{
		printf("%s\n", head->dir);
		head = head->next;
	}
}

int main(void)
{
	list_t *path_list = build_path_list();
	print_list(path_list);
	return (0);
}
