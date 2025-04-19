#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define IN_SIZE 128
#define KERNEL_SIZE 3
#define OUT_SIZE (IN_SIZE - KERNEL_SIZE + 1)

void conv2d(float input[IN_SIZE][IN_SIZE], float kernel[KERNEL_SIZE][KERNEL_SIZE], float output[OUT_SIZE][OUT_SIZE]) {
    for (int i = 0; i < OUT_SIZE; i++) {
        for (int j = 0; j < OUT_SIZE; j++) {
            float sum = 0.0f;
            for (int ki = 0; ki < KERNEL_SIZE; ki++) {
                for (int kj = 0; kj < KERNEL_SIZE; kj++) {
                    sum += input[i + ki][j + kj] * kernel[ki][kj];
                }
            }
            output[i][j] = sum;
        }
    }
}

void init_matrix(float A[IN_SIZE][IN_SIZE]) {
    for (int i = 0; i < IN_SIZE; i++)
        for (int j = 0; j < IN_SIZE; j++)
            A[i][j] = (float)rand() / RAND_MAX;
}

void init_kernel(float K[KERNEL_SIZE][KERNEL_SIZE]) {
    for (int i = 0; i < KERNEL_SIZE; i++)
        for (int j = 0; j < KERNEL_SIZE; j++)
            K[i][j] = (float)rand() / RAND_MAX;
}

int main() {
    float input[IN_SIZE][IN_SIZE];
    float kernel[KERNEL_SIZE][KERNEL_SIZE];
    float output[OUT_SIZE][OUT_SIZE];

    init_matrix(input);
    init_kernel(kernel);

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    conv2d(input, kernel, output);

    clock_gettime(CLOCK_MONOTONIC, &end);

    double time_taken = (end.tv_sec - start.tv_sec) +
                        (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("2D convolution took %.6f seconds.\n", time_taken);
    return 0;
}
