#include "shell.h"

/**
 * main - the starting point of shell
 * @ac: arguments count
 * @av: arguments pointers
 * Return: 0 on Success
 */
int main(int ac, char *av)
{
	init_global_vars();
	signal(SIGINT, signal_handler);
	if (handle_piped_shell() == 0)
		return (0);
	handle_shell();
	return (0);
}

/**
 * signal_handler - handle signals
 * @signal_number: signal code
 */
void signal_handler(int signal_number)
{
	switch (signal_number)
	{
	case SIGINT:
		interrupt_handler();
		break;
	default:
		break;
	}
}

/**
 * init_global_vars - handle ^C
 */
void init_global_vars(void)
{
	int i;

	gArgs = NULL;
	for (i = 0; i < 100; i++)
		env_vars[i] = NULL;
}

/**
 * handle_piped_shell - handle signals
 * Return: 0 on Success
 */
int handle_piped_shell(void)
{
	int bytes_read, count;
	char buffer[1024];

	if (isatty(STDIN_FILENO) != 0)
		return (1);
	bytes_read = handled_read(STDIN_FILENO, buffer, sizeof(char) * 1024);
	if (bytes_read < 0)
		return (1);
	command_process(buffer);
	return (0);
}

/**
 * handle_shell - handle signals
 */
void handle_shell(void)
{
	char buffer[1024];

	while (1)
	{
		handled_write(1, "simple_shell$ ", 15);
		if (_getline(buffer) != 0)
			continue;
		command_process(buffer);
	}
}
