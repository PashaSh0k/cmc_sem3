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
    if(key == -1)
        return 0;
    int msgid = msgget(key, 0666 | IPC_CREAT);
    int shmid = shmget(key, 100, 0666 | IPC_CREAT);
    FILE* file = fopen("text", "r");
    if(file == NULL)
        return 0;
    char* shmaddr = shmat(shmid, NULL, 0);
    int i = 0, spaces = 0, numbers = 0;
    while(fgets(shmaddr, 256, file)){
        i++;
        Message.mtype = 10;
        Message.Data = 0;
        msgsnd(msgid, &Message, sizeof(int) , 0);
        Message.mtype = 11;
        Message.Data = 0;
        msgsnd(msgid, &Message, sizeof(int) , 0);
        msgrcv(msgid, &Message, sizeof(int), 1, 0);
        numbers = Message.Data;
        msgrcv(msgid, &Message, sizeof(int), 2, 0);
        spaces = Message.Data;
        printf("№%d: count_of_spaces = %d, count_of_numbers = %d\n", i, spaces, numbers);
    }
    Message.mtype = 10;
    Message.Data = 1;
    msgsnd(msgid, &Message, sizeof(int) , 0);
    Message.mtype = 11;
    Message.Data = 1;
    msgsnd(msgid, &Message, sizeof(int) , 0);
    msgctl(msgid, IPC_RMID, NULL);
    shmctl(shmid, IPC_RMID, NULL);
    shmdt(shmaddr);
    fclose(file);
    return 0;
}