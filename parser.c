#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

/**
* read_line - Reads a line from stdin
*
* Return: Pointer to the read line (must be freed by the caller),
* or NULL on EOF/error
*/
char *read_line(void)
{
	 char *line = NULL;

	size_t bufsize = 0;

	if (getline(&line, &bufsize, stdin) == -1)
	{
		free(line);
		return (NULL);
	}

	/* Remove trailing newline */
	if (line[strlen(line) - 1] == '\n')
		line[strlen(line) - 1] = '\0';

	return (line);
}

/**
* parse_line - Splits a line into tokens
* @line: The input string
*
* Return: Array of strings (tokens), NULL-terminated. Must be freed by caller.
*/
char **parse_line(char *line)
{
	int bufsize = 64;

	int position = 0;

	char **tokens = malloc(bufsize * sizeof(char *));

	char *token;

	if (!tokens)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " \t\r\n");
	while (token != NULL)
	{
		tokens[position++] = token;

		if (position >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				perror("realloc");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, " \t\r\n");
	}
	tokens[position] = NULL;

	return (tokens);
}

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"

/**
* execute_command - Executes a shell command
* @command: Command string
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
		if (execve(args[0], args, NULL) == -1)
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

void shell_loop(void)
{
	char *line;
	char **args;

	while (1)
	{
		printf("$ ");
		line = read_line();
		if (!line)
			break;

		args = parse_line(line);

		execute_command(args);

		free(args);
		free(line);
	}
}

