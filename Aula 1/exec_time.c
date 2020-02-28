#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/times.h>


int main(int argc,char *argv[])
{
    struct tms sys_time;
    clock_t start,end;
    
    start=times(&sys_time);
    double ticks_sec = sysconf(_SC_CLK_TCK);

    int num1,num2,rand_num,i=1;

    num1=atoi(argv[1]);
    num2=atoi(argv[2]);

    srand(time(NULL));

    do 
    {
    rand_num=rand()%num1;
    printf("%d:%d\n",i,rand_num);
    i++;
    } while (rand_num != num2);

    
    end=times(&sys_time);

    printf("Tempo real: %f segundos\n",(end-start)/ticks_sec);
    printf("Tempo CPU(user): %f segundos\n",(double)sys_time.tms_utime/ticks_sec);
    printf("Tempo CPU(system): %f segundos\n",(double)sys_time.tms_stime/ticks_sec);

    return 0;
}