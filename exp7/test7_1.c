#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>

int buf_1[2], buf_2[2];
sem_t sem_1, sem_2, sem_3, sem_4;

void readData1 () {
    FILE *fp = fopen("1.data", "r");
    sem_wait(&sem_1);
    for(int i = 0; !feof(fp); i ++) {
        fscanf(fp, "%d", &buf_1[i]);
    }
    sem_post(&sem_3);
    fclose(fp);
}

void readData2() {
    FILE *fp = fopen("2.data", "r");
    sem_wait(&sem_2);
    for(int i = 0; !feof(fp); i ++) {
        fscanf(fp, "%d", &buf_2[i]);
    }
    sem_post(&sem_4);
    fclose(fp);
}

void fun() {
    sem_wait(&sem_3);
    sem_wait(&sem_4);
    for(int i = 0; i < 2; i ++) {
        printf("%d + %d = %d\n", buf_1[i], buf_2[i], buf_1[i] + buf_2[i]);
        printf("%d * %d = %d\n", buf_1[i], buf_2[i], buf_1[i] * buf_2[i]);
    }
    sem_post(&sem_1);
    sem_post(&sem_2);
}

int main() {
    pthread_t readdata1, readdata2, calculation;
    sem_init(&sem_1, 0, 1);
    sem_init(&sem_2, 0, 1);
    sem_init(&sem_3, 0, 0);
    sem_init(&sem_4, 0, 0);
    pthread_create(&readdata1, NULL, (void*) readData1, NULL);
    pthread_create(&readdata2, NULL, (void*) readData2, NULL);
    pthread_create(&calculation, NULL, (void*) fun, NULL);
    pthread_join(readdata1, NULL);
    pthread_join(readdata2, NULL);
    pthread_join(calculation, NULL);
    sem_destroy(&sem_1);
    sem_destroy(&sem_2);
    sem_destroy(&sem_3);
    sem_destroy(&sem_4);
}