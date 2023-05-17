#include "shell.h"

/**
* main - function method of our shell
* Return: alwayz zero
*/

int main() {
    char command[100];

    while (1) {
        printf("user$ ");
        fgets(command, sizeof(command), stdin);

        /*Check for the exit command*/
        if (strcmp(command, "exit\n") == 0) {
            exit(0);
        }

        /*Execute the command*/
        system(command);
    }

    return 0;
}
