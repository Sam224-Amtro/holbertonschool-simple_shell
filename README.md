# 💻🧠 Simple Shell — Projet C (Ubuntu 20.04)

**Langage :** C • **Norme :** Betty • **Plateforme :** Ubuntu 20.04 • **Objectif :** Shell minimaliste conforme à `/bin/sh` pour les cas standards • **Qualité :** Memory-safe (sans fuite)

---

## 👥 Auteurs

* Sanoussy fofana c27
* Georgia Boulnois

---

## 📖 Sommaire

1. [Introduction](#-introduction)
2. [Objectif du projet](#-objectif-du-projet)
3. [Flowchart](#-flowchart)
4. [Arborescence du projet](#-arborescence-du-projet)
5. [Compilation / Man page](#-compilation--man-page)
6. [Exemples et sorties](#-exemples-et-sorties)
7. [Liste des fonctions](#-liste-des-fonctions)
8. [Contraintes](#-contraintes)
9. [Sources / Références](#-sources--références)

---

## 1️⃣ Introduction

Ce projet (programme **`hsh`**) s’inscrit dans la formation Holberton. Il implémente un **mini-interpréteur de commandes** en C : lecture de l’entrée, parsing, recherche dans le `$PATH`, exécution via `execve`, gestion de quelques **builtins** (`exit`, `env`) et **comportement équivalent** à `/bin/sh` dans les cas standards.

---

## 2️⃣ Objectif du projet

* Reproduire un **shell minimaliste** en C, proche de `/bin/sh`.
* Gérer les **modes interactif** (prompt `$`) et **non‑interactif** (pipe/fichier).
* Lire, parser (tokenizer), exécuter via **`fork` + `execve` + `wait`**.
* Implémenter les **builtins** : `exit`, `env`.
* Recherche des commandes dans le **`$PATH`**.
* Gestion d’erreurs standard (codes de retour, messages `perror`, `127` si commande introuvable).
* **Aucune fuite mémoire** (vérifié avec `valgrind`).
* Respect strict de la **norme Betty** (≤ 5 fonctions par fichier).
* Utilisation **exclusivement** des appels systèmes autorisés.
* Architecture **claire, modulaire et évolutive**.

---

## 3️⃣ Flowchart

> Diagramme du flux principal (lecture → parsing → builtin → recherche PATH → exécution)

```mermaid
flowchart TD
    A[Start hsh] --> B{stdin ?}
    B -->|isatty==true| C[Afficher prompt "$ "]
    B -->|isatty==false| D[Pas de prompt]
    C --> E[getline(line)]
    D --> E[getline(line)]
    E -->|EOF| Z[Exit (dernier status)]
    E --> F[remove_trailing_newline]
    F --> G[parse_line(line) -> args]
    G -->|args[0]==NULL| C
    G --> H{handle_builtin(args)}
    H -->|true| C
    H -->|false| I[find_full_path(args[0], $PATH)]
    I -->|trouvé| J[fork/execve(args)]
    I -->|non trouvé| K[stderr: "hsh: 1: cmd: not found" ; status=127]
    J --> L[wait & récupérer status]
    L --> C
    K --> C
```

---

## 4️⃣ Arborescence du projet

```
/holbertonschool-simple_shell
│
├── AUTHORS
├── builtins.c
├── execute.c
├── handle_path.c
├── main.c
├── main.h
├── man_1_simple_shell
├── parse_input.c
├── README.md
└── utils.c
```

> **Note :** Les noms de fichiers correspondent aux fonctionnalités listées plus bas (ex. `parse_input.c` contient `parse_line`).

---

## 5️⃣ Compilation / Man page

### Compilation

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

### Lancer la page de manuel

```bash
man ./man_1_simple_shell
```

### Vérifier la norme Betty

```bash
betty *.c *.h
```

### Détection de fuites mémoire (exemples)

```bash
valgrind --leak-check=full --show-leak-kinds=all ./hsh

echo "ls -l" | valgrind --leak-check=full ./hsh
```

---

## 6️⃣ Exemples et sorties

### Mode interactif

```console
$ ./hsh
$ ls
AUTHORS  builtins.c  execute.c  handle_path.c  main.c  main.h  man_1_simple_shell  parse_input.c  README.md  utils.c
$ echo Hello Axel, my Favorite SWE !
Hello Axel, my Favorite SWE !
$ exit
```

### Mode non‑interactif

```console
$ echo "ls" | ./hsh
AUTHORS  builtins.c  execute.c  handle_path.c  main.c  main.h  man_1_simple_shell  parse_input.c  README.md  utils.c

$ echo "echo Hello Axel, my Favorite SWE !" | ./hsh
Hello Axel, my Favorite SWE !
```

---

## 7️⃣ Liste des fonctions

| Fichier         | Fonction                  | Rôle / Description                                  |
| --------------- | ------------------------- | --------------------------------------------------- |
| `main.c`        | `main`                    | Point d’entrée. Lance `shell_loop`.                 |
| `main.c`        | `shell_loop`              | Boucle principale : prompt, lecture, exécution.     |
| `main.c`        | `remove_trailing_newline` | Nettoie le `\n` final de l’entrée.                  |
| `builtins.c`    | `handle_builtin`          | Exécute les builtins (`exit`, `env`).               |
| `builtins.c`    | `free_args`               | Libère le tableau `args` (sans libérer les tokens). |
| `execute.c`     | `execute_command`         | `fork` + `execve` + `wait` sur la commande.         |
| `parse_input.c` | `parse_line`              | Découpe la ligne utilisateur en tokens (`args[]`).  |
| `utils.c`       | `_realloc_args`           | Réalloue dynamiquement le tableau `args[]`.         |
| `handle_path.c` | `find_full_path`          | Cherche le binaire dans les répertoires de `$PATH`. |
| `utils.c`       | `get_path_from_env`       | Récupère la valeur de `$PATH` depuis `envp`.        |

> **Convention parseur :** `parse_line` stocke des **pointeurs dans `line` (via `strtok`)** → ne pas `free(args[i])`. Toujours `free(args)` et `free(line)` le cas échéant.

---

## 8️⃣ Contraintes

* **Norme Betty** stricte, **≤ 5 fonctions** par fichier.
* **Aucune fuite mémoire** (contrôlé par `valgrind`).
* Modes **interactif** et **non‑interactif** supportés.
* **Compatibilité `/bin/sh`** sur les cas standards.
* **Format d’erreur** identique, hormis le nom du programme (`argv[0]`).

### Format d’erreur attendu

```console
$ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
```

### Appels systèmes et fonctions autorisés

* **`string.h`** (fonctions standard)
* `access` • `chdir` • `close` • `closedir` • `execve` • `exit` • `_exit`
* `fflush` • `fork` • `free` • `getcwd` • `getline` • `getpid` • `isatty`
* `kill` • `malloc` • `open` • `opendir` • `perror` • `printf`/`fprintf`/`vfprintf`/`sprintf`
* `putchar` • `read` • `readdir` • `signal`
* `stat`/`__xstat` • `lstat`/`__lxstat` • `fstat`/`__fxstat`
* `strtok` • `wait`/`waitpid`/`wait3`/`wait4` • `write`

---

## 9️⃣🔗 Sources / Références

* Pages **`man`** officielles (2, 3)
* Cours & projets Holberton School
* Page de manuel de `sh` et tests comparatifs avec `/bin/sh`
* ChatGPT (assistance)

### Outils utilisés

* **valgrind** — détection de fuites mémoire
* **gcc** — compilation stricte (`-Wall -Werror -Wextra -pedantic -std=gnu89`)
* **betty** — vérification de style

---

## ✅ Astuces pratiques

* Toujours vérifier `isatty(STDIN_FILENO)` pour afficher le prompt seulement en interactif.
* Bien **libérer** : `free(args)` et `free(line)` quand nécessaire ; `args[i]` ne doit **pas** être libéré si vient de `strtok`.
* S’assurer que `find_full_path` **alloue** le chemin renvoyé (pour pouvoir `free(full_path)`).
* En non‑interactif, retourner le **dernier code de sortie** de la commande exécutée.


