#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


void * threadSum(void* arg)
{
    int * nums = (int *) arg;
    printf("Sum: %d\n",(nums[0]) + (nums[1]));
    return NULL;
}

void * threadDiff(void* arg)
{
    int * nums = (int *) arg;
    printf("Difference: %d\n",(nums[0]) - (nums[1]));
    return NULL;
}

void * threadProd(void* arg)
{
    int * nums = (int *) arg;
    printf("Product: %d\n",(nums[0]) * (nums[1]));
    return NULL;
}

void * threadDiv(void* arg)
{
    int * nums = (int *) arg;
    printf("Ratio: %d\n",(nums[0]) / (nums[1]));
    return NULL;
}

int main()
{
    printf("Type two numbers: \n");
    int num1,num2;
    scanf("%d %d",&num1,&num2);
    int args[2];
    args[0] = num1;
    args[1] = num2;

    pthread_t tids[4];
    pthread_create(&tids[0],NULL,threadSum,&args);
    pthread_create(&tids[1],NULL,threadDiff,&args);
    pthread_create(&tids[2],NULL,threadProd,&args);
    pthread_create(&tids[3],NULL,threadDiv,&args);

    pthread_exit(0);
}