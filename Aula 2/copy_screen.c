#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define MAXLEN 1000
#define MAX_STRLEN 50

int main(int argc, char* argv[])
{
    char file_content[MAXLEN]="";

    int source = open(argv[1],O_RDONLY);
    read(source,file_content,MAXLEN);

    if (argc == 3)
    {
        int dest=open(argv[2],O_WRONLY);
        dup2(dest,STDOUT_FILENO);
    }

    write(STDOUT_FILENO,file_content,MAXLEN);

    close(source);
    close(STDOUT_FILENO);

    return 0;
}