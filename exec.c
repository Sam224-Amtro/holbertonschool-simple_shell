#include "main.h"

int execute_command(char *command, char **args, char **envp)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}

	if (pid == 0)
	{
		execve(command, args, envp);
		_exit(127); /* execve a échoué */
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
			return (-1);

		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status));
	}
	return (-1);
}
