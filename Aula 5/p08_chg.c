#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc,char* argv[])
{
    if (argc != 2)
    {
        fprintf(stderr,"Usage: p08_chg [message]\n");
        exit(1);
    }

    FILE* fifoPtr = fopen("/tmp/fifo_chg","w");
    fprintf(fifoPtr,"%s",argv[1]);
    fclose(fifoPtr);

    return 0;
}