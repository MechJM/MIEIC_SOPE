#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define MAXLEN 1000
#define MAX_STRLEN 50

int main(int argc,char* argv[])
{
    char source_name[MAX_STRLEN]="";
    char dest_name[MAX_STRLEN]="";
    strcpy(source_name,argv[1]);
    strcpy(dest_name,argv[2]);

    char file_content[MAXLEN]="";

    int source = open(source_name,O_RDONLY);
    int dest = open(dest_name,O_WRONLY);

    read(source,file_content,MAXLEN);
    write(dest,file_content,MAXLEN);

    close(source);
    close(dest);

    return 0;
}