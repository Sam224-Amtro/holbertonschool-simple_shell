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
				continue;
			full_path = find_full_path(args[0], envp);
			if (full_path)
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
	if (!isatty(STDIN_FILENO))
		exit(exit_status);
	free(line);
	free(args[0]);
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
/*
 * fprintf envoie un message d'erreur vers stderr si la commande
 * n'est pas trouvée.
 * Le format suit celui de /bin/sh :
 *    "./hsh: 1: commande: not found"
 *
 * Explications des paramètres :
 *    argv[0] : nom du programme (ici "./hsh")
 *    1       : numéro de ligne simulée
 *    args[0] : commande entrée par l'utilisateur
 */
