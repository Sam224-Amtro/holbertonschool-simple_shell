#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include <unistd.h>

/**
 * main - Entry point for the simple shell program
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Description: This function starts the shell by calling shell_loop().
 * It ignores command-line arguments for now.
 *
 * Return: Always 0 on success
 */
int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	shell_loop();
	return (0);
}

/**
 * shell_loop - Main loop of the shell
 *
 * Displays a prompt (if in interactive mode), waits for user input,
 * reads a line using getline(), removes the trailing newline, and currently
 * just prints back the line. The loop stops when EOF (Ctrl+D) is received.
 *
 * Return: Nothing
 */
void shell_loop(void)
{
	char * line = NULL;
	size_t len = 0;
	ssize_t nread;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			printf("$ ");
		}

		nread = getline(&line, &len, stdin);

		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
			{
				printf("\n");
			}
			break;
		}

        if (line[nread - 1] == '\n')
		{
			line[nread - 1] = '\0';
		}
        printf("You typed: %s\n", line);
	}

	free(line);
}

