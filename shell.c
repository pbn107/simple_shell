#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void get_commands(char * commands, char ** args);
int get_line(char *buffer);

int main(int argc, char **argv, char **envp)
{
	char *args[100] = {NULL};
       	char line[1000];
	ssize_t st;

	while (1)
	{
		pid_t id;
		printf("cisfun$ "); 
		fflush(stdout);
		st = get_line(line);

		if (st <= 0)
		{
			printf("Error: could not read the command\n");
			return -1;
		}
		get_commands(line, args);
		if (strcmp("exit",args[0]) == 0)
		{
			break;
		}
		if (strcmp("env", args[0]) == 0)
		{
			int i = 0;
			while(envp[i])
			{
				printf("%s\n",envp[i]);
				i++;
			}
		}

		id = fork();
		if (id == 0)
		{
			char path[100];
			strcpy(path, "/bin/");
			strcat(path, args[0]);
			if (execve(path, args, NULL) == -1)
				printf("./shell: No such file or diractory\n", args[0]);
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(NULL);
		}

	}
	
	return (0);
}

void get_commands(char *commands, char **args)
{
	int i = 0;
	char * delim = strdup(" ");

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
	return ;
}

int get_line(char *buffer)
{
	ssize_t n = 0;

	while ((n = read(0, buffer, 1000)) > 0)
	{
		if (n > 1)
		{
			if (buffer[n - 1] == '\n')
			{
				buffer[n-1] = '\0';
				break;
			}
		}
		else
		{
			n = -1;
			break;
		}
	}
	return n;
}
