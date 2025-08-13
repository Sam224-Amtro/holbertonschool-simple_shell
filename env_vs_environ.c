#include <stdio.h>

/*  Variable globale */
extern char **environ;  //

int main(int ac, char **av, char **env)
{
	printf("Adresse de env : %p\n", (void *)env);
	printf("Adresse de environ : %p\n", (void *)environ);

	/* On peut aussi afficher la première variable pour comparer */
	printf("Première variable de env : %s\n", env[0]);
	printf("Première variable de environ : %s\n", environ[0]);

	return (0);
}
