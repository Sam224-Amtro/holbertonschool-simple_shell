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
void remove_trailing_newline(char *line);

/* parser.c */
char *read_line(void);
char **parse_line(char *line);
int count_tokens(char *line);

/* execute.c */
int execute_command(char **args);

/* utils.c */
void free_args(char **args);
void print_error(char *prog_name, char *cmd);

#endif