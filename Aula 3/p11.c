#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define MAXLEN 256
#define ARGNO 10

int main(void)
{
    while(1)
    {
        char input[MAXLEN] = "";
        char args[ARGNO][MAXLEN];
        char ch;
        write(STDOUT_FILENO,"minish >",strlen("minish >"));

        int currentArg = 0;
        int currentArgLen = 0;

        for (read(STDIN_FILENO,&ch,1);ch != '\n';read(STDIN_FILENO,&ch,1)) {
            if (ch == ' '){
                args[currentArg][currentArgLen] = '\0';
                currentArg++;
                currentArgLen = 0;
            } 
            else {
                args[currentArg][currentArgLen] = ch;
                currentArgLen++;
            }
        }
        args[currentArg][currentArgLen] = '\0';
        currentArg++;

        char * execArgs[currentArg+1]; 

        int redirect = 0;

        for (int i=0;i<currentArg;i++)
        {
            if (strcmp(args[i],"-o") == 0 && strcmp(args[i+1],"") != 0)
            {
                redirect = 1;
                break;
            }
            else execArgs[i] = args[i];
        }
        
        if (!redirect) execArgs[currentArg] = NULL;
        else execArgs[currentArg-2] = NULL;

        if (strcmp(execArgs[0],"quit") == 0) return 0;
       
        pid_t pid = fork();
        if (pid == 0) 
        {
            if (redirect)
            {
                int file = open(args[currentArg-1],O_CREAT|O_WRONLY,0600);
                dup2(file,STDOUT_FILENO);
            }

            execvp(args[0],execArgs);
        }
        int status;
        wait(&status);
    }
}