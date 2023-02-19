#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int get_line(char *str);

int main (void)
{
	char buff[1000];
	get_line(buff);
	printf("%s \n",buff);
	return 0;
}

int get_line(char *buffer)
{
	int n = 0;

	while ((n = read(0, buffer, 1000)) > 0)
	{
		if (buffer[n - 1] == '\n')
		{
			buffer[n-1] = '\0';
			break;
		}
	}
}
