#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>

#define STR_LEN 50

struct nums
{
    int num1;
    int num2;
};

void * threadSum(void* arg)
{
    struct nums strnum = *(struct nums *)arg;
    int sum = strnum.num1 + strnum.num2;
    int * sumPtr = malloc(sizeof(int));
    *sumPtr = sum;
    return sumPtr;
}

void * threadDiff(void* arg)
{
    struct nums strnum = *(struct nums *)arg;
    int diff = strnum.num1 - strnum.num2;
    int * diffPtr = malloc(sizeof(int));
    *diffPtr = diff;
    return diffPtr;
}

void * threadProd(void* arg)
{
    struct nums strnum = *(struct nums *)arg;
    int prod = strnum.num1 * strnum.num2;
    int * prodPtr = malloc(sizeof(int));
    *prodPtr = prod;
    return prodPtr;
}

void * threadDiv(void* arg)
{
    struct nums strnum = *(struct nums *)arg;
    float ratio;
    if (strnum.num2 == 0) ratio = -1;
    else ratio = (float) strnum.num1 / strnum.num2;
    float * ratioPtr = malloc(sizeof(float));
    *ratioPtr = ratio;
    return ratioPtr;
}

int main()
{
    if (mkfifo("/tmp/fifo_req",0600) < 0) fprintf(stderr,"Couldn't create request FIFO.\n");

    int num1,num2;
    do
    {
        FILE* reqPtr = fopen("/tmp/fifo_req","r");
        char ansName[STR_LEN] = "";

        fscanf(reqPtr,"%d %d %s",&num1,&num2,ansName);
        fclose(reqPtr);

        struct nums args;
        args.num1 = num1;
        args.num2 = num2;

        pthread_t tids[4];
        pthread_create(&tids[0],NULL,threadSum,&args);
        pthread_create(&tids[1],NULL,threadDiff,&args);
        pthread_create(&tids[2],NULL,threadProd,&args);
        pthread_create(&tids[3],NULL,threadDiv,&args);

        void * sum;
        void * diff;
        void * prod;
        void * div;

        pthread_join(tids[0],&sum);
        pthread_join(tids[1],&diff);
        pthread_join(tids[2],&prod);
        pthread_join(tids[3],&div);

        FILE* ansPtr = fopen(ansName,"w");
        fprintf(ansPtr,"%d %d %d %f",*(int*)sum,*(int*)diff,*(int*)prod,*(float*)div);
        fclose(ansPtr);

    } while (num1 != 0 || num2 != 0);

    unlink("/tmp/fifo_req");
        
    return 0;
}