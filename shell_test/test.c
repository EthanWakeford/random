#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "main.h"

int count_del(char *str)
{
	int count = 0, index;

	for (index = 0; str[index] != '\0'; index++)
	{
		if (str[index] == ' ')
		count++;
	}
	return (count + 1);
}


int main(int ac, char **av, char **env)
{
	char *buffer = NULL, *tok;
	char **argv = NULL;
	size_t bufsize;
	unsigned int index = 0, tok_size, is_mall = 0;
	pid_t is_kid;
	struct stat st;

	if (ac > 1)
	{
		(void)ac;
		(void)av;
	}

	while (1)
	{
		printf("$ ");
		getline(&buffer, &bufsize, stdin);

		if (strcmp(buffer, "exit\n") == 0)
			break;

		tok_size = count_del(buffer);
		argv = malloc(sizeof(*argv) * (tok_size + 1));
		printf("malloc size = %d\n", tok_size + 1);
		if (argv == NULL)
		{
			printf("malloc fail\n");
			continue;
		}
		tok = strtok(buffer, " \n");
		/*init each value of argv*/
		for (index = 0; tok != NULL; index++)
		{
			argv[index] = tok;
			tok = strtok(NULL, " \n");
		}
		
		if (stat(argv[0], &st) == -1)
		{
			argv[0] = _which(argv[0]);
			is_mall = 1;
			if (argv[0] == NULL)
			{
				printf("invalid command\n");
				free(argv);
				continue;
			}
		}
		printf("new argv[0]: %s\n", argv[0]);

		argv[index] = NULL;
		/*fork process and child runs execve*/
		printf("running command\n");
		is_kid = fork();
		if (is_kid == 0)
		{
			if (execve(argv[0], argv, env) == -1)
			{
				printf("execute fail\n");
				exit(100);
			}
		}
		else
		{
			wait(NULL);
		}
		if (is_mall)
			free(argv[0]);
		free(argv);
		is_mall = 0;
	}
	free(buffer);
	return (0);
}
