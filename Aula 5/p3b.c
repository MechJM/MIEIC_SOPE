#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#define READ  0
#define WRITE 1
#define MAXLEN 1000

int main(int argc, char* argv[])
{
    int fd[2];
    if (pipe(fd) < 0) fprintf(stderr,"Couldn't create pipe.\n");

    pid_t pid = fork();

    if (pid == 0)
    {
        close(fd[WRITE]);
        dup2(fd[READ],STDIN_FILENO);
        execvp("sort",&argv[1]);
    }
    else if (pid > 0)
    {
        close(fd[READ]);
        dup2(fd[WRITE],STDOUT_FILENO);
        execlp("cat","cat",argv[1],NULL);
    }
    else fprintf(stderr,"Couldn't create child process.\n");

    return 0;
}