/*
 * Compilation: gcc -o -pthread exec matrix.c main.c
 * Executation: ./main numThreads numDimension matrixA.txt matrixB.txt matrixC.txt matrixD.txt matrixE.txt
 *              ./main numThreads numDimension matrixA100.txt matrixB100.txt matrixC100.txt matrixD100.txt matrixE100.txt
 *              ./main numThreads numDimension matrixA1k.txt matrixB1k.txt matrixC1k.txt matrixD1k.txt matrixE1k.txt       
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"
#include "string.h"

int main(int argc, char* argv[]) {

    if (argc != 8) 
    {
        printf("Quantidade de argumentos incorreta.\n");
        exit(EXIT_FAILURE);
    }

    long int num_threads = stringToInt(argv[1]);
    long int dimension = stringToInt(argv[2]);

    clock_t start_global, end_global, start_sum, end_sum, start_multiplication, end_multiplication, start_reduction, end_reduction;
    FILE *archive_matrix_A, *archive_matrix_B, *archive_matrix_C, *archive_matrix_D, *archive_matrix_E;

    archive_matrix_A = fopen(argv[3], "r");
    if (archive_matrix_A == NULL) { printf("Arquivo da matriz A nao foi aberto.\n"); exit(EXIT_FAILURE); }

    archive_matrix_B = fopen(argv[4], "r");
    if (archive_matrix_B == NULL) { printf("Arquivo da matriz B nao foi aberto.\n"); exit(EXIT_FAILURE); }

    archive_matrix_C = fopen(argv[5], "r");
    if (archive_matrix_C == NULL) { printf("Arquivo da matriz C nao foi aberto.\n"); exit(EXIT_FAILURE); }

    archive_matrix_D = fopen(argv[6], "w");
    if (archive_matrix_D == NULL) { printf("Arquivo da matriz D nao foi aberto.\n"); exit(EXIT_FAILURE); }

    archive_matrix_E = fopen(argv[7], "w");
    if (archive_matrix_E == NULL) { printf("Arquivo da matriz E nao foi aberto.\n"); exit(EXIT_FAILURE); }

/* DECLARATIONS ********************************************************************************************************************* */

    Matrix* matrix_A = newMatrix(dimension, archive_matrix_A);
    Matrix* matrix_B = newMatrix(dimension, archive_matrix_B);
    Matrix* matrix_C = newMatrix(dimension, archive_matrix_C);
    Matrix* matrix_D = newMatrix(dimension, archive_matrix_D);
    Matrix* matrix_E = newMatrix(dimension, archive_matrix_E);

/* START **************************************************************************************************************************** */

    start_global = clock();

    // PASSO 1 (2 threads Tl)

    transcribeMatrix(matrix_A);
    fclose(matrix_A->fileArray);

    transcribeMatrix(matrix_B);
    fclose(matrix_B->fileArray);

    // PASSO 2 (T threads Tp)

    start_sum = clock();
    sumMatrix(matrix_A, matrix_B, matrix_D);
    end_sum = clock() - start_sum;

    free(matrix_A);
    free(matrix_B);

    // PASSO 3 + PASSO 4 (1 thread Te e 1 thread Tl)

    writeMatrix(matrix_D);
    fclose(matrix_D->fileArray);

    transcribeMatrix(matrix_C);
    fclose(matrix_C->fileArray);

    // PASSO 5 (2 threads Tp)

    start_multiplication = clock();
    multiplyMatrix(matrix_C, matrix_D, matrix_E);
    end_multiplication = clock() - start_multiplication;

    free(matrix_C);
    free(matrix_D);

    // PASSO 6 + PASSO 7 (1 thread Te e 1 thread Tp)

    writeMatrix(matrix_E);
    fclose(matrix_E->fileArray);

    start_reduction = clock();
    reduceMatrix(matrix_E);
    end_reduction = clock() - start_reduction;

    end_global = clock() - start_global;

/* FINAL **************************************************************************************************************************** */

    double total_time_sum = ((double) end_sum)/CLOCKS_PER_SEC;
    double total_time_multiplication = ((double) end_multiplication)/CLOCKS_PER_SEC;
    double total_time_reduction = ((double) end_reduction)/CLOCKS_PER_SEC;
    double total_time_global = ((double) end_global)/CLOCKS_PER_SEC;

    printf("Reducao: %lld.\n", matrix_E->reduction);
    printf("Tempo soma: %lf segundos.\n", total_time_sum);
    printf("Tempo multiplicacao: %lf segundos.\n", total_time_multiplication);
    printf("Tempo reducao: %lf segundos.\n", total_time_reduction);
    printf("Tempo total: %lf segundos.\n", total_time_global);

    return 0;
}