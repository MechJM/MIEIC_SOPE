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
        int nums[2];
        printf("Indique os numeros: ");
        scanf("%d %d",&nums[0],&nums[1]);
        close(fd[READ]);
        write(fd[WRITE],nums,2*sizeof(int));
        close(fd[WRITE]);
    }
    else if (pid == 0)
    {
        close(fd[WRITE]);
        int nums[2];
        read(fd[READ],nums,2*sizeof(int));
        printf("Soma: %d\n",nums[0]+nums[1]);
        printf("Diferença: %d\n",nums[0]-nums[1]);
        printf("Produto: %d\n",nums[0]*nums[1]);
        if (nums[1] == 0) fprintf(stderr,"Nao e possivel dividir por 0.\n");
        else printf("Razão: %F\n",(double)nums[0]/nums[1]);
        close(fd[READ]);
    }
    else fprintf(stderr,"Couldn't create child process.\n");
    return 0;
}