#include <pthread.h>
#include <semaphore.h>

#define MAX_NUM_PHONE_CALLS 10000

pthread_mutex_t phoneCallsNum = PTHREAD_MUTEX_INITIALIZER;
sem_t thereIsACallToMake;
long int numPhoneCalls = 0;

void *caller(void *arg)
{
    while (1)
    {
        sem_wait(&thereIsACallToMake);
    }
}

void *receiver(void *arg)
{
    
    pthread_mutex_lock(&phoneCallsNum);
    while (numPhoneCalls < MAX_NUM_PHONE_CALLS)
    {
        pthread_mutex_unlock(&phoneCallsNum);
        int phoneNumber = receiveCall();
        pthread_mutex_lock(&phoneCallsNum);
        numPhoneCalls++;
        pthread_mutex_unlock(&phoneCallsNum);
        if (numPhoneCalls % 1000 == 0)
        {
            sem_post(&thereIsACallToMake);
        }
        pthread_mutex_lock(&phoneCallsNum);
    }
}

int main(void)
{
    sem_init(&thereIsACallToMake,0,0);
    pthread_t callerTid;
    pthread_t receiverTid[10];
    int args[10];
    pthread_create(&callerTid,NULL,caller,NULL);
    for (int i = 0; i < 10; i++)
    {
        args[i] = i + 1;
        pthread_create(&receiverTid[i],NULL,receiver,&args[i]);
    }
    sem_destroy(&thereIsACallToMake);
    return 0;
}