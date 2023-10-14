#include "main.h"

/**
 * interrupt_handler - handle signals
 */
void interrupt_handler(void)
{
	free_all(), free_env();
	_exit(0);
}

/**
 * handle_exit - handle signals
 */
void handle_exit(void)
{
	if (gArgs[1] && !gArgs[2])
		free_all(), free_env(), _exit(str_to_int(gArgs[1]));
	free_all(), free_env(), _exit(0);
}

/**
 * handle_env - handle signals
 */
void handle_env(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		handled_write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		handled_write(STDOUT_FILENO, "\n", 1);
	}
}

/**
 * handle_setenv - handle signals
 */
void handle_setenv(void)
{
	if (!gArgs[0] || !gArgs[1] || !gArgs[2])
		handled_write(STDERR_FILENO,
			"Usage: setenv [VARIABLE_NAME] [VARIABLE_VALUE]\n", 48);
	else
		_setenv(gArgs[1], gArgs[2]);
}
