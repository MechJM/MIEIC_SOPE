#include <stdio.h>
#include <stdlib.h>

#define BUF_LENGTH 256
#define MAX 1000

//d) e suposto deixar aparecer "No such file or directory"?

int main(void)
{
    FILE *src,*dst;
    char buf[BUF_LENGTH];
    if ((src=fopen("infile.txt","r"))==NULL)
    {
        perror("Nao foi possivel abrir o ficheiro infile.txt\n");
        exit(1);
    }
    if((dst=fopen("outfile.txt","w"))==NULL)
    {
        perror("Nao foi possivel abrir o ficheiro outfile.txt\n");
        exit(2);
    }
    while((fgets(buf,MAX,src))!=NULL)
    {
        fputs(buf,dst);
    }
    fclose(src);
    fclose(dst);
    exit(0);
}