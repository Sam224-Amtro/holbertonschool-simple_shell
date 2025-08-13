#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int ac, char **av)
{
	char *path_env, *path_copy, *dir;

	char full_path[1024];

	int i;
	/* Si l'utilisateur n'a pas mis au moins un argument après le nom du programme */
	if (ac < 2)
	{
		fprintf(stderr, "Usage: %s filename ...\n", av[0]);
		return (1);
	}
	/* Récupérer PATH */
	path_env = getenv("PATH");
	if (!path_env)
		return (1);

	for (i = 1; i < ac; i++)
	{
		/* Dupliquer la chaîne */
		path_copy = strdup(path_env);
		/* Découper la chaîne en dossiers, c'est pour séparer les répertoires.*/
		dir = strtok(path_copy, ":");
		while (dir)
		{
			/* sprintf = créer une chaîne à partir de morceaux que tu donnes, cela permet de construire le chemin complet */
			sprintf(full_path, "%s/%s", dir, av[i]);
			/* vérifie si exécutable */
			if (access(full_path, X_OK) == 0)
			{
				/* Afficher le chemin trouvé */
				printf("%s\n", full_path);
				break;
			}
			/* Donne-moi le prochain morceau de la chaîne précédente en coupant au caractère : */
			dir = strtok(NULL, ":");
		}
		/* libérer la la copie de PATH à chaque fichier*/
		free(path_copy);
	}
	return (0);
}
