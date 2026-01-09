#include <stdlib.h>
#include <stdbool.h>

#include "random_bool.h"

bool random_bool(double probability)
{
    return rand() < probability * ((double)RAND_MAX + 1.0);
}


