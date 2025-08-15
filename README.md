_ FEUILLE DE ROUTE _
Construction d'un mini-shell
1. La structure du répertoire
simple_shell
│── main.c
│── parser.c
│── execute.c
│── utils.c
│── main.h
│── README.md

2. Les fichiers et leurs contenus
- Main.c contient : 
 a. main() : point d’entrée, ignore argc et argv pour l’instant, appelle shell_loop().
 b. shell_loop() (version simple) :
	── Affiche un prompt ($ ).
	── Lit la commande avec getline().
	── (Optionnel) enlève le \n à la fin.
	── Appelle ensuite le parser et l’exécution.

- Parser.c contient :
 a. read_line() : lit une ligne, enlève le \n, retourne un char *.
 b. parse_line() : découpe la ligne en tokens (mots) avec strtok() et retourne un tableau char ** (NULL-terminé).
	── Alloue dynamiquement avec malloc() et realloc() si besoin.


- Execute.c contient :
 a. execute_command() :
	── Ignore si args[0] est NULL.
	── Crée un processus avec fork().
	── Dans le processus enfant : execve() avec args.
	── Dans le parent : waitpid() pour attendre l’enfant.

- main.h
 a. Définit toutes les fonctions et inclut les bibliothèques nécessaires.
 b. Déclare extern char **environ; pour l’environnement.