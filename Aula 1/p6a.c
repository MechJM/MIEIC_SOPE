#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define BUF_LENGTH 256
#define MAX 1000

//d) e suposto deixar aparecer "No such file or directory"?

/*
int main(void)
{
    FILE *src,*dst;
    char buf[BUF_LENGTH];
    if ((src=fopen("infile.txt","r"))==NULL)
    {
        //d)
        //perror("Nao foi possivel abrir o ficheiro infile.txt\n");
        //e)
        printf("errno = %d\n",errno);
        exit(1);
    }
    if((dst=fopen("outfile.txt","w"))==NULL)
    {
        //d)
        //perror("Nao foi possivel abrir o ficheiro outfile.txt\n");
        //e)
        printf("errno = %d\n",errno);
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
*/


//g) e h)
int main(int argc, char* argv[])
{
    char infile_name[BUF_LENGTH]="";
    char outfile_name[BUF_LENGTH]="";

    for (int i=1;i<argc;i++)
    {
        if (i==1) strcpy(infile_name,argv[i]);
        if (i==2) strcpy(outfile_name,argv[i]);
    }

    if (strcmp(infile_name,"")==0 && strcmp(outfile_name,"")==0) 
    {    
        printf("usage:p6a file1 file2\n");
        exit(0);
    }
    FILE *src,*dst;
    char buf[BUF_LENGTH];
    if ((src=fopen(infile_name,"r"))==NULL)
    {
        printf("errno = %d\n",errno);
        exit(1);
    }
    if((dst=fopen(outfile_name,"w"))==NULL)
    {
        printf("errno = %d\n",errno);
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