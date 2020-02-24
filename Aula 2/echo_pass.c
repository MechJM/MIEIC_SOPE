#include <termios.h>
#include <unistd.h>
#include <string.h>

#define MAX_STRLEN 50

int main(int argc,char * argv[])
{
    struct termios newterm,oldterm;
    char ch,password[MAX_STRLEN] = "";

    tcgetattr(STDIN_FILENO,&oldterm);
    newterm=oldterm;
    newterm.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON);
    tcsetattr(STDIN_FILENO,TCSAFLUSH,&newterm);

    write(STDOUT_FILENO,"Indique a password:\n",20);

    for (int i=0;i<MAX_STRLEN;i++)
    {
        if (read(STDIN_FILENO,&ch,1)!=1) break;
        if (ch == '\n') break;
        password[i]=ch;
        write(STDOUT_FILENO,"*",1);
    }
   
    tcsetattr(STDIN_FILENO,TCSANOW,&oldterm);

    write(STDOUT_FILENO,"\nPassword: ",11);
    write(STDOUT_FILENO,password,strlen(password));
    write(STDOUT_FILENO,"\n",1);
    return 0;
}