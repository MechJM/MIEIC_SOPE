#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

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
        int i,i2 = 0,count = 0;

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


        for (i=0;i<currentArg;i++)
        {
            //printf("%s\n",args[i]);
            execArgs[i] = args[i];

        }
        //args[currentArg] = NULL;
        execArgs[currentArg] = NULL;

        if (strcmp(execArgs[0],"quit") == 0) return 0;
       
        pid_t pid = fork();
        if (pid == 0) execvp(args[0],execArgs);
        int status;
        wait(&status);

        /*
        for (i = 0; i < MAXLEN; i++)
        {
            if (read(STDIN_FILENO,&ch,1) != 1) break;
            if (ch == ' ' || ch == '\n')
            {
                input[i] = 0;
                if (strcmp(input,"quit") == 0) return 0;
                i = -1;
                strcpy(args[i2],input);
                i2++;
                strcpy(input,"");
                if (ch == '\n') break;
            }
            else input[i] = ch;
        }
        args[i2] = NULL;
        pid_t pid = fork();
        if (pid == 0) execvp(args[0],args);
        int status;
        wait(&status);
    }*/}
}