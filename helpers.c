#include "helpers.h"

/**
 * get_commands - converts the a string of commands an array of commands
 * @commands: string of arguments
 * @args: array of commands
 */

void get_commands(char *commands, char **args)
{
	int i = 0;
	char *delim = strdup(" ");

	args[i] = strtok(commands, delim);
	for (i = 1; i < 100; i++)
	{
		args[i] = strtok(NULL, delim);
		if (args[i] == NULL)
		{
			args[i] = NULL;
			break;
		}
	}
}

/**
 * get_line - gets a line of arguments from the user
 * @buffer: pointer to a the an array to store the line
 * Return: 0 if no characters were read otherwise number of characters
 */

int get_line(char *buffer)
{
	ssize_t n = 0;

	while ((n = read(0, buffer, 1000)) > 0)
	{
		if (n > 1)
		{
			if (buffer[n - 1] == '\n')
			{
				buffer[n - 1] = '\0';
				break;
			}
		}
		else
		{
			n = -1;
			break;
		}
	}
	return (n);
}

/**
 * execute - executes commands
 * @args: array of strings
 * Return: 0 on failure
 */
int execute(char **args)
{
	char path[100];

	strcpy(path, "/bin/");
	strcat(path, args[0]);

	if (execve(path, args, NULL) == -1)
		printf("./shell: No such file or directory\n");

	exit(EXIT_FAILURE);
}

/**
 * _env - prints the environment variables of a process
 * @environ: array of enviroment variables (strings)
 */

void _env(char **environ)
{
	int i = 0;

	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
}

/**
 * print_cursor - prints the cursor  for the shell
 */

void print_cursor(void)
{
	printf("cisfun$ ");
	fflush(stdout);
}



















