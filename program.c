#include <stdio.h>

/**
 * program - that prints all the arguments, without using ac
 *@argc: this is the argument to check
 *@argv: this is the table argument to check
 *
 * Return: Always 0
*/
int main(int argc, char *argv[])
{
	(void)argc;

	char **arg = argv;
	while (*arg != NULL)
	{
		printf("%s\n", *arg);
		arg++;
	}
	return (0);
}
