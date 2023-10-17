#include "shell.h"
#include "globals.c"


/**
 * handle_cd - handle signals
 */
void handle_cd(void)
{
	int p_stat;
	char cwd[1024];

	if (gArgs[1] == NULL && !_getenv("HOME", 1))
	{
		handled_write(STDERR_FILENO, "can't find HOME var!\n", 22);
		return;
	}
	else if (gArgs[1] && _strcmp(gArgs[1], "-") == 0 && !_getenv("OLDPWD", 1))
	{
		status = 1;
		handled_write(STDERR_FILENO, "can't find OLDPWD var!\n", 24);
		return;
	}
	p_stat = chdir(gArgs[1] ? _strcmp(gArgs[1], "-") == 0
		? _getenv("OLDPWD", 1) : gArgs[1] : _getenv("HOME", 1));
	if (p_stat != 0)
	{
		status = 1;
		perror(gArgs[1] ? gArgs[1] : _getenv("HOME", 1));
		return;
	}
	_setenv("OLDPWD", _getenv("PWD", 1));
	getcwd(cwd, sizeof(cwd));
	_setenv("PWD", cwd);
}

/**
 * handled_read - handle signals
 * @fd: int
 * @buff: void
 * @n: int
 * Return: int
 */
int handled_read(int fd, void *buff, size_t n)
{
	int bytes_read;

	bytes_read = read(fd, buff, n);
	if (bytes_read < 0)
		perror("read");
	return (bytes_read);
}

/**
 * handled_write - handle signals
 * @fd: int
 * @buff: void
 * @n: int
 * Return: int
 */
int handled_write(int fd, void *buff, size_t n)
{
	int bytes_written;

	bytes_written = write(fd, buff, n);
	if (bytes_written < 0)
		perror("write");
	return (bytes_written);
}

/**
 * handle_quote - handle signals
 * @c: int
 * @q: void
 * @dq: int
 * Return: int
 */
int handle_quote(char c, int *q, int *dq)
{
	if (c == '\'' && *dq == 0)
	{
		*q = *q == 1 ? 0 : 1;
		return (1);
	}
	else if (c == '\"' && *q == 0)
	{
		*dq = *dq == 1 ? 0 : 1;
		return (2);
	}
	return (0);
}

/**
 * read_whole - handle signals
 * @buff: void
 * @start: int
 * @q: int
 * @dq: int
 * @arrow: int
 * Return: int
 */
int read_whole(char *buff, int start, int *q, int *dq, int arrow)
{
	int bytes_read, i;

	if (start > 0 && arrow > 0)
	handled_write(STDOUT_FILENO, "> ", 3);
	bytes_read = handled_read(STDIN_FILENO, buff + start, 1024);
	if (bytes_read == 0 && start == 0)
		handled_write(STDIN_FILENO, "exit\n", 6),
		free_all(), exit(0);
	if (bytes_read == 0)
		return (-20000);
	for (i = start; i < 1023 && (i - start) < bytes_read && buff[i] != '\0'; i++)
	{
		if (buff[i] == '\'' && *dq == 0)
			*q = *q == 1 ? 0 : 1;
		else if (buff[i] == '\"' && *q == 0)
			*dq = *dq == 1 ? 0 : 1;
	}
	return (bytes_read + ((*dq || *q) &&
		 buff[bytes_read - 1] == '\n' && bytes_read > 0 ?
		read_whole(buff, start + bytes_read, q, dq, 1) : 0));
}
