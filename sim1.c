#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define SEQ_LEN 128
#define DIM 64

void softmax(float* x, int len) {
    float max = x[0], sum = 0.0;
    for (int i = 1; i < len; i++)
        if (x[i] > max) max = x[i];
    for (int i = 0; i < len; i++) {
        x[i] = expf(x[i] - max);
        sum += x[i];
    }
    for (int i = 0; i < len; i++)
        x[i] /= sum;
}

void attention(float Q[SEQ_LEN][DIM], float K[SEQ_LEN][DIM], float V[SEQ_LEN][DIM], float output[SEQ_LEN][DIM]) {
    float scores[SEQ_LEN][SEQ_LEN];

    for (int i = 0; i < SEQ_LEN; i++) {
        for (int j = 0; j < SEQ_LEN; j++) {
            float dot = 0.0f;
            for (int d = 0; d < DIM; d++)
                dot += Q[i][d] * K[j][d];
            scores[i][j] = dot / sqrtf((float)DIM);
        }
        softmax(scores[i], SEQ_LEN);
    }

    for (int i = 0; i < SEQ_LEN; i++) {
        for (int d = 0; d < DIM; d++) {
            output[i][d] = 0.0f;
            for (int j = 0; j < SEQ_LEN; j++) {
                output[i][d] += scores[i][j] * V[j][d];
            }
        }
    }
}

void init_tensor(float A[SEQ_LEN][DIM]) {
    for (int i = 0; i < SEQ_LEN; i++)
        for (int j = 0; j < DIM; j++)
            A[i][j] = (float)rand() / RAND_MAX;
}

int main() {
    float Q[SEQ_LEN][DIM], K[SEQ_LEN][DIM], V[SEQ_LEN][DIM], O[SEQ_LEN][DIM];
    init_tensor(Q); init_tensor(K); init_tensor(V);

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    attention(Q, K, V, O);

    clock_gettime(CLOCK_MONOTONIC, &end);

    double time_taken = (end.tv_sec - start.tv_sec) +
                        (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Attention computation took %.6f seconds.\n", time_taken);
    return 0;
}
