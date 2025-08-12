#include <stdio.h>

/**
 * Ce qu’il fait le programme:
 * argv est un tableau : argv[0] = nom du programme, argv[1] = premier argument, etc.
 * Le dernier élément est NULL, donc on peut s’en servir pour arrêter la boucle.
 * On avance dans le tableau avec argv++ au lieu de compter avec ac.
*/
int main(int argc, char **argv)
{
	/* On ignore ac, dans l'exercice  on n'a pas le droit d'utiliser ac */
    (void)argc;

	/* Tant que le pointeur actuel n'est pas NULL */
    while (*argv)
    {
		/* Afficher l'argument */
        printf("%s\n", *argv);
		/* On passe à l'argument suivant */
        argv++;
    }
    return (0);
}