#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char **argv){
    FILE* f = fopen(argv[1], "w");
    if(f == NULL)
        return 0;
    int fd1[2], fd2[2];
    pipe(fd1);
    pipe(fd2);
    pid_t pid;
    if((pid = fork()) < 0){
        perror("error");
        exit(-1);
    }
    else if(pid == 0){
        close(fd1[0]);
        int flag = 1, k = 0;
        char str[80];
        int x;
        while(strcmp(str, "exit\n")){
            if(k > 0){
                read(fd2[0], &flag, sizeof(int));
            }
            scanf("%d", &x);
            fgets(str, 80, stdin);
            if(strcmp(str, "exit\n")){
                fputs(str,f);
                fflush(f);
            }
            write(fd1[1], &x, sizeof(int));
            write(fd1[1], str, sizeof(str));
            k++;
        }
        wait(NULL);
        close(fd1[1]);
        close(fd2[1]);
        fclose(f);
    }
    else if(pid > 0){
        int flag = 1;
        char str[80];
        int x, len;
        close(fd1[1]);
        while(strcmp(str, "exit\n")){
            read(fd1[0], &x ,sizeof(int));
            read(fd1[0], str, sizeof(str));
            len = strlen(str) - 1;
            if(x >= len){
                int i = 0;
                while(str[i] != '\n'){
                    str[i] = '*';
                    i++;
                }
            }
            else{
                int i = len/2;
                for(int j = 0; j < x; j++){
                    str[i] = '*';
                    i++;
                }
            }
            if(strcmp(str, "exit\n")){
                fputs(str, f);
                fflush(f);
            }
            write(fd2[1], &flag, sizeof(int));
        }
        close(fd1[0]);
        close(fd2[0]);
    }
    return 0;
}