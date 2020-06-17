#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

sem_t a,b,c;

void *thread1(void *arg)
{
    arg=arg;

    /*
    sem_post(&a);
    sem_wait(&b);
    sem_wait(&c);
    sem_post(&b);
    sem_post(&c);
    */
    sem_post(&a);
    sem_wait(&c);
    sem_post(&a);
    sem_wait(&c);
    

    printf("Hi from thread 1\n");
    return NULL;
}

void *thread2(void *arg)
{
    arg=arg;
    /*
    sem_post(&b);
    sem_wait(&a);
    sem_wait(&c);
    sem_post(&a);
    sem_post(&c);
*/
    sem_post(&b);
    sem_wait(&a);
    sem_post(&b);
    sem_wait(&a);

    printf("Hi from thread 2\n");
    return NULL;
}

void *thread3(void *arg)
{
    arg=arg;
    /*
    sem_post(&c);
    sem_wait(&a);
    sem_wait(&b);
    sem_post(&b);
    sem_post(&a);
*/
    sem_post(&c);
    sem_wait(&b);
    sem_post(&c);
    sem_wait(&b);
    printf("Hi from thread 3\n");
    return NULL;    
}


int main(void)
{
    sem_init(&a,0,0);
    sem_init(&b,0,0);
    sem_init(&c,0,0);

    pthread_t tid1,tid2,tid3;
    pthread_create(&tid1,NULL,thread1,NULL);
    pthread_create(&tid2,NULL,thread2,NULL);
    pthread_create(&tid3,NULL,thread3,NULL);

    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_join(tid3,NULL);
    


    return 0;
}