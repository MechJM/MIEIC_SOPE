#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <pthread.h>

#define BUF_LEN 4096

struct files
{
    char sourceFile[BUF_LEN];
    char destDir[BUF_LEN];
};

void* copyFile(void* arg)
{
    struct files args = *(struct files *) arg;

    FILE* source = fopen(args.sourceFile,"r");
    FILE* dest = fopen()
    char line[BUF_LEN] = "";
    while (fscanf(source,"%s\n",line) != EOF)
    {

    }
}

int main(int argc, char* argv[])
{
    DIR* dirp;
    if ((dirp = opendir(argv[1])) == NULL) 
    {
        write(STDERR_FILENO,"Couldn't open directory.\n",25);
        exit(1);
    }

    struct stat stat_buf;

    struct dirent *dentry;
    while ((dentry = readdir(dirp)) != NULL)
    {
        if (stat(dentry->d_name,&stat_buf) < 0)
        {
            fprintf(stderr,"Couldn't get entry statistics.\n");
            exit(1);
        }

        if (S_ISREG(stat_buf.st_mode))
        {
            pthread_t tid;
            struct files args;
            pthread_create(&tid,NULL,copyFile,&args);
        }
    }
    pthread_exit(0);
}

