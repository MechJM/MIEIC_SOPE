#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define STDERR 2
#define NUMITER 10000

int charNum = 50000;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

void * thrfunc(void * arg)
{
    int counter = 0;
    
    
    while(charNum > 0)
    {   
        pthread_mutex_lock(&mut);
        if (charNum <= 0) break;
        write(STDERR,(char *) arg,1);
        counter++;
        charNum--;
        pthread_mutex_unlock(&mut);
    }
    
    int* counterPtr = malloc(sizeof(int));
    
    *counterPtr = counter;

    return counterPtr;
}

int main()
{
    pthread_t ta,tb;
    void * ta_result;
    void * tb_result;
    int total;

    pthread_create(&ta, NULL, thrfunc, "1");
    pthread_create(&tb, NULL, thrfunc, "2");

    pthread_join(ta, &ta_result);
    printf("\nThread A: %d\n",*(int *)ta_result);
    pthread_join(tb, &tb_result);
    printf("Thread B: %d\n",*(int *)tb_result);
    total = *(int*) (ta_result) + *(int*) (tb_result);
    free(ta_result);
    free(tb_result);

    printf("Total: %d\n",total);

    return 0;
}