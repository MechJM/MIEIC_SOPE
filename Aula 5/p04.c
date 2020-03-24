#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

#define READ  0
#define WRITE 1

int main(int argc,char* argv[])
{
    int fd[2];
    if (pipe(fd)  < 0) fprintf(stderr,"Couldn't create pipe.\n");

    pid_t pid;

    pid = fork();

    if (pid > 0)
    {
        close(fd[READ]);
        dup2(fd[WRITE],STDOUT_FILENO);
        execlp("ls","ls",argv[1],"-laR",NULL);
    }
    else if (pid == 0)
    {
        int fd2[2];
        if (pipe(fd2) < 0) fprintf(stderr,"Couldn't create pipe.\n");

        pid_t pid2;
        pid2 = fork();

        if (pid2 > 0)
        {
            close(fd[WRITE]);
            close(fd2[READ]);
            dup2(fd[READ],STDIN_FILENO);
            dup2(fd2[WRITE],STDOUT_FILENO);
            execlp("grep","grep",argv[2],NULL);
        }
        else if (pid2 == 0)
        {
            close(fd2[WRITE]);
            dup2(fd2[READ],STDIN_FILENO);
            execlp("sort","sort",NULL);
        }
        else fprintf(stderr,"Couldn't create pipe.\n");
        
    }
    else fprintf(stderr,"Couldn't create child process.\n");



    return 0;
}