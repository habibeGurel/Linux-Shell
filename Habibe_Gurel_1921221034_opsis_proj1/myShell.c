#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int fd[2]; // pipe

void lsFunc()
{
    int pid = fork();
    if (pid < 0)
    { // if there is not any child
        printf("\nfailed forking");
    }
    else if (pid == 0)
    { // if there is a child
        int e = execvp("/bin/ls", NULL);
        perror("");
    }
    else
    { // main program
        wait(&pid);
    }
}
int isInt(char s[])
{ // This method checks if the input is a number
    int i = 0;
    while (s[i] != '\0')
    {
        if (isdigit(s[i]) == 0)
            return 0;
        i++;
    }
    return 1;
}
void execxFunc(char *file)
{
    int e = 0;
    int pid = fork();
    if (pid < 0)
    {
        printf("\nfailed forking");
    }
    else if (pid == 0)
    {
        write(fd[1], file, strlen(file)); // writes number, writef -f and file name to pipe
        e = execv("execx", NULL);         // calling the execx program
        perror("");
        close(fd[1]);
        
    }
}

void writeFunc(char *file)
{
    int e = 0;
    int pid = fork();
    if (pid < 0)
    {
       printf("\nfailed forking");
    }
    else if (pid == 0)
    {
         write(fd[1], file, strlen(file)); // writes the file name to pipe
        e = execv("writef", NULL);        // calling the writef program
        perror("");
        close(fd[1]);
    }
    else
    {
        wait(&e);
    }
}

void bashFunc()
{
    int pid = fork();
    if (pid < 0)
    {
        printf("\nfailed forking");
    }
    else if (pid == 0)
    {
        int e = execvp("bash", NULL); // calling the bash program
        perror("");
    }
    else
    {
        wait(&pid);
    }
}

int main()
{
    if (pipe(fd) < 0)
    {
        perror("");
        exit(1);
    }
    char command[100];
    int commandSize = 1;
    while (1)
    {

        printf("myshell>>");
        fgets(command, 100, stdin); // reading the input command
        for (int i = 0; i < 100; i++)
        {
            if (command[i] == ' ') // space control
            {
                commandSize++;
            }
        }
        char *token = strtok(command, " "); // asigns the command according to the space to the token
        char *commandArr[commandSize];      // create a command array
        int i = 0;
        while (token != NULL)
        {
            commandArr[i++] = token;   // assigns the tokens to the command array
            token = strtok(NULL, " "); // asigns the command according to the space to the token
        }
        if (strcmp(command, "bash\n") == 0)
        { // bash control
            bashFunc();
        }
        else if (strcmp(command, "ls\n") == 0)
        { // ls control
            lsFunc();
        }
        else if (strcmp(command, "exit\n") == 0)
        { // exit control
            exit(0);
        }
        else if (strcmp(command, "clear\n") == 0)
        { // clear control
            system("clear");
        }
        else if (strcmp(commandArr[0], "cat") == 0 && commandSize > 1)
        { // cat control
            for (int i = 0; i < commandSize; i++)
            {
                if (i == 0)
                {
                    printf("%s:", commandArr[i]);
                }
                else
                {
                    printf(" %s", commandArr[i]);
                }
            }
        }
        else if (strcmp(commandArr[0], "writef") == 0 && strcmp(commandArr[1], "-f") == 0 && commandSize == 3)
        { // writef -f fileName  (3 inputs)
            char fileName[50];
            strcpy(fileName, commandArr[2]); // copying commandArr[2] which is file name to fileName array
            writeFunc(fileName);             // calling writeFunc function with file name parameter
        }
        else if (strcmp(commandArr[0], "execx") == 0 && strcmp(commandArr[1], "-t") == 0 && isInt(commandArr[2]) && strcmp(commandArr[3], "writef") == 0 && strcmp(commandArr[4], "-f") == 0 && commandSize == 6)
        { // writef -f fileName  (3 inputs)
            // asigningn the command which is after the "execx -t"
            char fileName[50];
            strcpy(fileName, commandArr[2]);
            for (int i = 3; i <= 5; i++)
            {
                strcat(fileName, " ");
                strcat(fileName, commandArr[i]);
            }
            execxFunc(fileName); // calling the execxFunc function
        }
        else
        {
            printf("code error\n");
        }
        commandSize = 1;
    }
    return 0;
}