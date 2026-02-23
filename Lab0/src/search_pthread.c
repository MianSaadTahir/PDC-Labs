#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 100000000
#define TARGET 42
#define NUM_THREADS 4

int *arr;
int found_index = -1;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* search_chunk(void* arg) {

    long id = *(long*)arg;
    long start = id * (N / NUM_THREADS);
    long end = start + (N / NUM_THREADS);

    if (id == NUM_THREADS - 1)
        end = N;

    for (long i = start; i < end; i++) {

        pthread_mutex_lock(&lock);
        int stop = (found_index != -1);
        pthread_mutex_unlock(&lock);

        if (stop) break;

        if (arr[i] == TARGET) {
            pthread_mutex_lock(&lock);
            if (found_index == -1)
                found_index = i;
            pthread_mutex_unlock(&lock);
            break;
        }
    }

    return NULL;
}

int main() {

    pthread_t threads[NUM_THREADS];
    long ids[NUM_THREADS];

    arr = malloc(sizeof(int) * N);

    for (long i = 0; i < N; i++)
        arr[i] = rand() % 100;

    for (long i = 0; i < NUM_THREADS; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, search_chunk, &ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    if (found_index != -1)
        printf("Found at index %d\n", found_index);
    else
        printf("Not found\n");

    free(arr);
    return 0;
}