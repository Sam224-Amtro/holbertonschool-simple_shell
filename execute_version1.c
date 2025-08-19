#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"

extern char **environ;

/**
* execute_command - Executes a shell command
* @args: NULL-terminated array of arguments
*/

void execute_command(char **args)
{
	pid_t pid;
	int status;

	if (args[0] == NULL)
		return;

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args,  environ) == -1)
		{
			perror("execve");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("fork");
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}
/**
* test_env - Test affichage env et environ
*/
void test_env(char **env)
{
	printf("Adresse de env : %p\n", (void *)env);
	printf("Adresse de environ : %p\n", (void *)environ);

	printf("Première variable de env : %s\n", env[0]);
	printf("Première variable de environ : %s\n", environ[0]);
}

/**
* test_execve - Test simple execve
*/
void test_execve(void)
{
	char *argv[] = {"/bin/ls", "-l", "/usr/", NULL};

	printf("Before execve\n");
	if (execve(argv[0], argv, environ) == -1)
		perror("Error");
	printf("After execve\n");
}
/**
* search_path - Cherche un fichier dans les dossiers du PATH
*/
void search_path(int ac, char **av)
{
	char *path_env, *path_copy, *dir;
	char full_path[1024];
	int i;

	if (ac < 2)
	{
		fprintf(stderr, "Usage: %s filename ...\n", av[0]);
		return;
	}

	path_env = getenv("PATH");
	if (!path_env)
		return;

	for (i = 1; i < ac; i++)
	{
		path_copy = strdup(path_env);
		dir = strtok(path_copy, ":");
		while (dir)
		{
			sprintf(full_path, "%s/%s", dir, av[i]);
			if (access(full_path, X_OK) == 0)
			{
				printf("%s\n", full_path);
				break;
			}
			dir = strtok(NULL, ":");
		}
		free(path_copy);
	}
}
