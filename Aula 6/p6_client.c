#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define STR_LEN 50

int main()
{
    char fifoName[STR_LEN] = "";
    sprintf(fifoName,"/tmp/fifo_ans_%d",getpid());
    if (mkfifo(fifoName,0600) < 0) fprintf(stderr,"Couldn't create answer FIFO.\n");

    int num1,num2,flag = 1;

    while(flag)
    {
        printf("Type 2 numbers: \n");
        scanf("%d %d",&num1,&num2);

        FILE* reqPtr = fopen("/tmp/fifo_req","w");
        fprintf(reqPtr,"%d %d %s",num1,num2,fifoName);
        fclose(reqPtr);

        FILE* ansPtr = fopen(fifoName,"r");
        int sum,diff,prod;
        float div;
        fscanf(ansPtr,"%d %d %d %f",&sum,&diff,&prod,&div);
        fclose(ansPtr);

        printf("Sum: %d\n",sum);
        printf("Difference: %d\n",diff);
        printf("Product: %d\n",prod);
        printf("Ratio: %f\n",div);

        printf("Continue? (y/n)\n");
        char userAns[STR_LEN] = "";
        scanf("%s",userAns);
        if (strcmp(userAns,"y") != 0) flag = 0;
    }

    unlink(fifoName);
    return 0;
}