#include <stdio.h>
#include <unistd.h>

/**
 * main - PID
 *
 * Return: Always 0.
 */
int main(void)
{
	pid_t ppid = getppid();
	printf("%u\n", (unsigned)ppid);
	return (0);
}
