#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


void * threadSum(void* arg)
{
    int* nums = (int *) arg;
    int sum = (nums[0]) + (nums[1]);
    int * sumPtr = malloc(sizeof(int));
    *sumPtr = sum;
    return sumPtr;
}

void * threadDiff(void* arg)
{
    int* nums = (int *) arg;
    int diff = (nums[0]) - (nums[1]);
    int * diffPtr = malloc(sizeof(int));
    *diffPtr = diff;
    return diffPtr;
}

void * threadProd(void* arg)
{
    int* nums = (int *) arg;
    int prod = (nums[0]) * (nums[1]);
    int * prodPtr = malloc(sizeof(int));
    *prodPtr = prod;
    return prodPtr;
}

void * threadDiv(void* arg)
{
    int* nums = (int *) arg;
    int ratio = (nums[0]) / (nums[1]);
    int * ratioPtr = malloc(sizeof(int));
    *ratioPtr = ratio;
    return ratioPtr;
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

    void * sum;
    void * diff;
    void * prod;
    void * ratio;

    pthread_join(tids[0],&sum);
    pthread_join(tids[1],&diff);
    pthread_join(tids[2],&prod);
    pthread_join(tids[3],&ratio);

    printf("Sum: %d\n",*(int*)sum);
    printf("Difference: %d\n",*(int*)diff);
    printf("Product: %d\n",*(int*)prod);
    printf("Ratio: %d\n",*(int*)ratio);

    free(sum);
    free(diff);
    free(prod);
    free(ratio);

    pthread_exit(0);
}