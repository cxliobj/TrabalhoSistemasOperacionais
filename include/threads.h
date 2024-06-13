#ifndef THREADS_H
#define THREADS_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../include/errorMessages.h"
#include "../include/resources.h"
#include "../include/matrix.h"

/**
 * Função para fazer a leitura das matrizes A e B.
 * @param matrix Ponteiro de ponteiro que armazena as informações das 5 matrizes
 * @param num_threads Número de threads
 * @return A função retorna NULL.
 * @throw Retorna 2 se alguma thread falhar, junto com uma mensagem de erro.
**/
void transcribe_A_and_B(Matrix** matrix, int num_threads);

/**
 * Função para fazer a soma das matrizes A e B.
 * @param matrix Ponteiro de ponteiro que armazena as informações das 5 matrizes
 * @param dimension Tamanho da matriz
 * @param num_threads Número de threads
 * @return A função retorna NULL.
 * @throw Retorna 2 se alguma thread falhar, junto com uma mensagem de erro.
**/
void sum(Matrix** matrix, int dimension, int num_threads);

/**
 * Função para fazer a gravação da matriz D e leitura das matriz C.
 * @param matrix Ponteiro de ponteiro que armazena as informações das 5 matrizes
 * @param num_threads Número de threads
 * @return A função retorna NULL.
 * @throw Retorna 2 se alguma thread falhar, junto com uma mensagem de erro.
**/
void write_D_transcribe_C(Matrix** matrix, int num_threads);

/**
 * Função para fazer a gravação da matriz D e redução da matriz E.
 * @param matrix Ponteiro de ponteiro que armazena as informações das 5 matrizes
 * @param dimension Tamanho da matriz
 * @param num_threads Número de threads
 * @return A função retorna NULL.
 * @throw Retorna 2 se alguma thread falhar, junto com uma mensagem de erro.
**/
void multiply(Matrix** matrix, int dimension, int num_threads);

/**
 * Função para fazer a gravação da matriz D e redução da matriz E.
 * @param matrix Ponteiro de ponteiro que armazena as informações das 5 matrizes
 * @param dimension Tamanho da matriz
 * @param num_threads Número de threads
 * @return Retorna um inteiro de tipo long long int contendo a soma da operação de redução.
 * @throw Retorna 2 se alguma thread falhar, junto com uma mensagem de erro.
**/
long long int reduce(Matrix** matrix, int dimension, int num_threads);

#endif