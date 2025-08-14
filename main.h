#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

void remove_trailing_newline(char *str);


char **parse_line(char *line);
void execute_command(char *line);
void shell_loop(char **argv, char **envp);
int main(int argc, char **argv, char **envp);

#endif
