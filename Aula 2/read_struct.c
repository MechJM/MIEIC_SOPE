#include <fcntl.h>
#include <unistd.h>
#include <string.h>

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
    int file = open("students_struct",O_RDONLY);

    read(file,students,sizeof(students));

    for (int i = 0; i < MAX_STUD; i++)
    {
        write(STDOUT_FILENO,"Nome: ",6);
        write(STDOUT_FILENO,students[i].name,strlen(students[i].name));
        write(STDOUT_FILENO,"\n",1);
        write(STDOUT_FILENO,"Classificacao: ",15);
        write(STDOUT_FILENO,&students[i].score,2);
        write(STDOUT_FILENO,"\n",1);
    }
    

    close(file);
    return 0;
}