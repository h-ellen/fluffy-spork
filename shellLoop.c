#include "shel.h"

/**
* main - function method of our shell
* Return: alwayz zero
*/
int main(int argc, char *argv[], char ** envp)
{
	char line[LINEMAX];
	char *tokens[LIM];
	int tokenNum;

	no_reprint_prmpt = 0;
	/*to prevent the printing of the shell after certain methods*/
	/*we initialize pid to an pid that is not possible*/
  pid = -10;
	
	/*We call the method of initialization*/
	init();
    
    /*We set our extern char** environ to the environment, so that*/
    /*we can treat it later in other methods*/
	environ = envp;
	
	/*We set shell=<pathname>/simple-c-shell as an environment variable for*/
	/*the child*/
	setenv("shell",getcwd(currentDirectory, 1024),1);
  
	while(TRUE)
	{
		/*We print the shell prompt if necessary*/
		if (no_reprint_prmpt == 0) shellPrompt();
		no_reprint_prmpt = 0;
		
		/*We empty the line buffer*/
		memset ( line, '\0', LINEMAX );

		/*We wait for user input*/
		fgets(line, LINEMAX, stdin);
	
		/*If nothing is written, the loop is executed again*/
		if((tokens[0] = strtok(line," \n\t")) == NULL) continue;
		
		/*We read all the tokens of the input and pass it to our*/
		/*commandHandler as the argument*/
		tokenNum = 1;
		while((tokens[tokenNum] = strtok(NULL, " \n\t")) != NULL) tokenNum++;
		
		commandHandler(tokens);
		
	}          

	exit(0);
}
