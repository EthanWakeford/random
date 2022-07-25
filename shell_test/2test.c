#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};
	pid_t is_kid;
	int i;

	for (i = 0; i < 5; i++)
	{
		if (is_kid != 0)
		{
			wait(NULL);
			is_kid = fork();
		}
		else
		{
			if (execve(argv[0], argv, NULL) == -1)
				perror("Error\n");
		}
	}
	return (0);
}
