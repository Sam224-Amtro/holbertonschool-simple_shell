#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * remove_trailing_newline - Supprime le '\n' à la fin d'une chaîne
 * @line: chaîne à nettoyer
 */
void remove_trailing_newline(char *line)
{
	int i;

	for (i = 0; line[i] != '\0'; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = '\0';
			break;
		}
	}
}
/**
 * shell_loop - Boucle principale du shell
 * @argv: arguments du programme (argv[0] = nom)
 * @envp: tableau des variables d'environnement
 */
void shell_loop(char **argv, char **envp)
{
	char *line;
	char *full_path;
	size_t len;
	ssize_t n_read;
	char **args;
	int exit_status;

	line = NULL;
	len = 0;
	exit_status = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");

		n_read = getline(&line, &len, stdin);
		if (n_read == -1)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			free(line);
			if (!isatty(STDIN_FILENO))
				exit(exit_status);
			else
				exit(0);
		}

		remove_trailing_newline(line);
		args = parse_line(line);

		if (args[0] != NULL)
		{
			if (handle_builtin(args, envp, line))
			{
				free(args);
				continue;
			}

			full_path = find_full_path(args[0], envp);
			if (full_path != NULL)
			{
				exit_status = execute_command(full_path, args, envp);
				free(full_path);
			}
			else
			{
				fprintf(stderr, "%s: 1: %s: not found\n", argv[0], args[0]);
				exit_status = 127;
			}
		}

		free(args);
	}

	free(line);
}

/**
 * main - Point d'entrée du shell
 * @argc: nombre d'arguments passés (non utilisé ici)
 * @argv: tableau des arguments (argv[0] = nom du programme)
 * @envp: tableau contenant les variables d'environnement
 *
 * Return: 0 en cas de succès
 */
int main(int argc, char **argv, char **envp)
{
	(void)argc;
	shell_loop(argv, envp);
	return (0);
}
