#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <signal.h>

int flag = 0;

void sigalrm_handler(int signo)
{
    flag = 1;
}

int main(void)
{
    alarm(30);

    struct sigaction action;
    action.sa_handler = sigalrm_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    sigaction(SIGALRM,&action,NULL);

    int message_counter = 0;

    char last_message[100] = "";

    do
    {
        char message[100];

        FILE* fifoPtr = fopen("/tmp/fifo_chg","r");
        fscanf(fifoPtr,"%s",message);
        fclose(fifoPtr);

        if (strcmp(message,last_message) != 0)
        {
            printf("CHEGOU %s\n",message);
            message_counter++;
            strcpy(last_message,message);
        } 
    }
    while (!flag);

    printf("Mensagens impressas: %d\n",message_counter);

    return 0;
}