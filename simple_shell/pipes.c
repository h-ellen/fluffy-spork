#include "shel.h"

/**
* pipe_handler - Method used to manage pipes.
* Return: alwayz 0
*/ 
void pipe_handler(char *args[])
{
	/*File descriptors*/
	int filedesc[2];
	int filedesc2[2];
	int nums_cmnd = 0;
	char *comm[256];
	
	pid_t pid;
	
	int error = -1;
	int fin = 0;
	
	int o = 0;
	int p = 0;
	int q = 0;
	int r = 0;
	
	while (args[r] != NULL)
	{
		if (strcmp(args[r],"|") == 0)
		{
			nums_cmnd++;
		}
		r++;
	}
	nums_cmnd++;

	while (args[p] != NULL && fin != 1)
	{
		q = 0;
		while (strcmp(args[p],"|") != 0)
		{
			comm[k] = args[p];
			p++;	
			if (args[p] == NULL)
			{
				fin = 1;
				q++;
				break;
			}
			q++;
		}
		comm[q] = NULL;
		p++;		

		if (o % 2 != 0)
		{
			pipe(filedesc);
		}
		else
		{
			pipe(filedesc2);
		}
		
		pid=fork();
		
		if(pid==-1)
		{			
			if (o != nums_cmnd - 1)
			{
				if (o % 2 != 0)
				{
					close(filedesc[1]);
				}
				else
				{
					close(filedesc2[1]);
				} 
			}			
			printf("Child process could not be created\n");
			return;
		}
		if(pid==0)
		{
			/*If we are in the first command*/
			if (o == 0)
			{
				dup2(filedesc2[1], STDOUT_FILENO);
			}
		
			else if (o == nums_cmnd - 1)
			{
				if (nums_cmnd % 2 != 0)
				{ 
					/*for odd number of commands*/
					dup2(filedesc[0],STDIN_FILENO);
				}
				else
				{ 
					/*for even number of commands*/
					dup2(filedesc2[0],STDIN_FILENO);
				}

			}
			else
			{ 
				if (o % 2 != 0)
				{
					dup2(filedesc2[0],STDIN_FILENO); 
					dup2(filedesc[1],STDOUT_FILENO);
				}
				else
				{
					dup2(filedesc[0],STDIN_FILENO); 
					dup2(filedesc2[1],STDOUT_FILENO);					
				} 
			}
			
			if (execvp(comm[0],comm)==error)
			{
				kill(getpid(),SIGTERM);
			}		
		}
				
		/*CLOSING DESCRIPTORS ON PARENT*/
		if (o == 0)
		{
			close(filedesc2[1]);
		}
		else if (o == nums_cmnd - 1)
		{
			if (nums_cmnd % 2 != 0)
			{					
				close(filedesc[0]);
			}
			else
			{					
				close(filedesc2[0]);
			}
		}
		else
		{
			if (o % 2 != 0)
			{					
				close(filedesc2[0]);
				close(filedesc[1]);
			}
			else
			{
				close(filedesc[0]);
				close(filedesc2[1]);
			}
		}
				
		waitpid(pid,NULL,0);
				
		o++;	
	}
}
