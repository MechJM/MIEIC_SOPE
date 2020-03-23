#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

#define READ 0
#define WRITE 1

struct results
{
    int sum;
    int diff;
    int prod;
    int div_int;
    float div_float;
};

int main(void)
{   
    int fd[2],fd2[2];
    if (pipe(fd)  < 0) fprintf(stderr,"Couldn't create pipe.\n");
    if (pipe(fd2) < 0) fprintf(stderr,"Couldn't create pipe.\n");
    pid_t pid = fork();

    if (pid > 0)
    {   
        struct results res;

        close(fd[READ]);
        close(fd2[WRITE]);
        int nums[2];
        printf("Indique os numeros: ");
        scanf("%d %d",&nums[0],&nums[1]);
        
        write(fd[WRITE],nums,2*sizeof(int));
        close(fd[WRITE]);

        read(fd2[READ],&res,sizeof(res));
        printf("Soma: %d\n",res.sum);
        printf("Diferença: %d\n",res.diff);
        printf("Produto: %d\n",res.prod);
        if (res.div_int == -1 && res.div_float == -1) printf("A razao nao e valida.\n");
        else if (res.div_int == -1 && res.div_float != -1) printf("Razao: %f\n",res.div_float);
        else printf("Razao: %d\n",res.div_int);

        close(fd2[READ]);
    }
    else if (pid == 0)
    {
        close(fd[WRITE]);
        close(fd2[READ]);
        int nums[2];
        read(fd[READ],nums,2*sizeof(int));
        close(fd[READ]);
        
        struct results res;

        res.sum  = nums[0] + nums[1];
        res.diff = nums[0] - nums[1];
        res.prod = nums[0] * nums[1];
        if (nums[1] == 0) {res.div_int = -1; res.div_float = -1;}
        else if (nums[0] % nums[1] == 0) {res.div_int = nums[0] / nums[1]; res.div_float = -1;}
        else {res.div_float = (float) nums[0] / nums[1]; res.div_int = -1;}

        write(fd2[WRITE],&res,sizeof(res));
        close(fd2[WRITE]);
    }
    else fprintf(stderr,"Couldn't create child process.\n");
    return 0;
}