#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

struct nums
{
    int num1;
    int num2;
};

void * threadSum(void* arg)
{
    struct nums strnum = *(struct nums *)arg;
    printf("Sum: %d\n",strnum.num1 + strnum.num2);
    return NULL;
}

void * threadDiff(void* arg)
{
    struct nums strnum = *(struct nums *)arg;
    printf("Difference: %d\n",strnum.num1 - strnum.num2);
    return NULL;
}

void * threadProd(void* arg)
{
    struct nums strnum = *(struct nums *)arg;
    printf("Product: %d\n",strnum.num1 * strnum.num2);
    return NULL;
}

void * threadDiv(void* arg)
{
    struct nums strnum = *(struct nums *)arg;
    printf("Ratio: %d\n",strnum.num1 / strnum.num2);
    return NULL;
}

int main()
{
    printf("Type two numbers: \n");
    int num1,num2;
    scanf("%d %d",&num1,&num2);
    struct nums args;
    args.num1 = num1;
    args.num2 = num2;

    pthread_t tids[4];
    pthread_create(&tids[0],NULL,threadSum,&args);
    pthread_create(&tids[1],NULL,threadDiff,&args);
    pthread_create(&tids[2],NULL,threadProd,&args);
    pthread_create(&tids[3],NULL,threadDiv,&args);

    pthread_exit(0);
}