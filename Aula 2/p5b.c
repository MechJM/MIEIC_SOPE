#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
    int fd;
    char *text1="CCCCC";
    char *text2="DDDDD\n";
    fd = open("f1.txt", O_WRONLY|O_APPEND,0600);
    write(fd,text1,5);
    write(fd,text2,6);
    close(fd);
    return 0;
}