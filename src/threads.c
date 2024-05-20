#include "../include/threads.h"

void sum(Matrix** matrix, int dimension, int num_threads)
{
    ThreadParameters* parameters = newThreadParameters(num_threads);

    Matrix* matrix_A = matrix[0];
    Matrix* matrix_B = matrix[1];
    Matrix* matrix_D = matrix[3];

    // Como ha apenas 1 thread, havera apenas chamadas das funcoes (sem threads adicionais)
    if (num_threads == 1)
    {   
        // Leitura da matriz A
        matrix_transcribe((void*) matrix_A);

        // Leitura da matriz B
        matrix_transcribe((void*) matrix_B);

        // Soma das matrizes A + B = D
        parameters[0].array1 = matrix_A->array;
        parameters[0].array2 = matrix_B->array;
        parameters[0].array3 = matrix_D->array;
        parameters[0].idx_start = 0;
        parameters[0].idx_final = dimension * dimension;
        matrix_sum((void*) &parameters[0]);
        free(parameters);
        return;
    }

    pthread_t* thread_ids = newThreadIDs(num_threads);
    register int i;

    // Inicio das threads de leitura das matrizes A e B
    for (i = 0; i < 2; i++)
    {
        int thread = pthread_create(&thread_ids[i], NULL, matrix_transcribe, (void*) matrix[i]);
        verify_thread_create(thread);
    }

    // Aguardando a finalizacao das threads de leitura das matrizes A e B
    for (i = 0; i < 2; i++)
    {
        int thread = pthread_join(thread_ids[i], NULL);
        verify_thread_join(thread);
    }

    register unsigned int num_elements = (dimension * dimension) / num_threads;
    
    // Inicio das threads de soma A + B = D
    for (i = 0; i < num_threads; i++)
    {
        parameters[i].array1 = matrix_A->array;
        parameters[i].array2 = matrix_B->array;
        parameters[i].array3 = matrix_D->array;
        parameters[i].idx_start = num_elements * i;
        parameters[i].idx_final = (num_elements * (i+1));
        
        int thread = pthread_create(&thread_ids[i], NULL, matrix_sum, (void*) &parameters[i]);
        verify_thread_create(thread);
    }

    // Aguardando a finalizacao das threads de soma
    for (int i = 0; i < num_threads; i++)
    {
        int thread = pthread_join(thread_ids[i], NULL);
        verify_thread_join(thread);
    }
    free(parameters);
    free(thread_ids);
}

void multiply(Matrix** matrix, int dimension, int num_threads)
{
    ThreadParameters* parameters = newThreadParameters(num_threads);

    Matrix* matrix_C = matrix[2];
    Matrix* matrix_D = matrix[3];
    Matrix* matrix_E = matrix[4];

    // Como ha apenas 1 thread, havera apenas chamadas das funcoes (sem threads adicionais)
    if (num_threads == 1)
    {   
        // Gravacao da matriz D
        matrix_write((void*) matrix_D);

        // Leitura da matriz C
        matrix_transcribe((void*) matrix_C);

        // Multiplicao das matrizes D x C = E
        parameters[0].array1 = matrix_D->array;
        parameters[0].array2 = matrix_C->array;
        parameters[0].array3 = matrix_E->array;
        parameters[0].dimension = dimension;
        parameters[0].idx_start = 0;
        parameters[0].idx_final = dimension * dimension;
        matrix_multiplication((void*) &parameters[0]);
        free(parameters);
        return;
    }

    pthread_t* thread_ids = newThreadIDs(num_threads);
    register int i;

    // Gravcao da matriz D
    int thread = pthread_create(&thread_ids[0], NULL, matrix_write, (void*) matrix_D);
    verify_thread_create(thread);

    // Leitura da matriz C
    thread = pthread_create(&thread_ids[1], NULL, matrix_transcribe, (void*) matrix_C);
    verify_thread_create(thread);

    // Agurdando a finalizacao das threads de gravacao e leitura
    for (i = 0; i < 2; i++)
    {
        thread = pthread_join(thread_ids[i], NULL);
        verify_thread_join(thread);
    }

    register unsigned int num_elements = (dimension * dimension) / num_threads;

    // Inicio da thread de multiplicacao D x C = E
    for (i = 0; i < num_threads; i++)
    {
        parameters[i].array1 = matrix_D->array;
        parameters[i].array2 = matrix_C->array;
        parameters[i].array3 = matrix_E->array;
        parameters[i].dimension = dimension;
        parameters[i].idx_start = num_elements * i;
        parameters[i].idx_final = (num_elements * (i+1));

        thread = pthread_create(&thread_ids[i], NULL, matrix_multiplication, (void*) &parameters[i]);
        verify_thread_create(thread);
    }

    // Agurdando a finalizacao das threads de multiplicacao
    for (int i = 0; i < num_threads; i++)
    {
        thread = pthread_join(thread_ids[i], NULL);
        verify_thread_join(thread);
    }
    free(parameters);
    free(thread_ids);
}

long long int reduce(Matrix** matrix, int dimension, int num_threads)
{
    ThreadParameters* parameters = newThreadParameters(num_threads+1);
    Matrix* matrix_E = matrix[4];

    // Como ha apenas 1 thread, havera apenas chamadas das funcoes e o retorno do valor de reducao
    if (num_threads == 1)
    {
        // Gravação da matriz E
        matrix_write((void*) matrix_E);

        // Reducao da matriz E
        parameters[0].array1 = matrix_E->array;
        parameters[0].idx_start = 0;
        parameters[0].idx_final = dimension * dimension;
        long long int sum = *(long long int*) matrix_reduce((void*) &parameters[0]);
        return sum;
    }

    long long int* partialSum = NULL;
    long long int sum = 0;
    pthread_t* thread_ids = newThreadIDs(num_threads+1);
    register unsigned int num_elements = (dimension * dimension) / num_threads;
    register int i;

    // Inicio da thread de gravacao da matriz E
    int thread = pthread_create(&thread_ids[num_threads], NULL, matrix_write, (void*) matrix_E);
    verify_thread_create(thread);

    // Inicio da thread de reducao da matriz E
    for (i = 0; i < num_threads; i++)
    {
        parameters[i].array1 = matrix_E->array;
        parameters[i].idx_start = num_elements * i;
        parameters[i].idx_final = (num_elements * (i+1));
        thread = pthread_create(&thread_ids[i], NULL, matrix_reduce, (void*) &parameters[i]);
        verify_thread_create(thread);
    }

    thread = pthread_join(thread_ids[num_threads], NULL);
    verify_thread_join(thread);

    for (int i = 0; i < num_threads; i++)
    {
        thread = pthread_join(thread_ids[i], (void**) &partialSum);
        verify_thread_join(thread);
        sum += *(long long int*) partialSum;
    }
    free(parameters);
    free(thread_ids);
    return sum;
}