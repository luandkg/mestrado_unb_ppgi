#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

#define N 3

int timestamp = 0;
bool requesting = false;
bool replies[N];

pthread_mutex_t lock;

void request_CS(int id) {
    pthread_mutex_lock(&lock);
    requesting = true;
    timestamp++;
    printf("Processo %d requisitou CS (ts=%d)\n", id, timestamp);

    for (int i = 0; i < N; i++) {
        if (i != id) {
            printf("Processo %d -> requisição enviada a %d\n", id, i);
            replies[i] = true;
        }
    }
    pthread_mutex_unlock(&lock);

    bool ok = false;
    while (!ok) {
        ok = true;
        for (int i = 0; i < N; i++) {
            if (i != id && !replies[i]) {
                ok = false;
            }
        }
        usleep(100000);
    }
}

void release_CS(int id) {
    pthread_mutex_lock(&lock);
    requesting = false;
    printf("Processo %d liberou CS\n", id);
    pthread_mutex_unlock(&lock);
}

void *process(void *arg) {
    int id = *(int *)arg;
    request_CS(id);
    printf("Processo %d entrou na CS\n", id);
    sleep(1);
    release_CS(id);
    return NULL;
}

int main() {
    pthread_t threads[N];
    int ids[N];
    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, process, &ids[i]);
    }
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    return 0;
}
