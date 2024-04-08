/*
 * Compilation: gcc -o projetoSO projetoSO.c
 * Executation: ./projetoSO T n matrixA.txt matrixB.txt matrixC.txt matrixD.txt matrixE.txt
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Matrix 
{
    FILE* fileArray;
    int* array;
    int dimension;
    long long reduction;
} Matrix;

#define position(I, J, DIMENSION) ((I)*(DIMENSION) + (J))

int stringToInt (char* argv);

Matrix* newMatrix (int dimension, FILE* argv_file_matrix);

void sumMatrix (Matrix* matrix1, Matrix* matrix2, Matrix* matrix3);

void multiplyMatrix (Matrix* matrix1, Matrix* matrix2, Matrix* matrix3);

void transcribeMatrix (Matrix* matrix);

void writeMatrix (Matrix* matrix);

void reduceMatrix (Matrix* matrix);

int main(int argc, char* argv[]) {

    if (argc != 8) 
    {
        printf("Quantidade de argumentos incorreta.\n");
        exit(-1);
    }

    int num_threads = stringToInt(argv[1]);
    int dimension = stringToInt(argv[2]);

    clock_t start_global, end_global, start_sum, end_sum, start_multiplication, end_multiplication, start_reduction, end_reduction;
    FILE *archive_matrix_A, *archive_matrix_B, *archive_matrix_C, *archive_matrix_D, *archive_matrix_E;

    archive_matrix_A = fopen(argv[3], "r");
    if (archive_matrix_A == NULL) { printf("Arquivo da matriz A nao foi aberto.\n"); return 1; }

    archive_matrix_B = fopen(argv[4], "r");
    if (archive_matrix_B == NULL) { printf("Arquivo da matriz B nao foi aberto.\n"); return 1; }

    archive_matrix_C = fopen(argv[5], "r");
    if (archive_matrix_C == NULL) { printf("Arquivo da matriz C nao foi aberto.\n"); return 1; }

    archive_matrix_D = fopen(argv[6], "w");
    if (archive_matrix_D == NULL) { printf("Arquivo da matriz D nao foi aberto.\n"); return 1; }

    archive_matrix_E = fopen(argv[7], "w");
    if (archive_matrix_E == NULL) { printf("Arquivo da matriz E nao foi aberto.\n"); return 1; }

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

/* FUNCTIONS ************************************************************************************************************************ */

int stringToInt (char* argv) {
    char *endPtr;
    long int number = strtol(argv, &endPtr, 10);

    if (!*endPtr)
        return number;
    else
        return -2;
}

Matrix* newMatrix(int dimension, FILE* argv_file_matrix)
{
    Matrix* matrix = (Matrix*) malloc(sizeof(Matrix));
    matrix->fileArray = argv_file_matrix;
    matrix->array = (int*) malloc (dimension * dimension * sizeof(int));
    matrix->dimension = dimension;
    matrix->reduction = 0;
    return matrix;
}

void sumMatrix(Matrix* matrix1, Matrix* matrix2, Matrix* matrix3)
{
    int size = matrix1->dimension * matrix1->dimension;

    for (int position = 0; position < size; position++)
    {
        (matrix3->array)[position] = (matrix1->array)[position] + (matrix2->array)[position];
    }
}

void multiplyMatrix (Matrix* matrix1, Matrix* matrix2, Matrix* matrix3)
{
    int dimension = matrix1->dimension;

    for (int i = 0; i < dimension; i++)
    {
        for (int k = 0; k < dimension; k++)
        {
            for (int j = 0; j < dimension; j++)
            {
                (matrix3->array)[position(i,j, matrix3->dimension)] = (matrix3->array)[position(i, j, matrix3->dimension)] +
                                                    (matrix1->array)[position(i, k, matrix1->dimension)] * (matrix2->array)[position(k, j, matrix2->dimension)];
            }
        }
    }
}

void transcribeMatrix (Matrix* matrix)
{
    int finput=0, position=0;
    while (fscanf(matrix->fileArray, "%d", &finput) != EOF)
    {
        (matrix->array)[position] = finput;
        position++;
    }
}

void writeMatrix (Matrix* matrix)
{
    int dimension = matrix->dimension;

    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            fprintf(matrix->fileArray, "%d ", (matrix->array)[(position(i, j, dimension))]);
        }
        fprintf(matrix->fileArray, "\n");
    }
}

void reduceMatrix (Matrix* matrix)
{
    int size = matrix->dimension * matrix->dimension;
    
    long long sum = 0;

    for (int position = 0; position < size; position++)
    {
        sum += (matrix->array)[position];
    }
    matrix->reduction = sum;
}