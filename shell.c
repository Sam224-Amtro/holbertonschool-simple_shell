#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern char **environ;
/** 
 * printf("#cisfun$ "); → affiche le prompt.
 * fgets → lit la commande entrée par l’utilisateur.
 * strcspn → enlève le saut de ligne \n.
 * fork → crée un enfant.
 * Enfant (pid == 0) → exécute la commande avec execve (sans arguments supplémentaires).
 * Père → attend que l’enfant finisse avec wait.
 * Boucle infinie → permet de répéter jusqu’à Ctrl+D ou Ctrl+C.
*/

int main(void)
{
	char buffer[1024];

	pid_t pid;
	int status;

	while (1)
	{
		/* Afficher le prompt */
		printf("#cisfun$ ");
		fflush(stdout);

		/* Lire l'entrée utilisateure et lis aussi les espace entre les mots. */
		if (fgets(buffer, sizeof(buffer), stdin) == NULL)
		{
			/* Si EOF (Ctrl+D), on sort */
			printf("\n");
			break;
		}

		/* Retirer le \n à la fin */
		buffer[strcspn(buffer, "\n")] = '\0';

		/* Ignorer ligne vide */
		if (strlen(buffer) == 0)
			continue;

		/* Créer un processus enfant */
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			continue;
		}
		/* Enfant */
		if (pid == 0) 
		{
			char *argv[] = {buffer, NULL};

			if (execve(buffer, argv, environ) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		/* Père */
		else 
		{
			wait(&status);
		}
	}

	return (0);
}
