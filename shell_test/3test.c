#include <string.h>
#include <stdio.h>

int main(void)
{
	char *str = "hello";
	char *tok;

	tok = strtok(str, " ");
	printf("%s\n", tok);
	tok = strtok(NULL, " ");

	if (tok != NULL)
		printf("%s\n", tok);
	return (0);
}
