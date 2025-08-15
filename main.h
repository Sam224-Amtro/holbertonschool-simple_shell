#ifndef MAIN_H
#define MAIN_H

#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n"

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

void remove_trailing_newline(char *str);
char *get_path_from_env(char **envp);


char **parse_line(char *line);
void execute_command(char *line);
void shell_loop(char **argv, char **envp);
int main(int argc, char **argv, char **envp);
char *find_full_path(char *command, char **envp);
char **parse_line(char *line);

#endif
