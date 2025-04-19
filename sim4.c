#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define SIZE 100000000 

long long *array;
long long total_sum = 0;
pthread_mutex_t lock;

typedef struct {
    int thread_id;
    int start;
    int end;
    long long local_sum;
} ThreadData;

void* thread_sum(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    data->local_sum = 0;
    for (int i = data->start; i < data->end; i++) {
        data->local_sum += array[i];
    }

    pthread_mutex_lock(&lock);
    total_sum += data->local_sum;
    pthread_mutex_unlock(&lock);

    return NULL;
}

double get_time_diff(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) + 1e-9 * (end.tv_nsec - start.tv_nsec);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <num_threads>\n", argv[0]);
        return 1;
    }

    int num_threads = atoi(argv[1]);
    if (num_threads <= 0 || num_threads > 64) {
        fprintf(stderr, "Choose between 1 and 64 threads.\n");
        return 1;
    }

    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];
    pthread_mutex_init(&lock, NULL);

    array = malloc(SIZE * sizeof(long long));
    for (int i = 0; i < SIZE; i++) {
        array[i] = 1;
    }

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    int chunk = SIZE / num_threads;

    for (int i = 0; i < num_threads; i++) {
        thread_data[i].thread_id = i;
        thread_data[i].start = i * chunk;
        thread_data[i].end = (i == num_threads - 1) ? SIZE : (i + 1) * chunk;
        pthread_create(&threads[i], NULL, thread_sum, &thread_data[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("Threads: %d, Sum: %lld, Time: %.4f seconds\n",
           num_threads, total_sum, get_time_diff(start, end));

    pthread_mutex_destroy(&lock);
    free(array);
    return 0;
}
