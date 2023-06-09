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
#include <termios.h>

#define LIM 256
#define LINEMAX 1024

#define TRUE 1
#define FALSE !TRUE

/*Shell pid, pgid, terminal modes*/
static pid_t PID_SH;
static pid_t PGID_SH;
static int INTERACTIVE_SH;
static struct termios MOD_SH;
static char* current_dir;
extern char** environ;
struct sigact t_child;
struct sigact t_int;
int no_prompt;
pid_t pid;

/*signal handlers*/
void _child_handler(int p);
void _int_handler(int p);

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
