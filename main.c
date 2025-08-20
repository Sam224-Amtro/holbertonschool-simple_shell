#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * remove_trailing_newline - Supprime le caractère '\n' final
 * @line: Chaîne de caractères à nettoyer
 *
 * Description: Remplace le premier '\n' rencontré par '\0'
 */
void remove_trailing_newline(char *line)
{
	int i;

	if (!line)
		return;

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
 * read_line - Lit une ligne depuis l'entrée standard
 *
 * Return: Chaîne lue ou NULL si EOF
 */
char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t n_read;

	if (isatty(STDIN_FILENO))
		printf("$ ");

	n_read = getline(&line, &len, stdin);
	if (n_read == -1)
	{
		if (isatty(STDIN_FILENO))
			printf("\n");
		free(line);
		return (NULL);
	}

	remove_trailing_newline(line);
	return (line);
}

/**
 * execute_input - Traite et exécute une commande
 * @argv: Arguments du programme
 * @envp: Variables d'environnement
 * @line: Ligne entrée par l'utilisateur
 *
 * Return: Code de sortie de la commande
 */
int execute_input(char **argv, char **envp, char *line)
{
	char **args;
	char *full_path;
	int exit_status = 0;

	args = parse_line(line);
	if (!args)
		return (1);

	if (args[0] != NULL)
	{
		if (handle_builtin(args, envp, line))
		{
			free_args(args);
			return (1);
		}

		full_path = find_full_path(args[0], envp);
		if (full_path)
		{
			exit_status = execute_command(full_path, args, envp);
			free(full_path);
		}
		else
		{
			fprintf(stderr, "%s: 1: %s: not found\n",
				argv[0], args[0]);
			exit_status = 127;
		}
	}

	free_args(args);
	return (exit_status);
}

/**
 * shell_loop - Boucle principale du shell
 * @argv: Arguments du programme
 * @envp: Variables d'environnement
 */
void shell_loop(char **argv, char **envp)
{
	char *line = NULL;
	int exit_status = 0;

	while (1)
	{
		line = read_line();
		if (!line)
		{
			free(line);
			exit(exit_status);
		}

		exit_status = execute_input(argv, envp, line);
		free(line);
	}
}

/**
 * main - Point d'entrée du shell
 * @argc: Nombre d'arguments (non utilisé)
 * @argv: Tableau des arguments
 * @envp: Variables d'environnement
 *
 * Return: 0 en cas de succès
 */
int main(int argc, char **argv, char **envp)
{
	(void)argc;
	shell_loop(argv, envp);
	return (0);
}
