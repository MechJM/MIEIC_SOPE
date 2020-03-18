#include <stdio.h> 
#include <signal.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <wait.h>

int v = 0;
int increment = 1;
int printCounter = 0;
int flag = 0,flag2 = 1;

void sigusr_handler(int signo)
{
    if (signo == SIGUSR1) increment = 1;
    else if (signo == SIGUSR2) increment = -1;
    else write(STDERR_FILENO,"This handler shouldn't have been called.\n",strlen("This handler shouldn't have been called.\n"));
}

void sigalrm_handler(int signo)
{
    flag = 1;
}

void sigchld_handler(int signo)
{
    flag2 = 0;
}

int main(void)
{
    struct sigaction action;
    action.sa_handler = sigusr_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    if (sigaction(SIGUSR1,&action,NULL) < 0)
    {
        write(STDERR_FILENO,"Couldn't install handler for SIGUSR1.\n",38);
        exit(1);
    }

    if (sigaction(SIGUSR2,&action,NULL) < 0)
    {
        write(STDERR_FILENO,"Couldn't install handler for SIGUSR2.\n",38);
        exit(2);
    }

    pid_t pid = fork();
    if (pid < 0) write(STDERR_FILENO,"Couldn't create child process.\n",31);
    else if (pid == 0)
    {
        struct sigaction action2;
        action2.sa_handler = sigalrm_handler;
        sigemptyset(&action2.sa_mask);
        action2.sa_flags = 0;

        if (sigaction(SIGALRM,&action2,NULL) < 0)
        {
            write(STDERR_FILENO,"Couldn't install handler for SIGALRM.\n",38);
            exit(3);
        }

        alarm(1);

        while (1)
        {   
            if (flag)
            {   
                flag = 0;
                alarm(1);
                printf("%d\n",v);
                printCounter++;
                if (printCounter == 50) exit(0);
                v += increment;
            }
        }
    }
    else
    {
        struct sigaction action2;
        action2.sa_handler = sigchld_handler;
        sigemptyset(&action2.sa_mask);
        action2.sa_flags = 0;
        
        if (sigaction(SIGCHLD,&action2,NULL) < 0)
        {
            write(STDERR_FILENO,"Couldn't install handler for SIGCHLD.\n",38);
            exit(4);
        }

        int status;
    
        srand(time(NULL));
        while (flag2)
        {
            int randNum = rand() % 2 + 1;
            if (randNum == 1) kill(pid,SIGUSR1);
            else if (randNum == 2) kill(pid,SIGUSR2);
            else write(STDERR_FILENO,"rand() didn't work properly.\n",29);
        }
        exit(0);
    }
}