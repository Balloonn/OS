#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main() {
    int pid_child1, pid_child2;
    pid_child1 = fork();
    if(pid_child1 < 0) {
        printf("There is an error when creating the process.");
    }   
    else if(pid_child1 == 0) {
        printf("I am child 1!\n");
    }   
    else {
        pid_child2 = fork();
        if(pid_child2 < 0) {
            printf("There is an error when creating the process.");
        }
        else if(pid_child2 == 0) {
            printf("I am child 2!\n");
        }
        else {
            printf("I am father!\n");
        }
    }   
    return 0;                                                                                                                           
}