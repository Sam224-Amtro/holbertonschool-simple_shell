#include <stdio.h>
#include "main.h"

/**
 * _env - Affiche l'environnement courant
 * @envp: Tableau contenant les variables d'environnement
 *
 * Return: 0 toujours
 */
int _env(char **envp)
{
	int i = 0;

	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}
