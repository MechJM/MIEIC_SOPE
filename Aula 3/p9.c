#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[],char *envp[])
{
    pid_t pid;
    if (argc != 2)
    {
        printf("Usage: %s dirname\n",argv[0]);
        exit(1);
    }
    pid = fork();
    if (pid > 0) 
    {
        printf("My child is going to execute command \"ls -laR %s\"\n",argv[1]);
        int status;
        wait(&status);
        printf("My child returned %d\n",WEXITSTATUS(status));
        if (WIFEXITED(status)) printf("My child terminated normally\n");
        else printf("My child terminated abnormally\n");
    }
    else if (pid == 0)
    {
        char* const args[4] = {"ls","-laR",argv[1],NULL};
        execvp("ls",args);
        printf("Command not executed! \n");
        exit(1);
    }
    exit(0);
}