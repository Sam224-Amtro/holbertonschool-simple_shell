#include <stdio.h>
#include <stdlib.h>

/*
* Simple program that reads lines from the standard entrance
* and reappears them. Use the Getline () standard function.
*/
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	while (1)
	{
		printf("$ ");

		nread = getline(&line, &len, stdin);
		if (nread == 1)
		{
			printf("\nEnd of input delected. Exiting...\n");
			break;
		}
		printf("%s", line);
	}
	free(line);
	return (0);
}
