#include "../include/errorMessages.h"

void verify_thread_create(int err)
{
    if (err != 0)
    {
        fprintf(stderr, "Thread create failed.\n");
        exit(EXIT_FAILURE);
    }
}

void verify_thread_join(int err)
{
    if (err != 0)
    {
        fprintf(stderr, "Thread join failed.\n");
        exit(EXIT_FAILURE);
    }
}

void verify_allocation_memory_size(int obj)
{
    if (obj <= 0)
    {
        fprintf(stderr, "Incompatible size to allocate memory.\n");
        exit(EXIT_FAILURE);
    }
}

void verify_allocation_memory(void* obj)
{
    if (obj == NULL)
    {
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }
}

void verify_open_file(FILE* file, char* file_name)
{
    if (file == NULL)
    {
        fprintf(stderr, "Failed to open %s file.\n", file_name);
        exit(EXIT_FAILURE); 
    }
}

void verify_num_args(int argc)
{
    if (argc != 8) 
    {
        fprintf(stderr, "Invalid number of arguments\n");
        exit(EXIT_FAILURE);
    }
}

void verify_num_threads(int num_threads)
{
    if (num_threads <= 0 || num_threads == 3 || num_threads > 4)
    {
        fprintf(stderr, "Invalid number of threads.\n");
        exit(EXIT_FAILURE);
    }
}

void verify_num_dimension(int dimension)
{
    if (dimension <= 0)
    {
        fprintf(stderr, "Invalid dimension number.\n");
        exit(EXIT_FAILURE); 
    }
}