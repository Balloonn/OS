#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<strings.h>

int main() {
    int shmid, i;
    pid_t pid_server, pid_client;
    int *msgList;
    shmid = shmget(75, 1024, 0777|IPC_CREAT);
    msgList = (int*) shmat(shmid, 0, 0);
    pid_server = fork();
    if(pid_server < 0) {
        printf("There is an error when creating the process Server.");
    }
    else if(pid_server == 0) {
        sleep(1);
        for(i = 5; i; i--) {
            printf("Server received %d.\n", msgList[i]);
        }
    }
    else {
        pid_client = fork();
        if(pid_client < 0) {
            printf("There is an error when creating the process Client.");
        }
        else if(pid_client == 0) {
            i = 5;
            while(1) {
                msgList[i] = i;
                printf("Client sent %d.\n", msgList[i]);
                if(msgList[i] == 1) {
                    break;
                }
                i --;
            }
            exit(0);
        }
        else {
            shmdt(msgList);
            shmctl(shmid, IPC_RMID, 0);
            exit(0);
        }
    }
    return 0;
}