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

int main()
{
    time_t rawtime; // takes current time
    time(&rawtime);
    struct tm *timeinfo = localtime(&rawtime);
    int pid = getpid();
    int ppid = getppid();
    char file[50];
    read(3, file, 50);
    char *fileName = strtok(file, "\n");

    if (access(fileName, 0) == 0)
    { // if file is already exist
        FILE *input = fopen(fileName, "a");
        fprintf(input, "system time: %s", asctime(timeinfo));
        fprintf(input, "pid: %d", pid);
        fprintf(input, "ppid: %d", ppid);
        fclose(input);
    }
    else
    {
        FILE *input = fopen(fileName, "w");
        fprintf(input, "system time: %s", asctime(timeinfo));
        fprintf(input, "pid: %d", pid);
        fprintf(input, "ppid: %d", ppid);
        fclose(input);
    }
}