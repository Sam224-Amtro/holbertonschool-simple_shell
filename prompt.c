#include <stdio.h>
#include <stdlib.h>

/**
 * Ce que le programme doit faire
 * Afficher le prompt $ (sans saut de ligne).
 * Attendre que l’utilisateur tape quelque chose.
 * Afficher ce que l’utilisateur a tapé (saut de ligne à la fin).
 * Recommencer jusqu’à ce que l’utilisateur fasse Ctrl+D (EOF).
*/
int main(void)
{
	/* Pointeur qui contiendra la ligne lue*/
    char * line = NULL;
    /* Taille du buffer (gérée par getline) */
	size_t len = 0;
    /* Nombre de caractères lus */
	ssize_t nread;

		/* while (1) pour faire une boucle infinie volontaire, ce qui signifie : Continue à tourner tant qu’on n’a pas décidé d’arrêter*/
    while (1) 
	{
		/* Affiche l'invite */
        printf("$ ");
        nread = getline(&line, &len, stdin);

		if (nread == -1)  /* EOF détecté (Ctrl+D) ou erreur */
		{
			printf("\n");
			break;
		}
		/* Affiche la ligne lue (déjà avec \n) */	
        printf("%s", line);	
    }
	/*  libère la mémoire allouée par getline */
    free(line);
	return (0);
}
