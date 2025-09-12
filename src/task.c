#include "../include/task.h"
#include <stdlib.h>
#include <string.h>
#include <omp.h>
/**
 * @brief 优化的矩阵乘法实现。
 * 比赛选手需要在此函数中实现他们的优化代码。
 */
void multiply_optimized(const double* A, const double* B, double* C, int M, int K, int N) {
    memset(C, 0, M * N * sizeof(double));
    #pragma omp parallel for
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            double sum = 0.0;
            for (int k = 0; k < K; ++k) {
                sum += A[i * K + k] * B[k * N + j];
            }
            C[i * N + j] = sum;
        }
    }
}

