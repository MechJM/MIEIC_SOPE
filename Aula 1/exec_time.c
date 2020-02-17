#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/times.h>


int main(int argc,char *argv[])
{
    int num1,num2,rand_num,i=1;

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


    time_t raw_time = time(0);
    struct tm *current_time=localtime(&raw_time);

    int ticks_sec = sysconf(_SC_CLK_TCK);
    struct tms *sys_time;
    times(sys_time);

    printf("Tempo real: %d:%d\n",current_time->tm_hour,current_time->tm_min);
    printf("Tempo CPU(user): %ld segundos\n",sys_time->tms_utime/ticks_sec);
    printf("Tempo CPU(system): %ld segundos\n",sys_time->tms_stime/ticks_sec);

    return 0;
}