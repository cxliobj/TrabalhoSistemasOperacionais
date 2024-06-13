#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "../include/errorMessages.h"
#include "../include/resources.h"
#include "../include/matrix.h"
#include "../include/threads.h"
#define _POSIX_C_SOURCE 199309L

struct timespec start_sum, finish_sum;
struct timespec start_mult, finish_mult;
struct timespec start_reduc, finish_reduc;

double global_elapsed;
double sum_elapsed;
double mult_elapsed;
double reduc_elapsed;

int main(int argc, char** argv)
{
    verify_num_args(argc);

    int num_threads = stringToInt(argv[1]);
    verify_num_threads(num_threads);
    
    int dimension = stringToInt(argv[2]);
    verify_num_dimension(dimension);

    Matrix** matrix = (Matrix**) malloc(5 * sizeof(Matrix*));
    for (int i = 0; i < 5; i++)
    {
        matrix[i] = newMatrix(argv[i+3], dimension);
    }

    transcribe_A_and_B(matrix, num_threads);

    clock_gettime(CLOCK_MONOTONIC, &start_sum);
    sum(matrix, dimension, num_threads);
    clock_gettime(CLOCK_MONOTONIC, &finish_sum);

    write_D_transcribe_C(matrix, num_threads);

    clock_gettime(CLOCK_MONOTONIC, &start_mult);
    multiply(matrix, dimension, num_threads);
    clock_gettime(CLOCK_MONOTONIC, &finish_mult);

    clock_gettime(CLOCK_MONOTONIC, &start_reduc);
    long long int reduction = reduce(matrix, dimension, num_threads);
    clock_gettime(CLOCK_MONOTONIC, &finish_reduc);
    
    sum_elapsed = (finish_sum.tv_sec - start_sum.tv_sec);
    sum_elapsed += (finish_sum.tv_nsec - start_sum.tv_nsec) / 1000000000.0;

    mult_elapsed = (finish_mult.tv_sec - start_mult.tv_sec);
    mult_elapsed += (finish_mult.tv_nsec - start_mult.tv_nsec) / 1000000000.0;

    reduc_elapsed = (finish_reduc.tv_sec - start_reduc.tv_sec);
    reduc_elapsed += (finish_reduc.tv_nsec - start_reduc.tv_nsec) / 1000000000.0;

    global_elapsed = sum_elapsed + mult_elapsed + reduc_elapsed;

    printf("Reducao: %lld.\n", reduction);
    printf("Tempo soma: %lf segundos.\n", sum_elapsed);
    printf("Tempo multiplicacao: %lf segundos.\n", mult_elapsed);
    printf("Tempo reducao: %lf segundos.\n", reduc_elapsed);
    printf("Tempo total: %lf segundos.\n", global_elapsed);

    return 0;
}