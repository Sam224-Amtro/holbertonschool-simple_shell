#include <stdio.h>
#include <unistd.h>

/**
 * main - PID
 *
 * Return: Always 0.
 */
int main(void)
{
	pid_t ppid;

	ppid = getpid();
	printf("My ppid: %u\n", (unsigned int)ppid);
	return (0);
}
