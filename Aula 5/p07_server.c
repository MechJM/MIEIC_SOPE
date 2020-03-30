#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <signal.h>

void sigint_handler(int signo)
{
    unlink("/tmp/fifo_req");
    unlink("/tmp/fifo_ans");
}

int main(void)
{
    int num1,num2;

    struct sigaction action;
    action.sa_handler = sigint_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    sigaction(SIGINT,&action,NULL);

    if (mkfifo("/tmp/fifo_req",0600) < 0) fprintf(stderr,"Couldn't create FIFO.\n");
    if (mkfifo("/tmp/fifo_ans",0600) < 0) fprintf(stderr,"Couldn't create FIFO.\n");
    
    do
    {
        FILE* reqPtr = fopen("/tmp/fifo_req","r");
        fscanf(reqPtr,"%d %d",&num1,&num2);
        fclose(reqPtr);

        int   sum = num1 + num2;
        int  diff = num1 - num2;
        int  prod = num1 * num2;
        float div;
        if (num2 == 0) div = -1;
        else div = num1 / num2;

        FILE* ansPtr = fopen("/tmp/fifo_ans","w");
        fprintf(ansPtr,"%d\n%d\n%d\n%f",sum,diff,prod,div);
        fclose(ansPtr);

    } while (num1 != 0 || num2 != 0);

    unlink("/tmp/fifo_req");
    unlink("/tmp/fifo_ans");
    return 0;    
}
