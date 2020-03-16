#include <stdio.h> 
#include <signal.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <string.h>
#include <sys/types.h>
#include <time.h>

int v = 0;
int increment = 1;
int printCounter = 0;

void sigusr_handler(int signo)
{
    if (signo == SIGUSR1) increment = 1;
    else if (signo == SIGUSR2) increment = -1;
    else write(STDERR_FILENO,"This handler shouldn't have been called.\n",strlen("This handler shouldn't have been called.\n"));
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
        while (1)
        {   
            int timeToSleep = 1;
            printf("%d\n",v);
            printCounter++;
            if (printCounter == 50) exit(0);
            v += increment;
            timeToSleep = sleep(timeToSleep);
        }
    }
    else
    {
        srand(time(NULL));
        while (1)
        {
            int randNum = rand() % 2 + 1;
            if (randNum == 1) kill(pid,SIGUSR1);
            else if (randNum == 2) kill(pid,SIGUSR2);
            else write(STDERR_FILENO,"rand() didn't work properly.\n",29);
            if (printCounter == 50) exit(0);
        }
    }
}