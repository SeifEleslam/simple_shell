#include "shell.h"

/**
 * custom_perror - function
 * @msg: char*
 */
void custom_perror(char *msg)
{
	char n[10];

	int_to_str(cmd_count, n, _intlen(cmd_count, 10), 0);
	handled_write(STDERR_FILENO, program_name, _strlen(program_name));
	handled_write(STDERR_FILENO, ": ", 2);
	handled_write(STDERR_FILENO, n, _intlen(cmd_count, 10));
	handled_write(STDERR_FILENO, ": ", 2);
	handled_write(STDERR_FILENO, gArgs[0], _strlen(gArgs[0]));
	handled_write(STDERR_FILENO, ": ", 2);
	handled_write(STDERR_FILENO, msg, _strlen(msg));
	handled_write(STDERR_FILENO, "\n", 1);
}
