#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


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


    return 0;
}