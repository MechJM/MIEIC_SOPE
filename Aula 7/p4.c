#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>

#define MAXELEMS 10000000
#define MAXTHREADS 100
#define min(a,b) (a)<(b)?(a):(b)
#define SHM_SIZE 8

#define SHARED_BETWEEN_PROCESSES 1

char SEM_NAME[] = "/sem1";
char SHM_NAME[] = "/shm1";


int * npos;

sem_t sem;
int buf[MAXELEMS], pos=0, val=0;

void* fill(void* nr)
{
    while(1)
    {
        sem_wait(&sem);
        if (pos >= npos)
        {
            sem_post(&sem);
            return NULL;
        }
        buf[pos] = val;
        pos++; val++;
        sem_post(&sem);
        * (int*) nr += 1;
    }
}

void* verify(void* arg)
{
    arg = arg; //otherwise the compiler complains about an unused parameter
    int k;
    for (k=0; k < npos; k++)
    {
        if (buf[k] != k) printf("ERROR: buf[%d] = %d\n",k,buf[k]);
    }
    return NULL;
}

int main(int argc, char* argv[])
{
    int * shm;
    int shmfd = shm_open(SHM_NAME,O_CREAT|O_RDWR,0600);
    if (shmfd < 0)
    {
        fprintf(stderr,"Couldn't open shared memory location.\n");
        exit(1);
    }

    if (ftruncate(shmfd,SHM_SIZE) < 0)
    {
        fprintf(stderr,"Couldn't specify shared memory size.\n");
        exit(1);
    }

    shm = mmap(0,SHM_SIZE,PROT_READ|PROT_WRITE,MAP_SHARED,shmfd,0);
    if (shm == MAP_FAILED)
    {
        fprintf(stderr,"Couldn't map shared memory.\n");
        exit(1);
    }

    if (sem_init(&sem,SHARED_BETWEEN_PROCESSES,0) < 0)
    {
        fprintf(stderr,"Couldn't initialize semaphore.\n");
        exit(1);
    }




    int k, nthr, count[MAXTHREADS];
    pthread_t tidf[MAXTHREADS], tidv;
    int total;

    if (argc != 3)
    {
        printf("Usage: %s <nr_pos> <nr_thrs>\n",argv[0]);
        return 1;
    }

    npos = min(atoi(argv[1]), MAXELEMS);
    nthr = min(atoi(argv[2]), MAXTHREADS);

    for (k=0; k < nthr; k++)
    {
        count[k] = 0;
        pthread_create(&tidf[k], NULL, fill, &count[k]);
    }
    total = 0;
    for (k=0; k < nthr; k++)
    {
        pthread_join(tidf[k], NULL);
        printf("count[%d] = %d\n",k,count[k]);
        total += count[k];
    }
    printf("total count = %d\n",total);

    pthread_create(&tidv, NULL, verify, NULL);
    pthread_join(tidv, NULL);

    shm_unlink(SHM_NAME);
    return 0;
}