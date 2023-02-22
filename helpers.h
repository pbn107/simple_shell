#ifndef HELPERS_H
#define HELPERS_H
#include "shell.h"

void get_commands(char *commands, char **args);
int get_line(char *buffer);
void print_cursor(void);
void _env(char **environ);
int execute(char **args);

#endif
