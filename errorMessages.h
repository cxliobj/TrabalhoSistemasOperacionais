#ifndef ERROR_HPP
#define ERROR_HPP

#include <stdio.h>
#include <stdlib.h>

    void verify_thread_create (int thread);

    void verify_thread_join (int thread);

    void verify_allocation_memory_size (int obj);

    void verify_allocation_memory (void* obj);

    void verify_open_file (FILE* file);

    void verify_num_args (int argc);

    void verify_num_threads_dimension (int num_threads, int dimension);

#endif