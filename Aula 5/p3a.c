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
        execvp("sort",&argv[1]); //I forgot to copy arg0 but it somehow works
    }
    else if (pid > 0)
    {
        
        close(fd[READ]);
        char content[MAXLEN];

        int filedes;
                
        if ((filedes = open(argv[1],O_RDONLY)) < 0) fprintf(stderr,"Couldn't open file.\n");

        read(filedes,content,MAXLEN);

        write(fd[WRITE],content,strlen(content));

        close(fd[WRITE]);
    }
    else fprintf(stderr,"Couldn't create child process.\n");

    return 0;
}