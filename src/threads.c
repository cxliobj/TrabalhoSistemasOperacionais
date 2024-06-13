#include "../include/threads.h"

void transcribe_A_and_B(Matrix** matrix, int num_threads)
{
    Matrix* matrix_A = matrix[0];
    Matrix* matrix_B = matrix[1];

    if (num_threads == 1)
    {   
        // Leitura da matriz A
        matrix_transcribe((void*) matrix_A);

        // Leitura da matriz B
        matrix_transcribe((void*) matrix_B);
    }
    else 
    {
        pthread_t* thread_ids = newThreadIDs(num_threads);
        register int i;
        int err;

        // Inicio das threads de leitura das matrizes A e B
        for (i = 0; i < 2; i++)
        {
            err = pthread_create(&thread_ids[i], NULL, matrix_transcribe, (void*) matrix[i]);
            verify_thread_create(err);
        }

        // Aguardando a finalizacao das threads de leitura das matrizes A e B
        for (i = 0; i < 2; i++)
        {
            err = pthread_join(thread_ids[i], NULL);
            verify_thread_join(err);
        }
        free(thread_ids);
    } 
}

void sum(Matrix** matrix, int dimension, int num_threads)
{
    Matrix* matrix_A = matrix[0];
    Matrix* matrix_B = matrix[1];
    Matrix* matrix_D = matrix[3];

    Parameters* parameters = newParameters(num_threads);
    register unsigned int num_elements = (dimension * dimension) / num_threads;
    register int i;

    for (i = 0; i < num_threads; i++)
    {
        parameters[i].array1 = matrix_A->array;
        parameters[i].array2 = matrix_B->array;
        parameters[i].array3 = matrix_D->array;
        parameters[i].idx_start = num_elements * i;
        parameters[i].idx_final = (num_elements * (i+1));
    }

    if (num_threads == 1)
    {   
        // Soma das matrizes A e B
        matrix_sum((void*) &parameters[0]);
        free(parameters);
    }
    else 
    {
        pthread_t* thread_ids = newThreadIDs(num_threads);
        int err;

        // Inicio das threads de soma
        for (i = 0; i < num_threads; i++)
        {
            err = pthread_create(&thread_ids[i], NULL, matrix_sum, (void*) &parameters[i]);
            verify_thread_create(err);
        }

        // Aguardando a finalizacao das threads de soma
        for (int i = 0; i < num_threads; i++)
        {
            err = pthread_join(thread_ids[i], NULL);
            verify_thread_join(err);
        }
        free(parameters);
        free(thread_ids);
    }
    free(matrix_A);
    free(matrix_B);
}

void write_D_transcribe_C(Matrix** matrix, int num_threads)
{
    Matrix* matrix_C = matrix[2];
    Matrix* matrix_D = matrix[3];
    
    if (num_threads == 1)
    {   
        // Gravacao da matriz D
        matrix_write((void*) matrix_D);

        // Leitura da matriz C
        matrix_transcribe((void*) matrix_C);
    }
    else 
    {
        pthread_t* thread_ids = newThreadIDs(num_threads);
        register int i;
        int err;

        // Gravação da matriz D
        err = pthread_create(&thread_ids[0], NULL, matrix_write, (void*) matrix_D);
        verify_thread_create(err);

        // Leitura da matriz C
        err = pthread_create(&thread_ids[1], NULL, matrix_transcribe, (void*) matrix_C);
        verify_thread_create(err);

        // Aguardando a finalizacao das threads de gravação e leitura das matrizes D e C
        for (i = 0; i < 2; i++)
        {
            err = pthread_join(thread_ids[i], NULL);
            verify_thread_join(err);
        }
        free(thread_ids);
    }
}

void multiply(Matrix** matrix, int dimension, int num_threads)
{
    Matrix* matrix_C = matrix[2];
    Matrix* matrix_D = matrix[3];
    Matrix* matrix_E = matrix[4];

    Parameters* parameters = newParameters(num_threads);
    register unsigned int num_elements = (dimension * dimension) / num_threads;
    register int i;

    for (i = 0; i < num_threads; i++)
    {
        parameters[i].array1 = matrix_D->array;
        parameters[i].array2 = matrix_C->array;
        parameters[i].array3 = matrix_E->array;
        parameters[i].dimension = dimension;
        parameters[i].idx_start = num_elements * i;
        parameters[i].idx_final = (num_elements * (i+1));
    }

    if (num_threads == 1)
    {
        // Multiplicação das matrizes D e C
        matrix_multiplication((void*) &parameters[0]);
        free(parameters);
    }
    else
    {
        pthread_t* thread_ids = newThreadIDs(num_threads);
        int err;

        // Inicio das threads de multiplicação
        for (i = 0; i < num_threads; i++)
        {
            err = pthread_create(&thread_ids[i], NULL, matrix_multiplication, (void*) &parameters[i]);
            verify_thread_create(err);
        }

        // Aguardando a finalizacao das threads de multiplicação
        for (i = 0; i < num_threads; i++)
        {
            err = pthread_join(thread_ids[i], NULL);
            verify_thread_join(err);
        }
        free(parameters);
        free(thread_ids);
    }
    free(matrix_C);
    free(matrix_D);
}

long long int reduce(Matrix** matrix, int dimension, int num_threads)
{
    Matrix* matrix_E = matrix[4];

    Parameters* parameters = newParameters(num_threads+1);
    register unsigned int num_elements = (dimension * dimension) / num_threads;
    register int i;
    long long int sum = 0;

    for (i = 0; i < num_threads; i++)
    {
        parameters[i].array1 = matrix_E->array;
        parameters[i].idx_start = num_elements * i;
        parameters[i].idx_final = (num_elements * (i+1));
    }

    if (num_threads == 1)
    {
        // Gravação da matriz E
        matrix_write((void*) matrix_E);

        // Redução da matriz E
        sum = *(long long int*) matrix_reduce((void*) &parameters[0]);
    }
    else
    {
        pthread_t* thread_ids = newThreadIDs(num_threads+1);
        long long int* partialSum = NULL;
        int err;

        // Inicio da thread de gravação da matriz E
        err = pthread_create(&thread_ids[num_threads], NULL, matrix_write, (void*) matrix_E);
        verify_thread_create(err);

        // Inicio das threads de redução da matriz E
        for (i = 0; i < num_threads; i++)
        {
            err = pthread_create(&thread_ids[i], NULL, matrix_reduce, (void*) &parameters[i]);
            verify_thread_create(err);
        }

        // Esperando a thread de gravação
        err = pthread_join(thread_ids[num_threads], NULL);
        verify_thread_join(err);

        // Esperando as threads de redução
        for (int i = 0; i < num_threads; i++)
        {
            err = pthread_join(thread_ids[i], (void**) &partialSum);
            verify_thread_join(err);

            sum += *(long long int*) partialSum;
        }
        free(parameters);
        free(thread_ids);
    }
    free(matrix_E);
    return sum;
}