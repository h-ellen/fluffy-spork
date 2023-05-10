#include "shell.h"

/**
 *commands - Method used to handle the commands in stdin
 *Return: always 0
 */ 
int commands(char *args[])
{
	int a = 0;
	int b = 0;
	
	int fileDesc;
	int stdOut;
	
	int aux;
	int bkground = 0;
	
	char *args_aux[256];
	
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
				fileDesc = open(args[b+1], O_CREAT | O_TRUNC | O_WRONLY, 0600); 
				/*We replace stdo with the appropriate file*/
				stdOut = dup(STDOUT_FILENO); 
				
				dup2(fileDesc, STDOUT_FILENO); 
				close(fileDes);
				printf("%s\n", getcwd(current_dir, 1024));
				dup2(stdOut, STDOUT_FILENO);
			}
		}
		else
		{
			printf("%s\n", getcwd(current_dir, 1024));
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
				fileDesc = open(args[b+1], O_CREAT | O_TRUNC | O_WRONLY, 0600); 

				stdOut = dup(STDOUT_FILENO);
				dup2(fileDesc, STDOUT_FILENO); 
				close(fileDesc);
				man_env(args,0);
				dup2(stdOut, STDOUT_FILENO);
			}
		}
		else
		{
			man_env(args,0);
		}
	}
	else if (strcmp(args[0],"setenv") == 0)
    man_env(args,1);

	else if (strcmp(args[0],"unsetenv") == 0)
    man_env(args,2);
  else
  {
    while (args[a] != NULL && bkground == 0)
    {
      if (strcmp(args[a],"&") == 0)
      {
        bkground = 1;
      }
			else if (strcmp(args[a],"|") == 0)
			{
				pipe_handler(args);
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
				files(args_aux,args[a+1],args[a+3],1);
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
				files(args_aux,NULL,args[a+1],0);
				return 1;
			}
			a++;
		}

		args_aux[a] = NULL;
		prog_launch(args_aux,bkground);
	}
	return 1;
}
