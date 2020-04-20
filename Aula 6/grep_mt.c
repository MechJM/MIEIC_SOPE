#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

#define STR_LEN 1000
#define THREAD_NUM 100

struct args
{
    char * text;
    char * file;
};

void * findText(void * arg)
{
    FILE* filePtr = fopen((*(struct args*)arg).file,"r");
    char line[STR_LEN] = "";
    int i = 1;
    int * resPtr = malloc(sizeof(int));
    while (fgets(line,STR_LEN,filePtr) != NULL)
    {
        if (strstr(line,(*(struct args*)arg).text) != NULL) 
        {
            fclose(filePtr);
            *resPtr = i;
            return resPtr;
        }
        i++;
    }
    fclose(filePtr);
    
    *resPtr = -1;
    return resPtr;
}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        fprintf(stderr,"Usage: <text_to_search> <file_name>\n");
        exit(1);
    }

    struct args args_arr[THREAD_NUM];
    pthread_t tids[THREAD_NUM];

    for (int i = 2; argv[i] != NULL; i++)
    {
        args_arr[i-2].text = argv[1];
        args_arr[i-2].file = argv[i];
        pthread_create(&tids[i-2],NULL,findText,&args_arr[i-2]);
    }

    void * results[THREAD_NUM];

    for (int i = 0; i < (argc - 2); i++)
    {
        pthread_join(tids[i],&results[i]);

        int searchResult = * (int *) results[i];

        if (searchResult < 0) printf("Couldn't find that text.\n");
        else printf("Found on line: %d\n",searchResult);
        free(results[i]);
    }


    return 0;
}