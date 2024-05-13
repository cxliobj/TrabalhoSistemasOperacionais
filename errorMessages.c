#include "errorMessages.h"

void show_thread_create_error (int thread)
{
    if (thread != 0)
    {
        printf("Thread create failed.\n");
        exit(EXIT_FAILURE);
    }
}

void show_thread_join_error (int thread)
{
    if (thread != 0)
    {
        printf("Thread join failed.\n");
        exit(EXIT_FAILURE);
    }
}

void show_error_size_allocation_memory (int obj)
{
    if (obj <= 0)
    {
        printf("Incompatible size to allocate memory.\n");
        exit(EXIT_FAILURE);
    }
}

void show_error_allocation_memory (void* obj)
{
    if (obj == NULL)
    {
        printf("Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }
}

void show_error_open_file (FILE* file)
{
    if (file == NULL)
    { 
        printf("Failed to open some file.\n"); 
        exit(EXIT_FAILURE); 
    }
}

void show_error_num_args (int argc)
{
    if (argc != 8) 
    {
        printf("Invalid arguments quantity.\n");
        exit(EXIT_FAILURE);
    }
}

void show_error_numThreads_dimension (long long int num_threads, long long int dimension)
{
    if (num_threads <= 0)
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

void show_error_convert_string_to_int (char* endPtr)
{
    if (*endPtr)
    {
        printf("Failed to convert string to int.\n");
        exit(EXIT_FAILURE);
    }
}