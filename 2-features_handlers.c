#include "shell.h"

/**
 * handle_cd - handle signals
 */
void handle_cd(void)
{
	int status;
	char cwd[1024], owd[1024];
	char *arg;

	status = chdir(gArgs[1] ? _strcmp(gArgs[1], "-") == 0 ? _getenv("OLDPWD", 1) : gArgs[1] : _getenv("HOME", 1));
	if (status != 0)
	{
		perror(gArgs[1] ? gArgs[1] : _getenv("HOME", 1));
		return;
	}
	_setenv("OLDPWD", _getenv("PWD", 1));
	getcwd(cwd, sizeof(cwd));
	_setenv("PWD", cwd);
}
