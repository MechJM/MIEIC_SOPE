#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <wait.h>
#include <stdlib.h>

int childEnded;

void sigalrm_handler(int signo)
{
    childEnded = 0;
}

void sigchld_handler(int signo)
{
    childEnded = 1;
}

int main(int argc,char* argv[])
{
    pid_t pid;
    int limit = atoi(argv[1]);

    struct sigaction action;
    action.sa_handler = sigalrm_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    if (sigaction(SIGALRM,&action,NULL) < 0)
    {
        fprintf(stderr,"Couldn't install handler for SIGALRM.\n");
        exit(1);
    }

    struct sigaction action2;
    action2.sa_handler = sigchld_handler;
    sigemptyset(&action2.sa_mask);
    action2.sa_flags = 0;

    if (sigaction(SIGCHLD,&action2,NULL) < 0)
    {
        fprintf(stderr,"Couldn't install handler for SIGCHLD.\n");
        exit(2);
    }

    pid = fork();
    if (pid == 0)
    {
        execv(argv[2],&argv[2]);
    }
    else
    {
        alarm(limit);
        sigset_t sigset;
        sigfillset(&sigset);
        sigdelset(&sigset,SIGALRM);
        sigdelset(&sigset,SIGCHLD);
        sigsuspend(&sigset);
        if (!childEnded)
        {
            kill(pid,SIGKILL);
            printf("The program was forced to terminate.\n");
        } 
        else printf("The program ended normally.\n");
    }

    exit(0);
}