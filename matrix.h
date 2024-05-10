#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "errorMessages.h"
#include "resources.h"

#define position(I, J, DIMENSION) ((I)*(DIMENSION) + (J))

    void* transcribeMatrix (void* matrix_ref);

    void* writeMatrix (void* matrix_ref);

    void* sumMatrix(void* matrix_ref);

    void* multiplyMatrix (void* matrix_ref);

    void* reduceMatrix (void* matrix_ref);

#endif