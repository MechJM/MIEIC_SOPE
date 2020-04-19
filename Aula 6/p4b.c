#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define N 100
void * threadFunc(void * arg)
{
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
    //pthread_exit(0);
    return 0; //the threads never get a chance to run
}