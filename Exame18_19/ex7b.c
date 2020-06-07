#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>

#define BUF_SIZE 800
#define READ 0
#define WRITE 1

struct Request 
{
    pid_t pid;
    size_t nbytes;
    char data[1000];
};

struct Reply
{
    size_t nbytes;
    char data[1000];
};

void createRequest(const char *filename, struct Request *req)
{
    int file = open(filename,O_RDONLY);
    char buffer[BUF_SIZE]; // BUF_SIZE < 1000
    size_t n;
    req->pid = getpid();
    req->nbytes = 0;
    while ((n = read(file,buffer,BUF_SIZE)) > 0)
    {
        memcpy(&req->data[req->nbytes], buffer, n);
        req->nbytes += n;
    }
    close(file);
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        fprintf(stderr,"Usage: myprog <file>\n");
        exit(1);
    }

    struct Request req;
    createRequest(argv[1],&req);
    
    char fifoname[100] = "";
    sprintf(fifoname,"ans%d",getpid());
    mkfifo(fifoname,0600);
    
    int req_fd = open("requests",O_WRONLY);
    write(req_fd,&req,sizeof(req));
    close(req_fd);

    struct Reply ans;
    int ans_fd = open(fifoname,O_RDONLY);
    read(ans_fd,&ans,sizeof(ans));
    close(ans_fd);
    
    printf("%s",ans.data);
    unlink(fifoname);

    return 0;
}