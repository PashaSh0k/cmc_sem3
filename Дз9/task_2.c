#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<dirent.h>
//#include <dir.h>
#define MAXDIR 1000

typedef struct dirent dirent;
void outalldir(char* directory){
    char* catalog = (char*)malloc(MAXDIR * sizeof(char));
    dirent* dir;
    DIR* direct = opendir(directory);
    struct stat info;
    while((dir = readdir(direct)) != NULL){
        if(strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0){
            stat(dir->d_name, &info);
            if(info.st_mode & S_IFDIR){// directory or file?
                printf("%s\n", dir->d_name);
                if(chdir(dir->d_name) == 0){
                    getcwd(catalog, MAXDIR);
                    outalldir(catalog);
                    chdir("..");
                }
            }
        }
    }
    free(dir);
    closedir(direct);
    free(catalog);
    return;
}
int main(int argc, char **argv){
    char* directory = (char*)malloc(MAXDIR * sizeof(char));
    getcwd(directory, MAXDIR);
    printf("Now directory is %s\n", directory);
    outalldir(directory);
    printf("That is all catalogs in this directory\n");
    free(directory);
    return 0;
}