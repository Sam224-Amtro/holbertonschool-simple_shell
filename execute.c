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
	else // Processus parent
	{
		waitpid(pid, &status, 0);
	}
}
