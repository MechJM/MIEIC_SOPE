#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

#define STR_LEN 1024

char destination_dir[STR_LEN];
char filename[STR_LEN];

int process_dir(char *dirname)
{
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;
    if(!(dir=opendir(dirname)))return 1;
    while((entry=readdir(dir))!=NULL)
    {
        char path[1024];
        // ‐‐‐ BLOCO A ‐‐‐
        ...
        if(...)
        {
            //se 'entry' for um diretório
            if(strcmp(entry‐>d_name,".") == 0 || strcmp(entry‐>d_name,"..") == 0) continue; // se esta linha não existisse o processo ia continuar a procurar no próprio
                                                                                      // diretório e em todos os "diretórios-pai" até chegar à raíz do sistema
            pid_t pid = fork();
            if (pid < 0) 
            {
                fprintf(stderr,"Couldn't create process.\n");
                exit(1);
            }
            else if (pid == 0) process_dir(entry->d_name);
            //cria um processo que invoca process_dir()
        }// ‐‐‐ FIM DO BLOCOA ‐‐‐
        // ‐‐‐ BLOCO B ‐‐‐
        else if(...)
        {//se 'entry' for um ficheiro regular
        ...
            if(strstr(entry‐>d_name,filename)!=NULL)
            {//se o nome do ficheiro contiver filename...//cria um processo que invoca o utilitário 'cp'
            }
        }// ‐‐‐ FIM DO BLOCO B ‐‐‐
    }
    return 0;
}

int main (int argc, char* argv[])
{
    if (argc < 4) 
    {
        fprintf(stderr,"Usage: find_and_copy <dir_to_search> <filename> <destination_dir>\n");
        exit(1);
    }

    strcpy(destination_dir,argv[3]);
    strcpy(filename,argv[2]);

    struct sigaction action;
    action.sa_handler = SIG_IGN
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    if (sigaction(SIG_INT,&action,NULL) < 0)
    {
        fprintf(stderr, "Couldn't install signal handler.\n");
        exit(1);
    }


    process_dir(argv[1]);

    return 0;
}