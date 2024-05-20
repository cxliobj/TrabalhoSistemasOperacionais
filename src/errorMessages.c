#include "../include/errorMessages.h"

void verify_thread_create(int thread)
{
    if (thread != 0)
    {
        printf("Thread create failed.\n");
        exit(EXIT_FAILURE);
    }
}

void verify_thread_join(int thread)
{
    if (thread != 0)
    {
        printf("Thread join failed.\n");
        exit(EXIT_FAILURE);
    }
}

void verify_allocation_memory_size(int obj)
{
    if (obj <= 0)
    {
        printf("Incompatible size to allocate memory.\n");
        exit(EXIT_FAILURE);
    }
}

void verify_allocation_memory(void* obj)
{
    if (obj == NULL)
    {
        printf("Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }
}

void verify_open_file(FILE* file)
{
    if (file == NULL)
    { 
        printf("Failed to open some file.\n"); 
        exit(EXIT_FAILURE); 
    }
}

void verify_num_args(int argc)
{
    if (argc != 8) 
    {
        printf("Invalid arguments quantity.\n");
        exit(EXIT_FAILURE);
    }
}

void verify_num_threads_dimension(int num_threads, int dimension)
{
    if (num_threads <= 0 || num_threads > 4)
    {
        printf("Invalid threads number.\n");
        exit(EXIT_FAILURE);
    }
    if (dimension <= 0)
    {
       printf("Invalid dimension number.\n");
        exit(EXIT_FAILURE); 
    }
    if (dimension % num_threads != 0)
    {
        printf("Number of threads is incompatible with the dimension number.\n");
        exit(EXIT_FAILURE);
    }
}