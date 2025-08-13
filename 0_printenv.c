#include <stdio.h>

/* Déclaration de la variable globale */
extern char **environ;

/**
 * Variable globale :
 * Contient toutes les variables d’environnement du processus.
 * Chaque élément de environ est une chaîne de caractères de la forme NOM=VALEUR.
 * Le tableau est terminé par NULL.
*/
int main(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}

	return (0);
}
