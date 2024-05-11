#ifndef ERROR_HPP
#define ERROR_HPP

#include <stdio.h>
#include <stdlib.h>

    void show_thread_create_error (int thread);

    void show_thread_join_error (int thread);

    void show_error_size_allocation_memory (int obj);

    void show_error_allocation_memory (void* obj);

    void show_error_open_file (FILE* file);

#endif