#include <stdio.h> 
#include <signal.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <wait.h>

int status;

void sigchldHandler(int signo)
{
    wait(&status);
}

int main(void) 
{   
    pid_t pid;   
    int i, n, status;   
    for (i=1; i<=10; i++) 
    {     
        pid=fork();
        if (pid == 0)
        {       
            printf("CHILD no. %d (PID=%d) working ... \n",i,getpid());       
            sleep(5); // child working ...       
            printf("CHILD no. %d (PID=%d) exiting ... \n",i,getpid());        
            exit(0);     
        }
    }

    struct sigaction action;
    action.sa_handler = SIG_IGN;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    if (sigaction(SIGCHLD,&action,NULL) < 0)
    {
        fprintf(stderr,"Couldn't install handler for child.\n");
        exit(1);
    }
    
    for (i=1 ;i<=4; i++ ) 
    {      
        printf("PARENT: working hard (task no. %d) ...\n",i);     
        n=10; 
        while((n=sleep(n))!=0);     
        printf("PARENT: end of task no. %d\n",i);   
        printf("PARENT: my child ended with value %d\n",WEXITSTATUS(status));  
    }   
    
    exit(0); 
} 

