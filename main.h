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

/* main.c */
int main(int argc, char **argv);
void shell_loop(void);

/* parser.c */
char *read_line(void);
char **parse_line(char *line);

/* execute.c */
void execute_command(char **args);
void test_env(char **env);
void search_path(int ac, char **av);



/* utils.c */
void free_args(char **args);
void print_error(char *prog_name, char *cmd);
void remove_trailing_newline(char *str);

#endif