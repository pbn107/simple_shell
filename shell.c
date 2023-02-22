#include "helpers.h"

/**
 * exit_shell - exits the shell
 * @args: array of strings
 * Return: 0 or status code
 */

int exit_shell(char **args)
{
	if (args[1] != NULL && args[2] == NULL)
	{
		int status = atoi(args[1]);

		exit(status);
	}
	else if (args[1] == NULL)
	{
		exit(EXIT_SUCCESS);
	}
	perror("usage: exit or exit <exit code>\n");
	exit(EXIT_FAILURE);
}

/**
 * _setenv - sets an environmental variable
 * @args: array of strings
 * Return: always
 */

int _setenv(char **args)
{
	int res = setenv(args[1], args[2], 1);
	char *str;

	if (res == -1)
	{
		printf("Error: usage setenv VARIABLE VALUE\n");
	}

	str = getenv(args[1]);
	printf("%s\n", str);
	exit(EXIT_SUCCESS);
}

/**
 * _unsetenv - removes an environment variable
 * @args: string of arrays
 * Return: EXIT_SUCCESS
 */

int _unsetenv(char **args)
{
	int res = unsetenv(args[1]);

	if (res == -1)
	{
		printf("Error: usage unsetenv VARIABLE\n");
	}
	exit(EXIT_SUCCESS);
}

/**
 * main - shell program
 * @argc: number of cmd arguments
 * @argv: array of cmd arguments
 * *envp: environment variables
 * Return: EXIT_SUCESS
 */

int main(int argc, char **argv, char ** envp)
{
	char *str = argv[argc-1];
	char *args[100] = {NULL};
	char line[1000];
	ssize_t st;
	
	if (strcmp(str, "haha")== 0)
		printf("yebo\n");

	while (1)
	{
		print_cursor();

		st = get_line(line);
		get_commands(line, args);

		if (strcmp("exit", args[0]) == 0)
			exit_shell(args);
		if (fork() == 0)
		{
			if (st <= 0)
				exit(EXIT_FAILURE);
			if (strcmp("setenv", args[0]) == 0)
				_setenv(args);
			if (strcmp("unsetenv", args[0]) == 0)
				_unsetenv(args);
			if (strcmp("env", args[0]) == 0)
				_env(envp);

			execute(args);
		}
		else
			wait(NULL);
	}
	exit(EXIT_SUCCESS);
}
