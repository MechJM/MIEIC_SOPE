#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define N 100
void * threadFunc(void * arg)
{
    sleep(1);
    int * orderPtr = malloc(sizeof(int));
    *orderPtr = *(int*)arg;
    return orderPtr;
}

int main(void)
{
    int order[N];
    pthread_t tid[N];
    void * returnValue;
    for (int i=0; i<N; i++)
    {
        order[i] = i+1;
        pthread_create(&tid[i],NULL,threadFunc,&order[i]);
    }

    for (int i=0; i<N; i++)
    {
        pthread_join(tid[i],&returnValue);
        printf("Return value from thread %ld: %d\n",tid[i],*(int*)returnValue);
        free(returnValue);
    }


    pthread_exit(0);
}