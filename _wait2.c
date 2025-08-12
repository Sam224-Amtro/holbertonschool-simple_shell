#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	pid_t child_pid;
	int status;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
		return (1);
	}

	/* enfant */
	if (child_pid == 0) 
	{
		/* On peut faire des actions ici */
		printf("Child process (PID %d): I am the child\n", getpid());
	}
	/* père */
	else 
	{
		printf("Parent process (PID %d): I am the father\n", getpid());
		/* On attend que l'enfant termine */
		wait(&status);
		printf("Child finished with status %d\n", status);
	}

	return (0);
}
