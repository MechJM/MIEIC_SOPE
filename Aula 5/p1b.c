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

    struct nums
    {
        int num1;
        int num2;
    };

    if (pid > 0)
    {   
        struct nums nums;
        printf("Indique os numeros: ");
        scanf("%d %d",&nums.num1,&nums.num2);
        close(fd[READ]);
        write(fd[WRITE],&nums,sizeof(nums));
        close(fd[WRITE]);
    }
    else if (pid == 0)
    {
        struct nums nums;
        close(fd[WRITE]);
        read(fd[READ],&nums,sizeof(nums));
        printf("Soma: %d\n",nums.num1+nums.num2);
        printf("Diferença: %d\n",nums.num1-nums.num2);
        printf("Produto: %d\n",nums.num1*nums.num2);
        if (nums.num2 == 0) fprintf(stderr,"Nao e possivel dividir por 0.\n");
        else printf("Razão: %F\n",(double)nums.num1/nums.num2);
        close(fd[READ]);
    }
    else fprintf(stderr,"Couldn't create child process.\n");
    return 0;
}