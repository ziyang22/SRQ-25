#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>

#include "../include/task.h"

// -----------------------------------------------------------
// 矩阵定义和基本操作
// -----------------------------------------------------------

double* create_matrix(int N) {
    double* m = (double*)malloc(sizeof(double) * N * N);
    if (!m) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }
    for (int i = 0; i < N * N; ++i) {
        m[i] = (double)(i % 100) + 1.0;
    }
    return m;
}

void free_matrix(double* m) {
    free(m);
}

// -----------------------------------------------------------
// 测试和基准函数
// -----------------------------------------------------------

void run_correctness_test() {
    printf("--- Running correctness test ---\n");
    const int N = 100;
    double *A = create_matrix(N);
    double *B = create_matrix(N);
    double *C_naive = create_matrix(N);
    double *C_optimized = create_matrix(N);

    // 调用朴素实现，这个函数位于 task.c 中
    // 在这里直接声明以避免头文件依赖，或者直接复制一份
    void multiply_naive(const double* A, const double* B, double* C, int N);
    multiply_naive(A, B, C_naive, N);

    // 调用学生的优化实现
    multiply_optimized(A, B, C_optimized, N);

    int passed = 1;
    for (int i = 0; i < N * N; ++i) {
        if (fabs(C_naive[i] - C_optimized[i]) > 1e-9) {
            printf("Correctness test failed at index %d!\n", i);
            printf("Naive: %f, Optimized: %f\n", C_naive[i], C_optimized[i]);
            passed = 0;
            break;
        }
    }

    if (passed) {
        printf("Correctness test passed!\n");
    }
    printf("--------------------------------\n");
    
    free_matrix(A);
    free_matrix(B);
    free_matrix(C_naive);
    free_matrix(C_optimized);
}

void run_benchmark() {
    printf("--- Running performance benchmark ---\n");
    int matrix_sizes[] = {1024, 2048, 4096};
    int num_sizes = sizeof(matrix_sizes) / sizeof(matrix_sizes[0]);
    struct timeval start, end;
    double time_taken;

    for (int i = 0; i < num_sizes; ++i) {
        int N = matrix_sizes[i];
        printf("Testing matrix size: %dx%d\n", N, N);
        double *A = create_matrix(N);
        double *B = create_matrix(N);
        double *C = create_matrix(N);

        // 朴素算法计时
        gettimeofday(&start, NULL);
        void multiply_naive(const double* A, const double* B, double* C, int N);
        multiply_naive(A, B, C, N);
        gettimeofday(&end, NULL);
        time_taken = (double)(end.tv_sec - start.tv_sec) + (double)(end.tv_usec - start.tv_usec) / 1000000.0;
        printf("Naive multiplication took: %f seconds.\n", time_taken);

        // 优化算法计时
        gettimeofday(&start, NULL);
        multiply_optimized(A, B, C, N);
        gettimeofday(&end, NULL);
        time_taken = (double)(end.tv_sec - start.tv_sec) + (double)(end.tv_usec - start.tv_usec) / 1000000.0;
        printf("Optimized multiplication took: %f seconds.\n", time_taken);
        printf("--------------------------------\n");
        
        free_matrix(A);
        free_matrix(B);
        free_matrix(C);
    }
}

// -----------------------------------------------------------
// 主函数
// -----------------------------------------------------------

int main(int argc, char* argv[]) {
    if (argc > 1 && strcmp(argv[1], "test") == 0) {
        run_correctness_test();
    } else {
        run_benchmark();
    }
    return 0;
}