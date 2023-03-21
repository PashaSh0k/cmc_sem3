#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv){
    if(argc > 6 || argc < 6){
        perror("incorrect number of parametrs\n");
        return 0;
    }
    if(atoi(argv[5]) == 1){
        pid_t p1 = fork();
        if(p1 == -1){
            perror("can't create process one\n");
            return 0;
        }
        if(p1 == 0){ //сын
            execl(argv[1], argv[1], argv[2], NULL);
            perror("error with file1/arg11\n");
            exit(-1);
        }
        pid_t p2 = fork();
        if(p2 == -1){
            perror("can't create process two\n");
            return 0;
        }
        if(p2 == 0){ //сын
            execl(argv[3], argv[3], argv[4], NULL);
            perror("error with file2/arg21\n");
            exit(-1);
        }
        int status1, status2;
        waitpid(p1, &status1, 0);
        waitpid(p2, &status2, 0);
        if(WIFEXITED(status1) != 0)
            printf("process one successful done with status = %d\n", WEXITSTATUS(status1));
        else{
            perror("error with process one\n");
            return 0;
        }
        if(WIFEXITED(status2) != 0)
            printf("process two successful done with status = %d\n", WEXITSTATUS(status2));
        else{
            perror("error with process two\n");
            return 0;
        }
        return 0;
    }
    else if(atoi(argv[5]) == 2){
        pid_t p1 = fork();
        if(p1 == -1){
            perror("can't create process one\n");
            return 0;
        }
        if(p1 == 0){ //сын
            char* vector[3] = {argv[1], argv[2], NULL}; 
            execv(argv[1], vector);
            perror("error with file1/arg11\n");
            exit(-1);
        }
        int status1;
        waitpid(p1, &status1, 0);
        if(WIFEXITED(status1) != 0)
            printf("process one successful done with status = %d\n", WEXITSTATUS(status1));
        else{
            perror("error with process one\n");
            return 0;
        }
        p1 = fork();
        if(p1 == -1){
            perror("can't create process two\n");
            return 0;
        }
        if(p1 == 0){ //сын
            char* vector[3] = {argv[3], argv[4], NULL}; 
            execv(argv[3], vector);
            perror("error with file2/arg21\n");
            exit(-1);
        }
        waitpid(p1, &status1, 0);
        if(WIFEXITED(status1) != 0)
            printf("process two successful done with status = %d\n", WEXITSTATUS(status1));
        else{
            perror("error with process two\n");
            return 0;
        }
        return 0;
    }
    perror("error with argv[5]");
    return 0;
}