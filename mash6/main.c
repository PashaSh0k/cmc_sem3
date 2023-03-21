#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>
#include <sys/wait.h>

char flag = 0;

void checkSig(int sig){
    return;
}

void endSon(int sig){
    kill(getpid(), SIGCHLD);
    exit(0);
}

void endFather(int sig){
    exit(0);
}

void changeflag(int sig){
    flag = 1;
}

int outword(int fd){
    char c;
    while(read(fd, &c, 1) == 1 && c != '\n' && c != ' '){
        putchar(c);
    }
    putchar('\n');
    if(c == -1) //end file
        return 0;
    else
        return 1;
}
int main(int argc, char **argv){
    int fd = open(argv[1], O_RDONLY, 0666);
    if(fd == -1)
        return 0;
    pid_t pid;
    int check = 1;
    signal(SIGUSR1, checkSig);
    pid = fork();
    if(pid < 0){
        perror("error");
        exit(-1);
    }
    else if(pid == 0){//son
        signal(SIGALRM, endSon);
        alarm(3);
        while(1 && check){
            pause();
            printf("Son\n");
            check = outword(fd);
            kill(getppid(), SIGUSR1);
        }
        exit(0);
    }
    else if(pid > 0){//father
        signal(SIGCHLD, changeflag);
        signal(SIGINT, endFather);
        while(!flag && check){
            printf("Father\n");
            check = outword(fd);
            if(flag)
                break;
            kill(pid, SIGUSR1);
            pause();
        }
        while(1 && check){
            printf("Father\n");
            check = outword(fd);
            sleep(1);
        }
        close(fd);
    }
    return 0;
}