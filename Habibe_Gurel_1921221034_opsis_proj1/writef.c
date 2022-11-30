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
#include <time.h>
//
int main()
{
    char input[50];
    read(3, input, 50);
    char *fileName = strtok(input, "\n");
    time_t rawtime; // takes current time
    time(&rawtime);
    struct tm *systime = localtime(&rawtime);//takes system time
    int pid = getpid();
    int ppid = getppid();

    if (access(fileName, 0) != 0)
    { // if file is not exist
        FILE *file = fopen(fileName, "w");// "w" is creates a new file and write on it
        fprintf(file, "system time: %s pid: %d ppid: %d\n",strtok(asctime(systime),"\n"),pid,ppid);// information is printed side by side
        fclose(file);
    }
    else
    {// if file is already exist
        FILE *file = fopen(fileName, "a");// "a" appends to existing file
        fprintf(file, "system time: %s pid: %d ppid: %d\n",strtok(asctime(systime),"\n"),pid,ppid);// information is printed side by side
        fclose(file);
    }
    return 0;
}