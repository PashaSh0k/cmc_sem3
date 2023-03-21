#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <string.h>

struct{
    long mtype;
    int Data;
} Message;

int main(int argc, char** argv){
    key_t key = ftok("main.c", '1');
    int msgid = msgget(key, 0666);
    int shmid = shmget(key, 100, 0666);
    char buf[256];
    int count;
    char* shmaddr = shmat(shmid, NULL, 0);
    while(1){
        count = 0;
        msgrcv(msgid, &Message, sizeof(int), 11, 0);
        if(Message.Data == 1)
            break;
        strcpy(buf, shmaddr);
        for(int i = 0; i < strlen(buf); i++)
            if(buf[i] == ' ')
                count++;
        Message.Data = count;
        Message.mtype = 2;
        msgsnd(msgid, &Message, sizeof(int) , 0);
    }
    shmdt(shmaddr);
    return 0;
}