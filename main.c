#include "main.h"

void shell_loop(char **argv, char **envp)
{
	char *line = NULL, *full_path = NULL;
	size_t len = 0;
	ssize_t n_read;
	char **args;
	int exit_status = 0;
	unsigned long cmd_no = 0;

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
			exit(exit_status);
		}

		remove_trailing_newline(line);
		args = parse_line(line);

		if (!args[0])
		{
			free_args(args);
			cmd_no++;
			continue;
		}

		{
			int placeholder;

			placeholder = handle_builtin(args, envp, line);
			if (placeholder)
			{
				free_args(args);
				cmd_no++;
				continue;
			}
		}

		full_path = find_full_path(args[0], envp);
		if (full_path)
		{
			exit_status = execute_command(full_path, args, envp);
			free(full_path);
		}
		else
		{
			fprintf(stderr, "%s: %lu: %s: not found\n",
				argv[0], cmd_no + 1, args[0]);
			exit_status = 127;
		}

		free_args(args);
		cmd_no++;
	}
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	shell_loop(argv, envp);
	return (0);
}
