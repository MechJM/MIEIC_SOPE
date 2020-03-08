#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[],char *envp[])
{
    pid_t pid;
    if (argc < 2)
    {
        printf("Usage: %s dirname [filename]\n",argv[0]);
        exit(1);
    }
    pid = fork();
    
    if (pid > 0) 
    {
        if (argc == 2) printf("My child is going to execute command \"ls -laR %s\"\n",argv[1]);
        else if (argc == 3) printf("My child is going to execute command \"ls -laR %s\" and redirect its output\n",argv[1]);
    }
    else if (pid == 0)
    {
        if (argc == 3)
        {
            int file = open(argv[2],O_CREAT|O_WRONLY|O_EXCL);
            dup2(file,STDOUT_FILENO);
        }

        execlp("ls","ls","-lsR",argv[1],NULL);
        printf("Command not executed! \n");
        exit(1);
    }
    exit(0);
}