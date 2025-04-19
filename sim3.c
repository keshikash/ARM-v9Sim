#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 512

void matmul(float A[SIZE][SIZE], float B[SIZE][SIZE], float C[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {
            C[i][j] = 0;
            for (int k = 0; k < SIZE; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

void init_matrices(float A[SIZE][SIZE], float B[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {
            A[i][j] = (float)rand() / RAND_MAX;
            B[i][j] = (float)rand() / RAND_MAX;
        }
}

int main() {
    float A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];
    init_matrices(A, B);

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    matmul(A, B, C);

    clock_gettime(CLOCK_MONOTONIC, &end);

    double time_taken = (end.tv_sec - start.tv_sec) +
                        (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Matrix multiplication took %.6f seconds.\n", time_taken);

    return 0;
}
