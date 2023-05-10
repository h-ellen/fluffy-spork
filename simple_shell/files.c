#include "shell.h"

/**
* prog_launch - Method for launching a program. It can be run in the background
* or in the foreground
* Return: always zero
*/ 
void prog_launch(char **args, int bckgrnd)
{	 
	 int error = -1;
	 
	 if((pid=fork())==-1)
	 {
		 printf("Child process could not be created\n");
		 return;
	 }

	if(pid==0)
	{
		signal(SIGINT, SIG_IGN);
		setenv("parent",getcwd(current_dir, 1024),1);
		
		/*If we launch non-existing commands we end the process*/
		if (execvp(args[0],args)==error)
		{
			printf("Command not found");
			kill(getpid(),SIGTERM);
		}
	 }
	 if (bckgrnd == 0)
	 {
		 waitpid(pid,NULL,0);
	 }
	else
	{
		 printf("Process created with PID: %d\n",pid);
	 }	 
}
 
/**
* files - Method used to manage I/O redirection
* Retuen: always zero
*/ 
void files(char *args[], char *inputFile, char *outputFile, int opt)
{
	 
	int error = -1;
	
	int file_desc;
	
	if((pid=fork())==-1)
	{
		printf("Child process could not be created\n");
		return;
	}
	if(pid==0)
	{
		if (opt == 0)
		{
			file_desc = open(outputFile, O_CREAT | O_TRUNC | O_WRONLY, 0600);
			dup2(file_desc, STDOUT_FILENO);
			close(file_desc);
		}
		else if (opt == 1)
		{
			file_desc = open(inputFile, O_RDONLY, 0600);
			dup2(file_desc, STDIN_FILENO);
			close(file_desc);
			file_desc = open(outputFile, O_CREAT | O_TRUNC | O_WRONLY, 0600);
			dup2(file_desc, STDOUT_FILENO);
			close(file_desc);
		}
		setenv("parent",getcwd(current_dir, 1024),1);
		
		if (execvp(args[0],args)==error)
		{
			printf("error");
			kill(getpid(),SIGTERM);
		}		 
	}
	waitpid(pid,NULL,0);
}
