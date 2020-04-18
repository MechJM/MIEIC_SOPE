#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define STDERR 2
#define NUMITER 10000
#define STR_LEN 50

void * thrfunc(void * arg)
{
    int i;

    fprintf(stderr,"Starting thread %d\n",*(int *) arg);
    char str_arg[STR_LEN] = "";
    sprintf(str_arg,"%d",*(int*)arg);
    for (i=1; i <= NUMITER; i++) write(STDERR,str_arg,1);
    return NULL;
}

int main()
{
    pthread_t ta,tb;

    int num = 1;

    pthread_create(&ta, NULL, thrfunc, &num);
    num++;
    pthread_create(&tb, NULL, thrfunc, &num);

    pthread_join(ta, NULL);
    pthread_join(tb, NULL);

    return 0;
}