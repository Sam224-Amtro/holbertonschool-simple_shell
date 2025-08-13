#include <stdio.h>
#include <string.h>

extern char **environ;

char *_getenv(const char *name)
{
	int i = 0;
	/**
		* strlen() est une fonction de la bibliothèque standard (<string.h>).
		* Cela permet de calculer la longueur d'une chaîne de caractères sans compter le caractère '\0' de fin.
	*/
	size_t len = strlen(name);

	while (environ[i] != NULL)
	{
		/* Vérifie si ça commence par "name=" avec "strncmp" qui compare au maximum n caractères des chaînes s1 et s2.*/
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
		{
			/* +1 pour passer le '=' et pour s’assurer qui n'a pas un préfixe (exemple : PATH vs PATHNAME). */
			return (environ[i] + len + 1);
		}
		i++;
	}
	/* pas trouvé */
	return (NULL);
}

int main(void)
{
	char *value;

	value = _getenv("PATH");
	if (value != NULL)
		printf("PATH = %s\n", value);
	else
		printf("Variable non trouvée\n");

	return (0);
}
