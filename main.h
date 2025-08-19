#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

extern char **environ;

/* shell.c */
void shell_loop(void);

/* parser.c */
char *read_line(void);
char **parse_line(char *line);

/* execute.c */
int execute_command(char *command, char **args, char **envp);

/* builtin.c */
int handle_builtin(char **args, char **envp, char *line);

/* path.c */
char *get_env_path(char **envp);
char *find_full_path(char *command, char **envp);

/* utils.c */
char **_realloc_args(char **args, int old_size, int new_size);
void free_args(char **args);
void print_error(char *prog_name, char *cmd);
void remove_trailing_newline(char *str);

#endif /* MAIN_H */