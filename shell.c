#include "shell.h"

/**
 * main - the starting point of shell
 * @ac: arguments count
 * @av: arguments pointers
 * Return: 0 on Success
 */
int main(__attribute__((unused)) int ac, char **av)
{
	init_global_vars(av[0]);
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
 * @pname: char
 */
void init_global_vars(char *pname)
{
	int i;

	cmd_count = 0;
	program_name = pname;
	gArgs = NULL;
	cmds = NULL;
	for (i = 0; i < 100; i++)
		env_vars[i] = NULL;
}

/**
 * handle_piped_shell - handle signals
 * Return: 0 on Success
 */
int handle_piped_shell(void)
{
	int total, bytes_read, handled_bytes, len;

	if (isatty(STDIN_FILENO) != 0)
		return (1);
	len = 0, total = 0;
	handled_bytes = 0, status = 0, bytes_read = 1;
	while (bytes_read != 0)
	{
		len += 1024, pipe_data[0] = (char *)_realloc(pipe_data[0], len - 1024, len);
		bytes_read = handled_read(STDIN_FILENO, pipe_data[0] + total, 1024);
		total += bytes_read;
	}
	bytes_read = total;
	pipe_data[1] = (char *)_realloc(pipe_data[1], 0, len);
	if (bytes_read <= 0)
		return (-1);
	if (pipe_data[0][bytes_read - 1] == '\n')
		pipe_data[0][bytes_read - 1] = '\0';
	while (handled_bytes < bytes_read)
		handled_bytes += cp_line(pipe_data[0] + handled_bytes, pipe_data[1]),
		command_process(pipe_data[1]);
	free_all();
	exit(handle_status(status));
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
