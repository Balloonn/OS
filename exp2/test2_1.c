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
        printf("b\n");
    }   
    else {
        pid_child2 = fork();
        if(pid_child2 < 0) {
            printf("There is an error when creating the process.");
        }
        else if(pid_child2 == 0) {
            printf("c\n");
        }
        else {
            printf("a\n");
        }
    }   
    return 0;                                                                                                                           
}