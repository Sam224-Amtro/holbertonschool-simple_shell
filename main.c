#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 1024

/**
 * remove_trailing_newline - removes the final line break from a string
 * @line: string to be processed
 */
void remove_trailing_newline(char *line)
{
	size_t len;

	if (!line)
		return;

	len = strlen(line);

	if (len > 0 && line[len - 1] == '\n')
	{
		line[len - 1] = '\0';
	}
}

/**
 * execute_command - Executes a simple command entered by the user
 * @line: string representing the command
 */
void execute_command(char *line)
{
	pid_t pid;
	int status;
	char *args[2];

	if (strcmp(line, "") == 0)
		return;

	pid = fork();

	if (pid < 0)
	{
		perror("fork failed");
	}
	else if (pid == 0)
	{
		args[0] = line;
		args[1] = NULL;

		if (execvp(args[0], args) == -1)
		{
			perror("execvp failed");
		}

		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
	}
}

/**
 * shell_loop - main shell loop
 * @argv: array of arguments (not used)
 * @envp: array of environment variables (not used)
 */
void shell_loop(char **argv, char **envp)
{
	char line[MAX_LINE];
	(void)argv;
	(void)envp;

	while (1)
	{
		printf("$ ");
		fflush(stdout);

		if (!fgets(line, MAX_LINE, stdin))
		{
			printf("\n");
			break;
		}

		remove_trailing_newline(line);

		if (strcmp(line, "exit") == 0)
		{
			break;
		}

		execute_command(line);
	}
}

/**
 * main - Shell entry point
 * @argc: number of arguments passed (not used here)
 * @argv: array of arguments (argv[0] = program name)
 * @envp: array containing environment variables
 *
 * Return: 0 on success
 */
int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;

	shell_loop(argv, envp);

	return (0);
}
