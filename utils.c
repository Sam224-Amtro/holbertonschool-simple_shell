#include "main.h"

void remove_trailing_newline(char *line)
{
	int i;

	if (!line) return;
	for (i = 0; line[i]; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = '\0';
			break;
		}
	}
}

char **_realloc_args(char **args, int old_size, int new_size)
{
	char **new_args = malloc(sizeof(char *) * new_size);

	int i;

	if (!new_args)
		return (NULL);

	for (i = 0; i < old_size; i++)
		new_args[i] = args[i];

	free(args);
	return (new_args);
}

void free_args(char **args)
{
	free(args); /* on ne free PAS args[i], ils pointent dans line */
}

char *my_strdup(const char *s)
{
	size_t len;
	char *dup;

	if (!s)
		return (NULL);

	len = strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);

	strcpy(dup, s);
	return (dup);
}
