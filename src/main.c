/**
 * Nome do grupo: Vasco da Gama
 * Integrante 1: Celio Benhami Junior (246625) 
 * Integrante 2: Gabriel Gato Piragini Santana (169025)
*/

#include <stdio.h>
#include <time.h>
#include "../include/errorMessages.h"
#include "../include/resources.h"
#include "../include/threads.h"

#define file_matrix_A argv[3]
#define file_matrix_B argv[4]
#define file_matrix_C argv[5]
#define file_matrix_D argv[6]
#define file_matrix_E argv[7]

int main(int argc, char** argv)
{
    verify_num_args(argc);

    int num_threads = stringToInt(argv[1]);
    verify_num_threads(num_threads);
    
    int dimension = stringToInt(argv[2]);
    verify_num_dimension(dimension);

    Matrix* matrix_A = newMatrix(file_matrix_A, "r+", dimension);
    Matrix* matrix_B = newMatrix(file_matrix_B, "r+", dimension);
    Matrix* matrix_C = newMatrix(file_matrix_C, "r+", dimension);
    Matrix* matrix_D = newMatrix(file_matrix_D, "w+", dimension);
    Matrix* matrix_E = newMatrix(file_matrix_E, "w+", dimension);

    transcribe_A_and_B(matrix_A, matrix_B, num_threads);

    clock_t start_sum = clock();
    sum(matrix_A, matrix_B, matrix_D, dimension, num_threads);
    clock_t end_sum = clock() - start_sum;

    write_D_transcribe_C(matrix_C, matrix_D, num_threads);

    clock_t start_multiplication = clock();
    multiply(matrix_C, matrix_D, matrix_E, dimension, num_threads);
    clock_t end_multiplication = clock() - start_multiplication;

    clock_t start_reduction = clock();
    long long int reduction = reduce(matrix_E, dimension, num_threads);
    clock_t end_reduction = clock() - start_reduction;

    double total_time_sum = ((double) end_sum) / CLOCKS_PER_SEC;
    double total_time_multiplication = ((double) end_multiplication)/ CLOCKS_PER_SEC;
    double total_time_reduction = ((double) end_reduction) / CLOCKS_PER_SEC;
    double total_time_global = total_time_sum + total_time_multiplication + total_time_reduction;

    printf("Reducao: %lld.\n", reduction);
    printf("Tempo soma: %lf segundos.\n", total_time_sum);
    printf("Tempo multiplicacao: %lf segundos.\n", total_time_multiplication);
    printf("Tempo reducao: %lf segundos.\n", total_time_reduction);
    printf("Tempo total: %lf segundos.\n", total_time_global);

    return 0;
}