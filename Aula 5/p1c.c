#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

#define READ 0
#define WRITE 1

int main(void)
{   
    int fd[2];
    if (pipe(fd) < 0) fprintf(stderr,"Couldn't create pipe.\n");
    pid_t pid = fork();

    if (pid > 0)
    {   
        printf("Indique os numeros: ");
        char* nums[2];
        scanf("%s %s",nums[0],nums[1]);
        close(fd[READ]);
        write(fd[WRITE],nums,sizeof(nums));
        close(fd[WRITE]);
    }
    else if (pid == 0)
    {
        char* nums[2];
        close(fd[WRITE]);
        read(fd[READ],nums,sizeof(nums));
        printf("Soma: %d\n",atoi(nums[0])+atoi(nums[1]));
        printf("Diferença: %d\n",atoi(nums[0])-atoi(nums[1]));
        printf("Produto: %d\n",atoi(nums[0])*atoi(nums[1]));
        if (atoi(nums[1]) == 0) fprintf(stderr,"Nao e possivel dividir por 0.\n");
        else printf("Razão: %F\n",(double)atoi(nums[0])/atoi(nums[1]));
        close(fd[READ]);
    }
    else fprintf(stderr,"Couldn't create child process.\n");
    return 0;
}