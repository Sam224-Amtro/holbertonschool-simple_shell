#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* utils */
void remove_trailing_newline(char *line);
char **parse_line(char *line);
char **_realloc_args(char **args, int old_size, int new_size);
void free_args(char **args);
char *my_strdup(const char *s);

/* PATH */
char *get_path_from_env(char **envp);
char *find_full_path(const char *command, char **envp);

/* builtins / exec */
int handle_builtin(char **args, char **envp, char *line);
int execute_command(char *command, char **args, char **envp);

/* loop */
void shell_loop(char **argv, char **envp);

#endif /* MAIN_H */