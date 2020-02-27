#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
    int fd;
    char *text1="AAAAA";
    char *text2="BBBBB\n";
    fd = open("f1.txt",O_CREAT|O_WRONLY|O_SYNC|O_APPEND,0600);
    getchar();
    write(fd,text1,5);
    write(fd,text2,6);
    close(fd);
    return 0;
}
