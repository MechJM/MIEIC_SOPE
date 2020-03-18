#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int flag = 0,alarmCounter = 0;

void sigalrmHandler(int signo)
{
    flag = 1;
}

int main(int argc,char* argv[])
{
    struct sigaction action;
    action.sa_handler = sigalrmHandler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    if (sigaction(SIGALRM,&action,NULL) < 0)
    {
        fprintf(stderr,"Couldn't install handler for SIGALRM.\n");
        exit(1);
    }

    alarm(5);

    while(alarmCounter < 6)
    {
        if (flag)
        {
            flag = 0;
            alarmCounter++;
            printf("%s",argv[1]);
            printf("\n");
            alarm(5);
        }
    }
    exit(0);
}