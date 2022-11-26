#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>

int main()
{
    char command[100];

    while (1)
    {
        printf("myshell>>");
        fgets(command, 100, stdin); // reads the input
        if (strcmp(command, "exit\n") == 0)
        { // compare
            exit(0);
        }
        else if (strcmp(command, "bash\n") == 0)
        {
            bash();
        }
        else if (strcmp(command, "ls\n") == 0)
        {
            ls();
        }
        else if (strcmp(command, "clear\n") == 0)
        {
            system("clear");
        }
        else if (strcmp(command, "cat\n") == 0)
        {
        }
    }
}

void bash()
{
    int pid = fork();
    if (pid == 0)
    {
        int e = execvp("bash", NULL);
        perror("");
    }
    else if (pid < 0)
    {
        printf("\nfailed forking");
    }
    else
    {
        wait(&pid);
    }
}

void ls()
{
    int pid = fork();
    if (pid == 0)
    {
        int e = execvp("/bin/ls", NULL);
        perror("");
    }
    else if (pid < 0)
    {
        printf("\nfailed forking");
    }
    else
    {
        wait(&pid);
    }
}
