#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

#define STR_LEN 1000

int findText(char * text,char * file)
{
    FILE* filePtr = fopen(file,"r");
    char line[STR_LEN] = "";
    int i = 1;
    while (fgets(line,STR_LEN,filePtr) != NULL)
    {
        if (strstr(line,text) != NULL) 
        {
            fclose(filePtr);
            return i;
        }
        i++;
    }
    fclose(filePtr);
    return -1;
}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        fprintf(stderr,"Usage: <text_to_search> <file_name>\n");
        exit(1);
    }

    int searchResult = findText(argv[1],argv[2]);

    if (searchResult < 0) printf("Couldn't find that text.\n");
    else printf("Found on line: %d\n",searchResult);


    return 0;
}