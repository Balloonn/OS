#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

int main() {
    int fd[2];
    int pid_child1, pid_child2;
    char buf_1[128], buf_2[128];
    pipe(fd);
    if(pipe(fd) < 0) {
        printf("There is an error when creating the pipe.");
        exit(-1);    
    }
    pid_child1 = fork();
    if(pid_child1 < 0) {
        printf("There is an error when creating the process.");
        exit(-1);
    }   
    else if(pid_child1 == 0) {
        close(fd[0]);
        write(fd[1], "Child 1 is sending a message!\n", strlen("Child 1 is sending a message!\n"));
    }   
    else {
        pid_child2 = fork();
        if(pid_child2 < 0) {
            printf("There is an error when creating the process.");
            exit(-1);
        }
        else if(pid_child2 == 0) {
            close(fd[0]);
            write(fd[1], "Child 2 is sending a message!\n", strlen("Child 2 is sending a message!\n")); 
        }
        else {
            wait(0);
            close(fd[1]);
            read(fd[0], buf_1, sizeof(buf_1));
            printf("%s\n", buf_1);
            wait(0);
            read(fd[0], buf_2, sizeof(buf_2));
            printf("%s\n", buf_2);
        }
    }   
    return 0;                                                                                                                           
}