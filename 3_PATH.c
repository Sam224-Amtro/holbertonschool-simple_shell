#include <stdio.h>
#include <string.h>

extern char **environ;

/* Fonction pour récupérer une variable d'environnement */
char *_getenv(const char *name)
{
	int i = 0;

	size_t len = strlen(name);

	while (environ[i] != NULL)
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (environ[i] + len + 1); /* valeur après '=' */
		i++;
	}
	return (NULL);
}

void print_path_dirs(void)
{
	char *path = _getenv("PATH");
	/* Un pointeur vers un caractère qui va servir à stocker l’adresse du début de chaque "morceau" de la chaîne PATH quand on utilise strtok(). */
	char *token;

	if (path == NULL)
	{
		printf("PATH non défini\n");
		return;
	}

	/* Modifie la chaîne → faire une copie */
	char path_copy[1024];
	strncpy(path_copy, path, sizeof(path_copy) - 1);
	path_copy[sizeof(path_copy) - 1] = '\0';
	/* strtok il cherche le premier caractère qui n’est pas un séparateur. (fonction <string.h>) */
	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		printf("%s\n", token);
		token = strtok(NULL, ":");
	}
}

int main(void)
{
	print_path_dirs();
	return (0);
}
