#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#include<sys/msg.h>

typedef struct MSG {
    long type;
    char m[500];
} MSG;

int main() {
    pid_t pid_client;
    pid_client = fork();
    if(pid_client < 0) {
        printf("There is an error when creating the process Client.");
    }
    else if(pid_client == 0) {
        int msgqid;
        msgqid = msgget(75, IPC_CREAT|0666);
        MSG msg;
        memset(msg.m, 0, sizeof(msg.m));
        msg.type = 7;
        char const *message = "SUCCESS";
        for(int i=0;i<8;i++) {
            strcpy(msg.m, message);
            sleep(1);
            msgsnd(msgqid, &msg, sizeof(msg.m), 0);
            printf("Client has sent datatype %ld: %s\n", msg.type, msg.m);
            msg.type --;
            message ++;
            if(msg.type == 0) {
                sleep(1);
                printf("Client send complete.\n");
                exit(0);
            }
        }
    }
    else {
        pid_t pid_server;
        pid_server = fork();
        if(pid_server < 0) {
            printf("There is an error when creating the process Server.");
        }
        else if(pid_server == 0) {
            int msgqid;
            int type = 7;
            msgqid = msgget(75, IPC_CREAT|0666);
            MSG msg;
            while(1) {
                msgrcv(msgqid, &msg, sizeof(msg.m), type, 0);
                printf("\t\t\t\t\tServer has received datatype %d: %s\n", type, msg.m);
                type --;
                if(msg.type == 0) {
                    msgctl(msgqid, IPC_RMID, NULL);
                    sleep(1);
                    printf("Server get type 1, complete.\n");
                    sleep(1);
                    printf("Message queue destroyed.\n");
                    sleep(2);
                    exit(0);
                }
            }
        }
        else {
            wait(NULL);
            sleep(1);
            printf("Quit main process\n");
        }
    }
    return 0;
}