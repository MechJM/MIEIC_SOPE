#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>

#define BUF_SIZE 800
#define READ 0
#define WRITE 1


void full_copy(int from, int to)
{
    char buffer[BUF_SIZE];
    size_t n;
    while ((n = read(from,buffer,BUF_SIZE)) > 0) write(to,buffer,n);
    close(from);
    close(to);
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        fprintf(stderr,"Usage: myprog <file>\n");
        exit(1);
    }

    int file_source = open(argv[1],O_RDONLY);
    
    int fd[2];

    if (pipe(fd) < 0)
    {
        fprintf(stderr,"Couldn't create pipe.\n");
        exit(1);
    }
    pid_t pid = fork();
    if (pid < 0)
    {
        fprintf(stderr,"Couldn't create process.\n");
        exit(1);
    }
    else if (pid == 0)
    {
        close(fd[WRITE]);
        dup2(fd[READ],STDIN_FILENO);
        execlp("compress","compress",NULL);
    }
    else if (pid > 0)
    {
        close(fd[READ]);
        full_copy(file_source,fd[WRITE]);
    }

    


    return 0;
}