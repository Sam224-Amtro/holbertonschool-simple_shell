#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void shell_loop(char **argv, char **envp);
void remove_trailing_newline(char *line);
char **parse_line(char *line);
char **_realloc_args(char **args, int old_size, int new_size);
int handle_builtin(char **args, char **envp, char *line);
void free_args(char **args);

int handle_builtin(char **args, char **envp, char *line);
int execute_command(char *cmd, char **args, char **envp);
char *find_full_path(char *command, char **envp);
char *get_path_from_env(char **envp);

#endif /* MAIN_H */
