#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *buffer = NULL;
	size_t bufsize;

	getline(&buffer, &bufsize, stdin);
	printf("%s\n", buffer);
	free(buffer);
	return (0);
}
