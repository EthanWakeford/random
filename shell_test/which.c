#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>



char *get_env(const char *name)
{
	extern char **environ;
	int i, j;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (environ[i][0] == name[0])
		{
			for (j = 0; name[j] != '\0'; j++)
			/*checks and matches name with environ variable*/
			{
				if (environ[i][j] != name[j])
					break;
			}
			if (name[j] == '\0')
			/*if null byte then match is found */
			{
				/*return string with given name removed, (ex. just path)*/
				return (environ[i] + (j + 1));
			}
		}
	}
	return (NULL);
}


char *_which(char *function)
{
	DIR *directory;
	struct dirent *entry;
	char *path, *path_tok, *buffer;


	printf("function to find: %s\n", function);
	/*gets path and splits into tokens*/
	path = strdup(get_env("PATH"));
	printf("PATH: %s\n", path);
	if (path == NULL)
	{
		printf("get_env failed\n");
		return (NULL);
	}
	path_tok = strtok(path, ":");

	/*moves through each directory in PATH*/
	while (path_tok != NULL)
	{
		printf("Looking in: %s\n", path_tok);
		directory = opendir(path_tok);
		if (directory == NULL)
		{
			printf("unable to read directory\n");
			closedir(directory);
			free(path);
			return (NULL);
		}
		/*moves through each file in directory*/
		while ((entry = readdir(directory)) != NULL)
		{
			/*prints and returns if matching file to function found*/
			if (strcmp(entry->d_name, function) == 0)
			{
				printf("FOUND: %s: %s\n", entry->d_name, path_tok);
				closedir(directory);
				/* +2 bytes for null terminater and '/'  */
				buffer = malloc(strlen(path_tok) + 2 + strlen(function));
				if (buffer == NULL)
				{
					free(path);
					return (NULL);
				}
				buffer = strcpy(buffer, path_tok);
				free(path);
				return (strcat(strcat(buffer, "/"), function));
			}
		}
		path_tok = strtok(NULL, ":");
		closedir(directory);
	}
	printf("Not found\n");
	free(path);
	return (NULL);
}
