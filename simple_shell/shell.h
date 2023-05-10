#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <termios.h>

#define LIM 256
#define LINEMAX 1024

#define TRUE 1
#define FALSE !TRUE

/*Shell pid, pgid, terminal modes*/
static pid_t __attribute__ ((unused)) PID_SH;
static pid_t __attribute__ ((unused)) PGID_SH;
static int __attribute__ ((unused)) INTERACTIVE_SH;
static struct termios __attribute__ ((unused)) MOD_SH;
static char* __attribute__ ((unused)) current_dir;
extern char** __attribute__ ((unused)) environ;
struct sigaction act_child;
struct sigaction act_int;
int no_prompt;
pid_t pid;

/*signal handlers*/
void _child_handler();
void _int_handler();

int chgDir(char * args[]);
int commands(char *args[]);
void prog_launch(char **args, int bckgrnd);
void files(char *args[], char *inputFile, char *outputFile, int opt);
void initalize();
void shellPrompt();
int chgDir(char* args[]);
int man_env(char * args[], int option);
void pipe_handler(char *args[]);

#endif /*SHEL_H*/
