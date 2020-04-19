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
    int ratio = strnum.num1 / strnum.num2;
    int * ratioPtr = malloc(sizeof(int));
    *ratioPtr = ratio;
    return ratioPtr;
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