#include "shell.h"

/**
 * initalize - function used to initialize our shell.
 * Return: Always zero
 */

void initalize()
{
	PID_SH = getpid();
	INTERACTIVE_SH = isatty(STDIN_FILENO);
		if (INTERACTIVE_SH)
		{
			while (tcgetpgrp(STDIN_FILENO) != (PGID_SH = getpgrp()))
					kill(PID_SH, SIGTTIN);

			act_child.sa_handler = _child_handler;
			act_int.sa_handler = _int_handler;

			sigaction(SIGCHLD, &act_child, 0);
			sigaction(SIGINT, &act_int, 0);
	
			setpgid(PID_SH, PID_SH);

			PGID_SH = getpgrp();
			if (PID_SH != PGID_SH)
			{
					printf("Error, the shell is not process group leader");
					exit(EXIT_FAILURE);
			}
			/*Grab control of the terminal*/
			tcsetpgrp(STDIN_FILENO, PGID_SH);

			tcgetattr(STDIN_FILENO, &MOD_SH);

			current_dir = (char*) calloc(1024, sizeof(char));
        }
	else
	{
         not_interactive();
        }
}

/**
 * _child_handler - signal handler for SIGCHLD
 * Return: always zero
 */
void _child_handler()
{
	while (waitpid(-1, NULL, WNOHANG) > 0)
	{
	}
	printf("\n");
}

/**
 * _int_handler - Signal handler for SIGINT
 * Return: always zero
 */
void _int_handler()
{
	/*We send a SIGTERM signal to the child process*/
	if (kill(pid,SIGTERM) == 0)
	{
		printf("\nProcess %d received a SIGINT signal\n",pid);
		no_prompt = 1;			
	}
	else
	{
		printf("\n");
	}
}

/**
 * new_process - create a new process
 * @args: array of strings that contains the command and its flags
 *
 * Return: 1 if success, 0 otherwise.
 */
int new_process(char **args)
{
 pid_t pid;
 int status;

 pid = fork();
 if (pid ==  0)
 {
  /* child process */
  if (execvp(args[0], args) == -1)
  {
   perror("error in new_process: child process");
  }
  exit(EXIT_FAILURE);
 }
 else if (pid < 0)
 {
  /* error forking */
  perror("error in new_process: forking");
 }
 else
 {
  /* parent process */
  do {
   waitpid(pid, &status, WUNTRACED);
  } while (!WIFEXITED(status) && !WIFSIGNALED(status));
 }
 return (-1);
}
