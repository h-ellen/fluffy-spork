#include "shell.h"

/**
 * not_interactive - unix command line interpreter
 *
 * Return: void
 */
void not_interactive(void)
{
 char *line;
 char **args;
 int status = -1;

 do {
  line = read_stream();
  args = split_line(line); /* tokenize line */
  status = commands(args);
  /* avoid memory leaks */
  free(line);
  free(args);
  /* exit with status */
  if (status >= 0)
  {
   exit(status);
  }
 } while (status == -1);
}

/**
 *read_stream - read a line from the stream
 *
 *Return: pointer to read string
 */
char *read_stream(void)
{
 int bufsize = 1024;
 int i = 0;
 char *line = malloc(sizeof(char) * bufsize);
 int character;

 if (line == NULL)
 {
  fprintf(stderr, "allocation error in read_stream");
  exit(EXIT_FAILURE);
 }
 while (1)
 {
  character = getchar(); /* read first char from stream */
  if (character == EOF)
  {
   free(line);
   exit(EXIT_SUCCESS);
  }
  else if (character == '\n')
  {
   line[i] = '\0';
   return (line);
  }
  else
  {
   line[i] = character;
  }
  i++;
  if (i >= bufsize)
  {
   bufsize += bufsize;
   line = realloc(line, bufsize);
   if (line == NULL)
   {
    fprintf(stderr, "reallocation error in read_stream");
    exit(EXIT_FAILURE);
   }
  }
 }
}

/**
 * split_line - split a string into multiple strings
 * @line: string to be splited
 *
 * Return: pointer that points to the new array
 */
char **split_line(char *line)
{
 int bufsize = 64;
 int i = 0;
 char **tokens = malloc(bufsize * sizeof(char *));
 char *token;

 if (!tokens)
 {
  fprintf(stderr, "allocation error in split_line: tokens\n");
  exit(EXIT_FAILURE);
 }
 token = strtok(line, TOK_DELIM);
 while (token != NULL)
 {
  /* handle comments */
  if (token[0] == '#')
  {
   break;
  }
  tokens[i] = token;
  i++;
  if (i >= bufsize)
  {
   bufsize += bufsize;
   tokens = realloc(tokens, bufsize * sizeof(char *));
   if (!tokens)
   {
    fprintf(stderr, "reallocation error in split_line: tokens");
    exit(EXIT_FAILURE);
   }
  }
  token = strtok(NULL, TOK_DELIM);
 }
 tokens[i] = NULL;
 return (tokens);
}
