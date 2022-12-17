#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void thread_int(void *_int) {
    int *num = (int*) _int;
    printf("This is a int pthread, num = %d\n", *num);
}

void thread_char(void *_char) {
    char *ch = (char*) _char;
    printf("This is a char pthread, ch = %c\n", *ch);
}

int main(void) {
    pthread_t id;
    int _int = 1;
    char _char= 'a';
    int ret1 = pthread_create(&id, NULL, (void*) thread_int, &_int);
    if(ret1 != 0) {
        printf("Create int pthread error!\n");
        exit(1);
    }
    int ret2 = pthread_create(&id, NULL, (void*) thread_char, &_char);
    if(ret2 != 0) {
        printf("Create char pthread error!\n");
        exit(1);
    }
    pthread_join(id, NULL);
    printf("Main process exit.\n");
    return 0;
}

