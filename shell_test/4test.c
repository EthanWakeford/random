#include <stdio.h>

/**
 * main - prints the environment
 *
 * Return: Always 0.
 */
int main(int ac, char **av, char **env)
{
    extern char **environ;

	printf("environ add: %p\n", &environ);
	printf("env add: %p\n", &env);
    return (0);
}
