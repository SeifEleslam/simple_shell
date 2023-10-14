#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>

extern char **environ;
static char **gArgs;
static char *env_vars[100];

/*Handlers*/
void handle_shell(void);
int handle_piped_shell(void);
void init_global_vars(void);

void handle_unsetenv(void);
void handle_setenv(void);
void handle_getenv(void);
void handle_exit(void);

void interrupt_handler(void);
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
void alloc_err(void);
int handled_read(int fd, void *buff, size_t n);
int handled_write(int fd, void *buff, size_t n);

void free_all(void);
int fill_args(int count, char *buffer);
int _getline(char *buffer);

/*Command functions*/
void exe_command(void);
void exe_ncommand(void);
void command_process(char *buffer);
void exe_path(void);
void command_to_path(void);

/*Env related functions*/
char *_getenv(char *name, int val_only);
void _setenv(char *name, char *value);
void realloc_environ(char *var, int op);

void handle_cd(void);

#endif
