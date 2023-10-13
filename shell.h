#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

extern char **environ;
char **gArgs = NULL;
char *env_vars[100];

/*Handlers*/
void handle_shell();
int handle_piped_shell();

void handle_unsetenv();
void handle_setenv();
void handle_getenv();
void handle_exit();

void interrupt_handler();
void signal_handler(int signal_number);

/*Utils*/
int _strlen(char *s);
int str_to_int(char *s);
int contains(char *s, char c);
int nonexact_strcmp(char *s1, char *s2);
void str_append(char *from, char *to, int start);
int _strcmp(char *s1, char *s2);
int count_words(char *s);

/*Cycle functions*/
void alloc_err();
void free_all();
int fill_args(int count, char *buffer);
int _getline(char *buffer);

/*Command functions*/
void exe_command();
void exe_ncommand();
void command_process(char *buffer);
void exe_path();
void command_to_path();

/*Env related functions*/
char *_getenv(char *name, int val_only);
void _setenv(char *name, char *value);
void realloc_environ(char *var, int op);

void handle_cd();

#endif
