#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <time.h> 
#include <omp.h>
#include "../include/task.h"

// -----------------------------------------------------------
// 矩阵定义和基本操作
// -----------------------------------------------------------

double* create_sparse_matrix(int rows, int cols, double sparsity) {
    double* m = (double*)malloc(sizeof(double) * rows * cols);
    if (!m) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }
    for (int i = 0; i < rows * cols; ++i) {
        double r = (double)rand() / RAND_MAX;
        if (r < sparsity) {
            m[i] = (double)((i % 100) + 1.0);
        } else {
            m[i] = 0.0;
        }
    }
    return m;
}


double* create_matrix(int rows, int cols) {
    double* m = (double*)malloc(sizeof(double) * rows * cols);
    if (!m) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }
    for (int i = 0; i < rows * cols; ++i) {
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

    // 随便挑一个 M,K,N 做测试
    srand((unsigned)time(NULL));
    const int M = 1000 + rand() % 1001;
    const int K = 1000 + rand() % 1001;
    const int N = 1000 + rand() % 1001;

    double *A = create_matrix(M, K);
    double *B = create_matrix(K, N);
    double *C_naive = create_matrix(M, N);
    double *C_optimized = create_matrix(M, N);

    // 声明朴素版本
    void multiply_naive(const double* A, const double* B, double* C, int M, int K, int N);
    multiply_naive(A, B, C_naive, M, K, N);

    // 调用优化版本
    void multiply_optimized(const double* A, const double* B, double* C, int M, int K, int N);
    multiply_optimized(A, B, C_optimized, M, K, N);

    // 验证结果
    int passed = 1;
    for (int i = 0; i < M * N; ++i) {
        if (fabs(C_naive[i] - C_optimized[i]) > 1e-9) {
            printf("Correctness test failed at index %d (row=%d, col=%d)!\n",
                   i, i / N, i % N);
            printf("Naive: %f, Optimized: %f\n", C_naive[i], C_optimized[i]);
            passed = 0;
            break;
        }
    }

    if (passed) {
        printf("\033[32mCorrectness test passed!\033[0m\n");
    }
    printf("--------------------------------\n");

    free_matrix(A);
    free_matrix(B);
    free_matrix(C_naive);
    free_matrix(C_optimized);
}


void run_benchmark() {
    printf("--- Running performance benchmark ---\n");

    // M, K, N 组合 !!!!严禁修改!!!!
    int M_list[] = {1024, 2048, 5321, 2025};
    int K_list[] = {4321, 1466, 1235, 4666};  
    int N_list[] = {1024, 2048, 3425, 2025}; 

    int num_cases = sizeof(M_list) / sizeof(M_list[0]);

    struct timeval start, end;
    double time_taken;

    for (int i = 0; i < num_cases; ++i) {
        int M = M_list[i];
        int K = K_list[i];
        int N = N_list[i];

        printf("Testing matrix multiplication: %d x %d  *  %d x %d  =  %d x %d\n",
               M, K, K, N, M, N);

        double *A, *B, *C_naive, *C_opt;
        if (i == num_cases - 1) {
            A = create_sparse_matrix(M, K, 0.05);
            B = create_sparse_matrix(K, N, 0.05);
        } else {
            A = create_matrix(M, K);
            B = create_matrix(K, N);
        }

        C_naive = (double*)calloc(M * N, sizeof(double));
        C_opt   = (double*)calloc(M * N, sizeof(double));

        // 朴素算法计时
        gettimeofday(&start, NULL);
        void multiply_naive(const double* A, const double* B, double* C, int M, int K, int N);
        multiply_naive(A, B, C_naive, M, K, N);
        gettimeofday(&end, NULL);
        time_taken = (double)(end.tv_sec - start.tv_sec) + 
                     (double)(end.tv_usec - start.tv_usec) / 1000000.0;
        printf("Naive multiplication took: %f seconds.\n", time_taken);

        // 优化算法计时
        gettimeofday(&start, NULL);
        void multiply_optimized(const double* A, const double* B, double* C, int M, int K, int N);
        multiply_optimized(A, B, C_opt, M, K, N);
        gettimeofday(&end, NULL);
        time_taken = (double)(end.tv_sec - start.tv_sec) + 
                     (double)(end.tv_usec - start.tv_usec) / 1000000.0;
        printf("Optimized multiplication took: %f seconds.\n", time_taken);

        // 正确性验证
        int passed = 1;
        for (int j = 0; j < M * N; ++j) {
            if (fabs(C_naive[j] - C_opt[j]) > 1e-6) {
                printf("\033[31mCorrectness test failed at index %d (row=%d, col=%d)!\n",
                    j, j / N, j % N);
                printf("Naive: %f, Optimized: %f\033[0m\n", C_naive[j], C_opt[j]);
                passed = 0;
                break;
            }
        }
        if (passed) {
            printf("\033[32mCorrectness test passed!\033[0m\n");
        }
        printf("--------------------------------\n");

        free_matrix(A);
        free_matrix(B);
        free_matrix(C_naive);
        free_matrix(C_opt);
    }
}


// -----------------------------------------------------------
// 主函数
// -----------------------------------------------------------

int main(int argc, char* argv[]) {

// 设置最大线程数为8 !!!!严禁修改!!!!
    omp_set_num_threads(8);
    if (argc > 1 && strcmp(argv[1], "test") == 0) {
        run_correctness_test();
    } else {
        run_benchmark();
    }
    return 0;
}