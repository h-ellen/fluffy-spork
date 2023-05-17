#include "shell.h"

/**
 * shellPrompt - Displays the prompt for the shell
 * Return: always zero
 */
void shellPrompt()
{
	printf("user$ ");
}

/**
 * chgDir - Method to change directory
 */
int chgDir(char* args[])
{
	/*If no path, then go to the home directory*/
	if (args[1] == NULL)
	{
		chdir(getenv("HOME")); 
		return 1;
	}
	else
	{ 
		if (chdir(args[1]) == -1)
		{
			printf(" %s: no such directory\n", args[1]);
			return -1;
		}
	}
	return 0;
}

/**
 * man_env - Method used to manage the environment variables
 * Return: always zero
 */ 
int man_env(char * args[], int option)
{
	char **env_aux;
	switch(option)
	{
		case 0: 
			for(env_aux = environ; *env_aux != 0; env_aux ++)
			{
				printf("%s\n", *env_aux);
			}
			break;
		/*Case 'setenv': we set an environment variable to a value*/
		case 1: 
			if((args[1] == NULL) && args[2] == NULL)
			{
				printf("%s","Not enought input arguments\n");
				return -1;
			}
			if(getenv(args[1]) != NULL)
			{
				printf("%s", "The variable has been overwritten\n");
			}
			else
			{
				printf("%s", "The variable has been created\n");
			}
			
			/*If we specify no value for the variable, we set it to ""*/
			if (args[2] == NULL)
			{
				setenv(args[1], "", 1);
			}
			else
			{
				setenv(args[1], args[2], 1);
			}
			break;
		/*Case 'unsetenv': we delete an environment variable*/
		case 2:
			if(args[1] == NULL)
			{
				printf("%s","Not enought input arguments\n");
				return -1;
			}
			if(getenv(args[1]) != NULL)
			{
				unsetenv(args[1]);
				printf("%s", "The variable has been erased\n");
			}
			else
			{
				printf("%s", "The variable does not exist\n");
			}
		break;
	}
	return 0;
}
