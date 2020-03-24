#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>

#define READ  0
#define WRITE 1
#define MAXLEN 1000

int main(int argc,char* argv[])
{
    char* command[MAXLEN];
    int i2 = 0;
    int first = 1;
    for (int i = 1; argv[i] != NULL; i++)
    {
        if (strcmp(argv[i],"|") != 0)
        {
            sprintf(command[i2++],argv[i]);
        }
        else
        {
            command[i2] = NULL;
            i2 = 0;
            int fd[2];
            if (pipe(fd) < 0) fprintf(stderr,"Couldn't create pipe.\n");
            pid_t pid = fork();
            if (pid == 0)
            {
                if (!first)
                {
                    dup2(fd[READ],STDIN_FILENO);
                }
            }
            else if (pid > 0)
            {
                
            }
            else fprintf(stderr,"Couldn't create child process.\n");
        }
        
    }


    return 0;
}