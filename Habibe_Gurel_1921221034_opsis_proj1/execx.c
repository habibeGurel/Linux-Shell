#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main()
{
    int inputSize = 1;
    char input[100];
    read(3, input, 100);// reads the pipe and writes the value to input

    for (int k = 0; k < 100; k++)
    {
        if (input[k] == ' ')
        {
            inputSize++;
        }
    }
    int i = 0;
    char *token = strtok(input, " ");// splits the input according to the space
    char *inputArr[inputSize];// creates the input array that takes the inputs
    while (token != NULL)
    {
        inputArr[i++] = token;// we assigned the token to the input array
        token = strtok(NULL, " ");
    }

    int count = atoi(inputArr[0]);// casting string number to integer

    char file[50];
    strcpy(file, inputArr[3]);// copying the file name to the file array
    char *fileName = file;
    int pid;
    int e;
    for (int i = 0; i < count; i++)
    {
        e = 0;
        pid = fork();
        if (pid == 0)
        {
            write(4, fileName, strlen(fileName));// 4 is write command, we write file name to pipe
            e = execv("writef", NULL);// calling the writef program
            perror("");
        }
        else if (pid < 0)
        {
            printf("\nfailed forking");
        }
        else
        {
            wait(&e);
        }
    }
}