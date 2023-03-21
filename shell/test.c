#include <sys/types.h> 
#include <unistd.h> 
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char **argv){
    int x;
    scanf("%d", &x);
    printf("%d", x+1);
    return 0;
}