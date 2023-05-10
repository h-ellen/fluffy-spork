#include "shel.h"

/**
 *commandHandler - Method used to handle the commands in stdin
 *Return: always 0
 */ 
int commandHandler(char *args[])
{
	int a = 0;
	int b = 0;
	
	int fileDescriptor;
	int standardOut;
	
	int aux;
	int background = 0;
	
	char *args_aux[256];
	
	/*We look for the special characters and separate the command itself*/
	/*in a new array for the arguments*/
	while ( args[b] != NULL)
	{
		if ( (strcmp(args[b],">") == 0) || (strcmp(args[b],"<") == 0) || (strcmp(args[b],"&") == 0))
		{
			break;
		}
		args_aux[b] = args[b];
		b++;
	}
	
	/*'exit' command quits the shell*/
	if(strcmp(args[0],"exit") == 0)
		exit(0);
  
	/*'pwd' command prints the current directory*/
 	else if (strcmp(args[0],"pwd") == 0)
	{
		if (args[b] != NULL)
		{
			/*If we want file output*/
			if ( (strcmp(args[b],">") == 0) && (args[b+1] != NULL) )
			{
				fileDescriptor = open(args[b+1], O_CREAT | O_TRUNC | O_WRONLY, 0600); 
				/*We replace stdo with the appropriate file*/
				standardOut = dup(STDOUT_FILENO); 
				/*first we make a copy of stdout because we'll want it back*/

				dup2(fileDescriptor, STDOUT_FILENO); 
				close(fileDescriptor);
				printf("%s\n", getcwd(currentDirectory, 1024));
				dup2(standardOut, STDOUT_FILENO);
			}
		}
		else
		{
			printf("%s\n", getcwd(currentDirectory, 1024));
		}
	}
  
 	/*'clear' command clears the screen*/
	else if (strcmp(args[0],"clear") == 0)
    system("clear");
  
	/*'cd' command to change directory*/
	else if (strcmp(args[0],"cd") == 0)
    chgDir(args);
  
	/*'environ' command to list the environment variables*/
	else if (strcmp(args[0],"environ") == 0)
	{
		if (args[b] != NULL)
		{
			/*If we want file output*/
			if ( (strcmp(args[b],">") == 0) && (args[b+1] != NULL) )
			{
				fileDescriptor = open(args[b+1], O_CREAT | O_TRUNC | O_WRONLY, 0600); 
				/*We replace the standard output with the appropriate file*/
				standardOut = dup(STDOUT_FILENO);
				dup2(fileDescriptor, STDOUT_FILENO); 
				close(fileDescriptor);
				manageEnviron(args,0);
				dup2(standardOut, STDOUT_FILENO);
			}
		}
		else
		{
			manageEnviron(args,0);
		}
	}
  
	/*'setenv' command to set environment variables*/
	else if (strcmp(args[0],"setenv") == 0)
    manageEnviron(args,1);
  
	/*'unsetenv' command to undefine environment variables*/
	else if (strcmp(args[0],"unsetenv") == 0)
    manageEnviron(args,2);
  else
  {
    while (args[a] != NULL && background == 0)
    {
      if (strcmp(args[a],"&") == 0)
      {
        background = 1;
      }
			else if (strcmp(args[a],"|") == 0)
			{
				pipeHandler(args);
				return 1;
			}
			/**
			 *If '<' is detected, we have Input and Output redirection.
			 * First we check if the structure given is the correct one,
			 * and if that is the case we call the appropriate method
			 */
			else if (strcmp(args[a],"<") == 0)
			{
				aux = a+1;
				if (args[aux] == NULL || args[aux+1] == NULL || args[aux+2] == NULL )
				{
					printf("Not enough input arguments\n");
					return -1;
				}
				else
				{
					if (strcmp(args[aux+1],">") != 0)
					{
						printf("Usage: Expected '>' and found %s\n",args[aux+1]);
						return -2;
					}
				}
				fileIO(args_aux,args[a+1],args[a+3],1);
				return 1;
			}
			/**
			 *If '>' is detected, we have output redirection.
			 * First we check if the structure given is the correct one,
			 * and if that is the case we call the appropriate method
			 */
			else if (strcmp(args[a],">") == 0)
			{
				if (args[a+1] == NULL)
				{
					printf("Not enough input arguments\n");
					return -1;
				}
				fileIO(args_aux,NULL,args[a+1],0);
				return 1;
			}
			a++;
		}

		args_aux[a] = NULL;
		launchProg(args_aux,background);
	}
	return 1;
}
