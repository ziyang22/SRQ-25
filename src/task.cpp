#include "../include/task.h"
#include <stdlib.h>

/**
 * @brief 朴素的矩阵乘法实现 C = A * B.
 * 这个函数作为参考，学生不应该修改它。
 */
void multiply_naive(const double* A, const double* B, double* C, int N) {
    for (int i = 0; i < N * N; ++i) {
        C[i] = 0.0;
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                C[i * N + j] += A[i * N + k] * B[k * N + j];
            }
        }
    }
}

/**
 * @brief 优化的矩阵乘法实现。
 * 比赛选手需要在此函数中实现他们的优化代码。
 * 默认情况下，此函数调用朴素实现，以便于测试。
 */
void multiply_optimized(const double* A, const double* B, double* C, int N) {
    // 调用朴素实现作为默认行为
    multiply_naive(A, B, C, N);
}