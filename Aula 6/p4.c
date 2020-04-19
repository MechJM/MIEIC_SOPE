#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define N 100
/*
void sigalrm_handler(int signo)
{
    if (signo != SIGALRM) fprintf(stderr,"This handler shouldn't have been called.\n");

}
*/
void * threadFunc(void * arg)
{
    /*
    struct sigaction action;
    sigemptyset(&action.sa_mask);
    action.sa_flags=0;
    action.sa_handler = sigalrm_handler;
    sigaction(SIGALRM,&action,NULL);
    sigset_t mask;
    sigfillset(&mask);
    sigdelset(&mask,SIGALRM);
    alarm(1);
    sigsuspend(&mask);
    */

    sleep(1);
    fprintf(stderr,"TID: %ld\n",pthread_self());
    int * orderPtr = malloc(sizeof(int));
    *orderPtr = *(int*)arg;
    return orderPtr;
}

int main(void)
{
    int order[N];
    pthread_t tid[N];
    for (int i=0; i<N; i++)
    {
        order[i] = i+1;
        pthread_create(&tid[i],NULL,threadFunc,&order[i]);
    }
    pthread_exit(0);
}