#include <stdlib.h>
#include <signal.h>

char* bits;
int counter;

void sigusr1_handler(int signo)
{
    signo = signo;
    strcat(bits,"0");
    counter++;
}

void sigusr2_handler(int signo)
{
    signo = signo;
    strcat(bits,"1");
    counter++;
}

int main(int argc, char* argv[])
{
    int numbits = atoi(argv[1]);
    bits = calloc(numbits + 1, sizeof(char));
    counter = 0;
    /*
    struct sigaction action;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    action.sa_handler = sigusr1_handler;
    sigaction(SIGUSR1,&action,NULL);

    struct sigaction action2;
    sigemptyset(&action2.sa_mask);
    action2.sa_flags = 0;
    action2.sa_handler = sigusr2_handler;
    sigaction(SIGUSR2,&action,NULL);
    */
    for (int i = 1; i <= numbits; i++ )
    {
        if (fork() == 0) execl("/home/sope/gen_bit","/home/sope/gen_bit",NULL);
        else
        {
            int ret;
            wait(&ret);
            //ret = rand() % 2;
            strcat(bits, ret == 0 ? "0" : "1");
        }
    }
    /*
    while (counter < numbits)
    {

    }*/
    printf("%s",bits);
    return 0;
}