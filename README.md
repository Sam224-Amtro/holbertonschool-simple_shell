
_ FEUILLE DE ROUTE _
 1. Fichiers principaux

main.c
→ Contient la boucle principale :

Affiche le prompt ($ en mode interactif).

Lit la ligne avec getline.

Parse la ligne (parse_line).

Vérifie si c’est un builtin (handle_builtin).

Cherche le chemin complet (find_full_path).

Exécute la commande (execute_command).

Libère la mémoire.

parse_line.c
→ Découpe la ligne en tokens (arguments), renvoie un tableau terminé par NULL.
→ Inclut une fonction free_args pour libérer ce tableau.

builtins.c
→ Gère les commandes internes :

exit → quitte le shell.

env → affiche l’environnement.

execute_command.c
→ Fork + execve.
→ Retourne le code d’état du processus.
→ Affiche un message d’erreur si execve échoue.

path.c
→ get_env_path → récupère PATH depuis environ.
→ find_full_path → construit le chemin complet d’une commande (/bin/ls, /usr/bin/gcc, etc.).

helpers.c (optionnel)
→ Fonctions d’aide (_realloc_args, free_args, etc.).

main.h
→ Header avec toutes les déclarations de fonctions + includes.

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
