#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

static void sig_usr(int);

int main(void) {
    if(signal(SIGUSR1, sig_usr) == SIG_ERR) {
        printf("Can not catch SIGUSR1\n");
        exit(1);
    }
    if(signal(SIGUSR2, sig_usr) == SIG_ERR) {
        printf("Can not catch SIGUSR2\n");
        exit(1);
    }
    while(1) pause();
}

static void sig_usr(int signo) {
    if(signo == SIGUSR1) {
        printf("Received SIGUSR1\n");
    } 
    else if(signo == SIGUSR2) {
        printf("Received SIGUSR2\n");
    }
    else {
        printf("Received signal %d\n", signo);
        exit(1);
    }
    exit(0);
}