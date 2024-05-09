#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

    Matrix* newMatrix ();

    long long int* vectorAllocation(long long int dimension);

    FILE* openFile(char* argv_file_matrix);

#endif