#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

char command[256];

int main() {
    int callback;
    while(1) {
        printf(">");
        fgets(command, 256, stdin);
        command[strlen(command)-1] = 0;
        if(fork() == 0) {
            execlp(command, command, NULL, NULL);
            perror(command);
            exit(errno);
        }
        else {
            wait(&callback);
            printf("Child process return %d\n", callback);
        }
    }
    return 0;
}