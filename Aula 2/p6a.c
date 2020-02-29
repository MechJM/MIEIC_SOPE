#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <dirent.h> 
#include <sys/stat.h> 
#include <errno.h> 
#include <unistd.h>

int main(int argc, char *argv[]) 
{  
    DIR *dirp;  
    struct dirent *direntp;  
    struct stat stat_buf;  
    char *str;  
    
    if (argc != 2)  
    {   
        fprintf( stderr, "Usage: %s dir_name\n", argv[0]);   
        exit(1);  
    }  
    
    if ((dirp = opendir( argv[1])) == NULL)  
    {   
        perror(argv[1]);   
        exit(2);  
    }  
    
    link("temp.txt","temp1.txt");
    symlink("temp.txt","temp2.txt");

    while ((direntp = readdir( dirp)) != NULL)  
    {   
        //lstat(direntp->d_name, &stat_buf);   
        stat(direntp->d_name, &stat_buf);
        if (S_ISREG(stat_buf.st_mode)) str = "regular";
        else if (S_ISDIR(stat_buf.st_mode)) str = "directory";   
        else str = "other"; 
        printf("%-10ld  ",stat_buf.st_ino);  
        if (strcmp(str,"regular") !=0) printf("%-25s - %s\n", direntp->d_name, str);  
        else printf("%-25s - %-10s %ld\n",direntp->d_name,str,stat_buf.st_size);
    }  
    
    closedir(dirp);  
    exit(0); 
} 



