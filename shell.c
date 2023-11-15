#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h> /* handle strings */
/**
 * main - entry point of the program
 * Return: termination status of the program.
 **/

int main(void)
{
	size_t buffer_size = 0;
	char *buffer = NULL;
	char *stoken;
	int status, i = 0;
	char **array;
	pid_t child_pid;

	while (1) /* looping to ensure we always get data */
	{
		write(1, "#cisfun$ ", 9); /* write 1 for STDOUT 9 characters  */
		getline(&buffer, &buffer_size, stdin); /* read fom STDIn */
		stoken = strtok(buffer, "\t\n");
		array = malloc(sizeof(char *) * 1024); /*  allocating memory */

		while (stoken)
		{
			array[i] = stoken;
			stoken = strtok(NULL, "\t\n");
			i++;
		}
		array[i] = NULL;
		child_pid = fork();

		if (child_pid == 0) /* using child to run command  */
		{
			if (execve(array[0], array, NULL) == -1)
				perror("Error with the Exec...");
		}
		else
		{
			wait(&status);
		}
		i = 0;
		free(array);
	}
	return (EXIT_SUCCESS);
}
