#ifndef _SHEL_H
#define _SHEL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <termios.>

#define LIMIT 256
#define MAXLINE 1024

#define TRUE 1
#define FALSE !TRUE

/*Shell pid, pgid, terminal modes*/
static pid_t GBSH_PID;
static pid_t GBSH_PGID;
static int GBSH_IS_INTERACTIVE;
static struct termios GBSH_TMODES;
static char* currentDirectory;
extern char** environ;
struct sigaction act_child;
struct sigaction act_int;
int no_reprint_prmpt;
pid_t pid;

/*signal handlers*/
void signalHandler_child(int p);
void signalHandler_int(int p);

int changeDirectory(char * args[]);
#endif /*SHELL_H*/
