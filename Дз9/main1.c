#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    for(int i = 0; i < atoi(argv[1]); i++){
        printf("%d: pid = %d\n", i, getpid());
        sleep(1);
    }
    return 3;
}
