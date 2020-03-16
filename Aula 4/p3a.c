#include <stdio.h> 
#include <signal.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <string.h>

int v = 0;
int increment = 1;

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
        write(STDERR_FILENO,"Couldn't install handler for SIGUSR1.\n",strlen("Couldn't install handler for SIGUSR1.\n"));
        exit(1);
    }

    if (sigaction(SIGUSR2,&action,NULL) < 0)
    {
        write(STDERR_FILENO,"Couldn't install handler for SIGUSR2.\n",strlen("Couldn't install handler for SIGUSR2.\n"));
        exit(2);
    }

    while (1)
    {
        printf("%d\n",v);
        v += increment;
        sleep(1);
    }
    return 0;
}