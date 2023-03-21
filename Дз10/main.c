#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#define MAXSIZE 1000

int main(int argc, char **argv){
    if (argc != 2){
        perror("error\n");
        return 0;
    }
    FILE* f = fopen(argv[1], "r+");
    if(f == NULL)
        return 0;
    int fd1[2], fd2[2];
    pipe(fd1);
    pipe(fd2);
    pid_t pid;
    char str[MAXSIZE];
    if((pid = fork()) < 0){
        perror("error");
        exit(-1);
    }
    else if(pid == 0){ //сын
        char tmp;
        while(read(fd1[0], str, sizeof(str))){
            int str_len = strlen(str);
            if(str[str_len - 1] == '\n')
                str_len--;
            for(int i = 0; i < str_len / 2; i++){
                tmp = str[i];
                str[i] = str[str_len - 1 - i];
                str[str_len - 1 - i] = tmp;
            }
            write(fd2[1], str, sizeof(str));
        }
        close(fd1[1]);
        close(fd2[0]);
        close(fd1[0]);
        close(fd2[1]);
        exit(0);
    }
    else if(pid > 0){ // отец
        while(fgets(str, MAXSIZE, f)){
            write(fd1[1], str, sizeof(str));
            read(fd2[0], str, sizeof(str));
            fseek(f, -strlen(str), SEEK_CUR);
            fprintf(f, "%s", str);
        }
        close(fd1[1]);
        close(fd2[0]);
        close(fd1[0]);
        close(fd2[1]);
        wait(NULL);
        fclose(f);
        
    }
    return 0;
}