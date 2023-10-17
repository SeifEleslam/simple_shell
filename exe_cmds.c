#include "shell.h"

/**
 * exe_command - execute
 */
void exe_command(void)
{
	pid_t pid;

	pid = fork();
	if (pid == 0 && execve(*gArgs, gArgs, environ) == -1)
	{
		perror(*gArgs);
		exit(127);
	}
	wait(&status);
	status = WEXITSTATUS(status);
}

/**
 * exe_ncommand - execute
 */
void exe_ncommand(void)
{
	pid_t pid;
	char buff[1024];

	command_to_path(buff);
	pid = fork();
	if (pid == 0 && _strlen(buff) > 0 && execve(buff, gArgs, environ) == -1)
	{
		perror(*gArgs);
		exit(127);
	}
	wait(&status);
	status = WEXITSTATUS(status);
	buff[0] = '\0';
}

/**
 * command_process - execute
 * buffer: buff
 */
void command_process(char *buffer)
{
	int count, i;

	if (fill_cmds(buffer) != 0)
	return;
	for (i = 0; cmds[i] != NULL; i++)
	{
		count = count_words(cmds[i]);
		if (count <= 0)
			return;
		if (fill_args(count, cmds[i]) != 0)
			return;
		exe_path();
		free_args();
	}
	free_cmds();
}

/**
 * exe_path - execute
 */
void exe_path(void)
{
	if (_strcmp(gArgs[0], "exit") == 0)
		handle_exit();
	else if (_strcmp(gArgs[0], "env") == 0)
		handle_env();
	else if (_strcmp(gArgs[0], "cd") == 0)
		handle_cd();
	else if (_strcmp(gArgs[0], "setenv") == 0)
		handle_setenv();
	else if (_strcmp(gArgs[0], "unsetenv") == 0)
		handle_unsetenv();
	else if (contains(gArgs[0], '/') != 0)
		exe_ncommand();
	else
		exe_command();
}
