#include <stdio.h>
#include <unistd.h>

extern char **environ;

/**
 * Définis un tableau argv qui contient /bin/ls avec les arguments -l et /usr/.
 * Appeller execve pour exécuter /bin/ls avec ces arguments, mais sans passer l’environnement (le 3e argument est NULL).
 * Quand execve réussit, tu vois la sortie de ls -l /usr/.
 * Le printf("After execve\n"); n’est jamais atteint car execve remplace complètement ton programme.
*/
int main(void)
{
	char *argv[] = {"/bin/ls", "-l", "/usr/", NULL};

	printf("Before execve\n");
	if (execve(argv[0], argv, environ) == -1)
    {
		perror("Error:");
	}
	printf("After execve\n");
	return (0);
}