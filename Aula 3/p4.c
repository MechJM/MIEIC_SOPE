#include <unistd.h>
#include <sys/types.h>

int main (void)
{
    pid_t pid;

    pid = fork();

    if (pid == 0)
    {  
        write(STDOUT_FILENO,"world!\n",7);
    }
    else
    {
       write(STDOUT_FILENO,"Hello ",6);
    }
    
    return 0;
}