#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *str = "Hello everybody !";
	char *word;
	int i = 0;
	/* position début mot (-1 = pas dans un mot) */
	int start = -1;
	
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && stard == -1))
		{
			/* début d'un mot détecté */
			start = i;
		}
		else if ((str[i] == ' ' || str[i + 1] == '\0') && stard != -1)
		{
			/* fin d'un mot, fin exclue si espace sinon fin chaîne */
		 int end = (str[i] == ' ') ? i - 1 : i;

            /* Longueur du mot */
            int length = end - start + 1;

            /* allouer et copier le mot*/
            char *word = malloc(length + 1);
            if (!word)
            {
				/* perror signifie print error (imprimer erreur) */
				perror("malloc");
                return 1;
            }
            for (int j = 0; j < length; j++)
            {
				word[j] = str[start + j];
			}
            word[length] = '\0';

            printf("Mot trouvé : '%s'\n", word);
            free(word);

			/* prêt pour le mot suivant */
            start = -1;
        }
        i++;
    }

    return (0);
}