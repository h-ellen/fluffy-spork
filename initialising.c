#include "shel.h"
/**
 * initalize - function used to initialize our shell.
 * Return: Always zero
 */
void initalize()
{
	GBSH_PID = getpid();
	GBSH_IS_INTERACTIVE = isatty(STDIN_FILENO);
		if (GBSH_IS_INTERACTIVE)
		{
			while (tcgetpgrp(STDIN_FILENO) != (GBSH_PGID = getpgrp()))
					kill(GBSH_PID, SIGTTIN);

			act_child.sa_handler = signalHandler_child;
			act_int.sa_handler = signalHandler_int;

			sigaction(SIGCHLD, &act_child, 0);
			sigaction(SIGINT, &act_int, 0);
	
			setpgid(GBSH_PID, GBSH_PID);

			GBSH_PGID = getpgrp();
			if (GBSH_PID != GBSH_PGID)
			{
					printf("Error, the shell is not process group leader");
					exit(EXIT_FAILURE);
			}
			/*Grab control of the terminal*/
			tcsetpgrp(STDIN_FILENO, GBSH_PGID);

			tcgetattr(STDIN_FILENO, &GBSH_TMODES);

			currentDirectory = (char*) calloc(1024, sizeof(char));
        }
	else
	{
                printf("Could not make the shell interactive.\n");
                exit(EXIT_FAILURE);
        }
}

/**
 * SIGNAL HANDLERS
 */

/**
 * signalHandler_child - signal handler for SIGCHLD
 * Return: always zero
 */
void signalHandler_child(int p)
{
	/**
	 * Wait for all dead processes.
	 * We use a non-blocking call (WNOHANG) to be sure this signal handler will not
	 * block if a child was cleaned up in another part of the program.
	 */
	while (waitpid(-1, NULL, WNOHANG) > 0) {
	}
	printf("\n");
}

/**
 * signalHandler_int - Signal handler for SIGINT
 * Return: always zero
 */
void signalHandler_int(int p)
{
	/*We send a SIGTERM signal to the child process*/
	if (kill(pid,SIGTERM) == 0)
	{
		printf("\nProcess %d received a SIGINT signal\n",pid);
		no_reprint_prmpt = 1;			
	}
	else
	{
		printf("\n");
	}
}
