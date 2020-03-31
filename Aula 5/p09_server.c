#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/wait.h>

int main(void)
{
    if (mkfifo("/tmp/fifo.s",0600) < 0) 
    {
        fprintf(stderr,"Couldn't create FIFO.\n");
        exit(1);
    }

    char arguments[200],program_name[50];

    pid_t clientPid;

    while(1)
    {
        FILE* fifoServerPtr = fopen("/tmp/fifo.s","r");
        fscanf(fifoServerPtr,"%d %s",clientPid,arguments);
        fclose(fifoServerPtr);

        sscanf(arguments,"%s",program_name);

        pid_t pid = fork();
        if (pid == 0)
        {
            execvp(program_name,arguments);
            exit(1);
        }
        else if (pid > 0)
        {
            int status;
            waitpid(pid,&status,WNOHANG);
        }
        else fprintf(stderr,"Couldn't create child process.\n");
    }

    return 0;
}