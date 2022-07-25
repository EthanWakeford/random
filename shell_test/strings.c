#include "main.h"

char *strcpycat(char *dest, char *src)
{
	int d, s;
	char *new_str;

	new_str = malloc(strlen(dest) + strlen(src) + 1);

	for (d = 0; dest[d] != '\0'; d++)
	{
		new_str[d] = dest[d];
	}
	for (s = 0; src[s] != '\0'; s++, d++)
	{
		new_str[d] = src[s];
	}
	new_str[d] = '\0';
	return (new_str);
}
