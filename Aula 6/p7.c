#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

#define BUF_LEN 4096
#define NUM_THREADS 100

struct files
{
    char sourceFile[BUF_LEN];
    char destFile[BUF_LEN];
};

void* copyFile(void* arg)
{
    struct files args = *(struct files *) arg;

    FILE* source = fopen(args.sourceFile,"r");
    FILE* dest = fopen(args.destFile,"w");
    char line[BUF_LEN] = "";
    while (fscanf(source,"%s\n",line) != EOF)
    {
        fprintf(dest,"%s\n",line);
    }
    return NULL;
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        fprintf(stderr,"Usage: ./p7 <source_dir> <dest_dir>\n");
        exit(1);
    }

    DIR* dirp;
    if ((dirp = opendir(argv[1])) == NULL) 
    {
        write(STDERR_FILENO,"Couldn't open directory.\n",25);
        exit(1);
    }

    struct stat stat_buf;
    pthread_t tids[NUM_THREADS];
    struct files args_arr[NUM_THREADS];
    int i = 0;

    struct dirent *dentry;
    while ((dentry = readdir(dirp)) != NULL)
    {
        char path[BUF_LEN] = "";
        sprintf(path,"%s/%s",argv[1],dentry->d_name);

        if (stat(path,&stat_buf) < 0)
        {
            fprintf(stderr,"Couldn't get entry statistics.\n");
            exit(1);
        }



        if (S_ISREG(stat_buf.st_mode))
        {
            sprintf(args_arr[i].sourceFile,"%s/%s",argv[1],dentry->d_name);
            sprintf(args_arr[i].destFile,"%s/%s",argv[2],dentry->d_name);

            //printf("%s\n",args_arr[i].sourceFile);
            
            pthread_create(&tids[i],NULL,copyFile,&args_arr[i]);
        }
        i++;
    }
    pthread_exit(0);
}

