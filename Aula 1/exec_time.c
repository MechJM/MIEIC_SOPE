#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/times.h>


int main(int argc,char *argv[])
{
    int num1,num2,rand_num,i=1;
    struct tms sys_time;
    clock_t start,end;

    start=times(&sys_time);

    num1=atoi(argv[1]);
    num2=atoi(argv[2]);

    srand(time(NULL));
    rand_num=rand()%num1;
    printf("%d:%d\n",i,rand_num);

    while(rand_num!=num2)
    {
        i++;
        rand_num=rand()%num1;
        printf("%d:%d\n",i,rand_num);
        sleep(1);
    }

    long int ticks_sec = sysconf(_SC_CLK_TCK);
    end=times(&sys_time);

    printf("Tempo real: %ld segundos\n",(end-start)/ticks_sec);
    printf("Tempo CPU(user): %f segundos\n",(double)sys_time.tms_utime/ticks_sec);
    printf("Tempo CPU(system): %f segundos\n",(double)sys_time.tms_stime/ticks_sec);

    return 0;
}