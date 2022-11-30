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

int fd[2];//pipe

int isNum(char s[])
{// This method checks if the input is a number
    for (int i = 0; s[i]!= '\0'; i++)
    {
        if (isdigit(s[i]) == 0)
              return 0;
    }
    return 1;
}
void ls()
{
    int pid = fork();
    if (pid == 0)
    {// if there is a child
        int e = execvp("/bin/ls", NULL);
        perror("");
    }
    else if (pid < 0)
    {// if there is not any child
        printf("\nfailed forking");
    }
    else
    {// main program
        wait(&pid);
    }
}

void myWrite(char *file){
    int e = 0;
    int pid = fork();
    if (pid == 0)
    {
        write(fd[1], file, strlen(file));// writes the file name to pipe
        e = execv("writef", NULL);// calling the writef program
        perror("");
        close(fd[1]);
    }else if (pid < 0)
    {
        printf("\nfailed forking");
    }
    else
    {
        wait(&e);
    }
}
void myExecx(char *file){
    int e = 0;
    int pid = fork();
    if (pid == 0)
    {
        write(fd[1], file, strlen(file));// writes number, writef -f and file name to pipe
        e = execv("execx", NULL);// calling the execx program
        perror("");
        close(fd[1]);
    }else if (pid < 0)
    {
        printf("\nfailed forking");
    }

}
void bash()
{
    int pid = fork();
    if (pid == 0)
    {
        int e = execvp("bash", NULL);// calling the bash program
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

int main()
{
    if(pipe(fd) < 0){
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
        char *token = strtok(command, " ");// asigns the command according to the space to the token 
        char *commandArr[commandSize];// create a command array 
        int i = 0;
        while (token != NULL)
        { 
            commandArr[i++] = token;// assigns the tokens to the command array
            token = strtok(NULL, " ");// asigns the command according to the space to the token 
        }
        if(strcmp(command, "bash\n") == 0){// bash control
            bash();
        }else if(strcmp(command, "clear\n") == 0){// clear control
            system("clear");
        }else if(strcmp(command, "exit\n") == 0){// exit control
            exit(0);
        }else if(strcmp(command, "ls\n") == 0){// ls control
            ls();
        }else if(strcmp(commandArr[0], "cat") == 0 && commandSize>1){// cat control
            for (int i = 0; i < commandSize; i++)
            {
                if(i==0){
                    printf("%s:",commandArr[i]);
                }else{
                    printf(" %s",commandArr[i]);
                }
            }
            
        }else if(strcmp(commandArr[0], "writef") == 0 && strcmp(commandArr[1], "-f") == 0 && commandSize == 3){//writef -f fileName  (3 inputs)
            char fileName[50];
            strcpy(fileName,commandArr[2]);// copying commandArr[2] which is file name to fileName array
            myWrite(fileName);// calling myWrite function with file name parameter
        }else if(strcmp(commandArr[0], "execx") == 0 && strcmp(commandArr[1], "-t") == 0 && isNum(commandArr[2])
        && strcmp(commandArr[3], "writef") == 0 && strcmp(commandArr[4], "-f") == 0 && commandSize == 6){//writef -f fileName  (3 inputs)
            // asigningn the command which is after the "execx -t" 
            char fileName[50];
            strcpy(fileName,commandArr[2]);
            for (int i = 3; i <= 5; i++)
            {
                strcat(fileName," ");
                strcat(fileName,commandArr[i]);
            }
            myExecx(fileName);// calling the myExecx function
        }else{
            printf("hatali kod\n");
        }
        commandSize = 1;
    }
    return 0;
}