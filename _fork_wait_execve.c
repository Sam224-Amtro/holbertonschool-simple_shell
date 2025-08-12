#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	pid_t child_pid;
	int i;

	for (i = 0; i < 5; i++)
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("fork");
			return (1);
		}
		/* Enfant */
		if (child_pid == 0) 
		{
			execlp("ls", "ls", "-l", "/tmp", NULL);
			/* Si execlp échoue */
			perror("execlp"); 
			return (1);
		}
		/* Père */
		else 
		{
			/* Attend la fin de l’enfant */
			wait(NULL); 
		}
	}

	return (0);
}
