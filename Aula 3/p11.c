#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 256

int main(void)
{
    while(1)
    {
        char input[256] = "";
        char args[10] = "";
        char ch;
        write(STDOUT_FILENO,"minish >",strlen("minish >"));
        int i,i2 = 0;
        for (i = 0; i < MAXLEN; i++)
        {
            if (read(STDIN_FILENO,&ch,1) != 1) break;
            if (ch == "\n") break;
            if (ch == " ")
            {
                input[i] = 0;
            }
            input[i] = ch;
        }
        input[i] = 0;
    }
}