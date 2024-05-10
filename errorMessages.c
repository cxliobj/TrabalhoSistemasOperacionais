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