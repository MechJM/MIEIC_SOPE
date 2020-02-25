#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

#define MAX_STRLEN 50
#define MAX_STUD 20

typedef struct Student
{
    char name[MAX_STRLEN+1];
    int score;
}Student;

int main(void)
{
    Student students[MAX_STUD];
    char ch,answer[4];
    int flag=1,i2=0;

    while (flag)
    {
        Student student;
        write(STDOUT_FILENO,"Indique o nome do aluno:\n",25);
        int i=0;
        for ( i = 0; i < (MAX_STRLEN+1); i++)
        {
            if (read(STDIN_FILENO,&ch,1)!=1) break;
            if (ch == '\n') break;
            student.name[i]=ch;
        }
        student.name[i]=0;
        write(STDOUT_FILENO,"Indique a classificacao:\n",25);
        read(STDIN_FILENO,&student.score,2);
        read(STDIN_FILENO,&ch,1); //para limpar o \n do buffer

        write(STDOUT_FILENO,"Pretende indicar mais estudantes?(sim/nao)\n",43);
        read(STDIN_FILENO,&answer,4);
        if (strcmp(answer,"sim\n")!=0) flag=0;

        students[i2]=student;
        i2++;
    }

    int file = open("students_struct",O_WRONLY);
    write(file,students,sizeof(students));
    close(file);

    return 0;
}
