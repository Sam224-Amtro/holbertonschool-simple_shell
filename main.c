#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * remove_trailing_newline - enlève le '\n' final d'une chaîne
 * @line: chaîne à modifier
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
 * free_args - libère la mémoire allouée pour args
 * @args: tableau de chaînes
 */
void free_args(char **args)
{
	int i;

	if (!args)
		return;

	for (i = 0; args[i] != NULL; i++)
		free(args[i]);

	free(args);
}

/**
 * shell_loop - boucle principale du shell
 * @argv: tableau des arguments du programme
 * @envp: tableau des variables d'environnement
 */
void shell_loop(char **argv, char **envp)
{
	char *line = NULL, *full_path;
	size_t len = 0;
	ssize_t n_read;
	char **args;
	int exit_status = 0;
	int line_count = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");

		n_read = getline(&line, &len, stdin);
		if (n_read == -1) /* Ctrl+D ou erreur */
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			free(line);
			exit(exit_status);
		}

		line_count++;
		remove_trailing_newline(line);
		args = parse_line(line);

		if (args && args[0] != NULL)
		{
			if (handle_builtin(args, envp, line))
			{
				free_args(args);
				continue;
			}

			full_path = find_full_path(args[0], envp);
			if (full_path)
			{
				exit_status = execute_command(full_path, args, envp);
				free(full_path);
			}
			else
			{
				fprintf(stderr, "%s: %d: %s: not found\n",
					argv[0], line_count, args[0]);
				exit_status = 127;
			}
		}
	}
}

/**
 * main - point d'entrée du shell
 * @argc: nombre d'arguments (non utilisé)
 * @argv: tableau des arguments
 * @envp: tableau des variables d'environnement
 *
 * Return: 0 en cas de succès
 */
int main(int argc, char **argv, char **envp)
{
	(void)argc;
	shell_loop(argv, envp);
	return (0);
}
