#include "shell.h"

/**
* main - function method of our shell
* Return: alwayz zero
*/
int main(int argc, char ** envp)
{
	char line[LINEMAX];
	char *tokens[LIM];
	int tokenNum;

	no_prompt = 0;
  pid = -10;
	
	initalize();

	environ = envp;

	setenv("shell",getcwd(current_dir, 1024),1);

	while(TRUE)
	{
		/*We print the shell prompt if necessary*/
		if (no_prompt == 0) shellPrompt();
		no_prompt = 0;
		
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
		
		commands(tokens);
		
	}          

	exit(0);
}
