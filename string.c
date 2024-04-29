#include "string.h"

int stringToInt (char* argv) 
{
    char *endPtr;
    long int number = strtol(argv, &endPtr, 10);

    if (!*endPtr)
    {
        return number;
    }
    else
    {
        printf("Conversao stringToInt falhou.\n");
        exit(EXIT_FAILURE);
    }
}