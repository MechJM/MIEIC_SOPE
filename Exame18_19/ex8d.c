#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>

#define NB 10
#define F 5
#define NOT_PSHARED 0

int food_bits = 0;
int finish = 0;

sem_t full,empty;
pthread_mutex_t foodMut = PTHREAD_MUTEX_INITIALIZER;

void *bird(void *arg)
{
    while (finish == 0)
    {
        get_food();
        sem_wait(&empty);
        pthread_mutex_lock(&foodMut);
        food_bits = F;
        pthread_mutex_unlock(&foodMut);
        sem_post(&full);
    }
    return NULL;
}

void *baby(void *arg)
{
    int id = *(int *)arg;
    int n_bits = 0;
    
    while (finish == 0)
    {
        sem_wait(&full);
        pthread_mutex_lock(&foodMut);
        food_bits--;
        if (food_bits == 0)
        {
            sem_post(&empty);
            fprintf(stderr,"I am baby %d, I have already eaten %d bits of food and I am still hungry!",id , n_bits);
        }
        pthread_mutex_unlock(&foodMut);
        n_bits++;
    }
    int *resPtr = malloc(sizeof(int));
    *resPtr = n_bits;

    return resPtr;
}

int main(void)
{
    pthread_t tid_bird, tid_baby[NB];

    int ids[NB];

    sem_init(&full,NOT_PSHARED,0);
    sem_init(&empty,NOT_PSHARED,1);

    pthread_create(&tid_bird,NULL,bird,NULL);
    for (int i = 0; i < NB; i++)
    {
        ids[i] = i;
        pthread_create(&tid_baby[i],NULL,baby,&ids[i]);
    }

    pthread_join(tid_bird,NULL);
    for (int i = 0; i < NB; i++)
    {
        void *res;
        pthread_join(tid_baby[i],&res);
        int total_bits = *(int *)res;
        fprintf(stdout,"Baby number %d has eaten %d bits of food",i, total_bits);
    }

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&foodMut);
    return 0;
}