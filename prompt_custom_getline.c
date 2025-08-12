#include <stdio.h>
#include <stdlib.h>

/*
* Personalized implementation of Getline ().
* Bed from a stream (stream) character by character
* Until a '\ n' or eof, while resizing the buffer if necessary.
*/
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream)
{
	if (lineptr == NULL || n == NULL || stream == NULL)
		return (-1);

	if (*lineptr == NULL)
	{
		*n = 128;
		*lineptr = malloc(*n);
		if (*lineptr == NULL)
			return (-1);
	}
	size_t pos = 0;
	int c;

	while ((c = fgetc(stream)) != EOF)
	{
		if (pos + 1 >= *n)
		{
			*n *= 2;
			char *new_ptr = realloc(*lineptr, *n);
			if (new_ptr == NULL)
			{
				return (-1);
			}
			*lineptr = new_ptr;
		}
		(*lineptr)[pos++] = (char)c;

		if (c == '\n')
			break;
	}
	if (pos == 0 && c == EOF)
		return (-1);

	(*lineptr)[pos] = '\0';
	return (ssize_t)pos;
}
/*
* Main program using Custom_getline ()
* To read commands from the user.
*/
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	while (1)
	{
		printf("$ ");
		nread = custom_getline(&line, &len, stdin);

		if (nread == -1)
		{
			printf("\nEnd of input detected. Exiting...\n");
			break;
		}
		printf("%s", line);
	}
	free(line);
	return (0);
}
