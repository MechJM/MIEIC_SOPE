#include <stdio.h>
#include <stdlib.h>

void atexit_handler1(void)
{
    printf("Executing exit handler 1\n");
    //exit(0);
}

void atexit_handler2(void)
{
    printf("Executing exit handler 2\n");
    //exit(0);
}

int main(void)
{
    //abort();
    printf("Main done!\n");
    atexit(atexit_handler2);
    atexit(atexit_handler1);
    exit(0);
}