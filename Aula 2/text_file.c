#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

#define MAX_STRLEN 50
#define MAX_STUD 20



int main(int argc,char* argv[])
{
    char students[MAX_STUD][MAX_STRLEN],ch,answer[3]="";
    int i=0,flag=1;

    while(flag)
    {   
        write(STDOUT_FILENO,"Indique o nome e classificacao do aluno:\n",41);
        for (int i2=0;i2<MAX_STRLEN;i2++)
        {
            if (ch == '\n') break;
            if (read(STDIN_FILENO,&ch,1) != 1) break;
            students[i][i2]=ch;
        }
        write(STDOUT_FILENO,"Pretende indicar mais estudantes?(sim/nao)\n",43);
        read(STDIN_FILENO,&answer,3);
        if (strcmp(answer,"sim")!=0) flag=0;
        i++;
    }

    int file = open("students.txt",O_WRONLY|O_TRUNC);

    for (int i3 = 0; i3 < i; i3++)
    {
        write(file,students[i3],strlen(students[i3]));
    }

    close(file);
    
    return 0;
}

