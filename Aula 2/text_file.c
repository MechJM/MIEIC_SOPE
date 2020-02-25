#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

#define MAX_STRLEN 50
#define MAX_STUD 20



int main(int argc,char* argv[])
{
    char students[MAX_STUD][MAX_STRLEN],ch,answer[4]="";
    int i=0,flag=1;

    while(flag)
    {   
        write(STDOUT_FILENO,"Indique o nome e classificacao do aluno:\n",41);
        int i2;
        for (i2 = 0; i2 < MAX_STRLEN; i2++)
        {
            if (read(STDIN_FILENO,&ch,1) != 1) break;
            if (ch == '\n') break;
            students[i][i2]=ch;
        }
        students[i][i2]=0; //muito importante para a string terminar corretamente!!
        write(STDOUT_FILENO,"Pretende indicar mais estudantes?(sim/nao)\n",43);
        read(STDIN_FILENO,&answer,4); //nao esquecer o \n!!
        if (strcmp(answer,"sim\n")!=0) flag=0;
        i++;
    }

    int file = open("students.txt",O_WRONLY|O_TRUNC);

    for (int i3 = 0; i3 < i; i3++)
    {
        write(file,students[i3],strlen(students[i3]));
        if (i3 != (i-1)) write(file,"\n",1);
    }

    close(file);
    
    return 0;
}

