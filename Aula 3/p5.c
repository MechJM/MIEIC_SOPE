#include <unistd.h>
#include <sys/types.h>

int main (void)
{
    pid_t pid = fork();

    if (pid == 0)
    {
        pid_t pid2 = fork();
        if (pid2 == 0)
        {
            write(STDOUT_FILENO,"friends!\n",9);
        }
        else
        {
            write(STDOUT_FILENO,"my ",3);
        }
    }
    else
    {
        write(STDOUT_FILENO,"Hello ",6);
    }
    


    return 0;
}