#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define MAXLEN 1000
#define MAX_STRLEN 50

int main(int argc, char* argv[])
{
    char source_name[MAX_STRLEN]="";
    char dest_name[MAX_STRLEN]="";
    strcpy(source_name,argv[1]);
    strcpy(dest_name,argv[2]);

    FILE* source = fopen(source_name,"r");
    FILE* dest = fopen(dest_name,"w");

    char file_content[MAXLEN]="";

    fread(file_content,1,MAXLEN,source);
    fwrite(file_content,1,MAXLEN,dest);

    fclose(source);
    fclose(dest);


    return 0;
}